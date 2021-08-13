/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include <stdio.h>
#include "xparameters.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xil_testmem.h"
#include "xttcps.h"
#include "xgpio.h"
#include "xqspips.h"
#include "sleep.h"
#include <xscugic.h>
#include <xil_exception.h>

#include "platform.h"
#include "memory_config.h"
#include "xil_printf.h"

// Static variables and structs
#define TTC_DEVICE_ID	    XPAR_XTTCPS_0_DEVICE_ID
#define TTC_INTR_ID		    XPAR_XTTCPS_0_INTR
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define QSPI_DEVICE_ID      XPAR_XQSPIPS_0_DEVICE_ID

typedef struct {
	u32 OutputHz;	/* Output frequency */
	u16 Interval;	/* Interval value */
	u8 Prescaler;	/* Prescaler value */
	u16 Options;	/* Option settings */
} TmrCntrSetup;

static TmrCntrSetup SettingsTable[1] = {
	{1000, 0, 0, 0},	/* Ticker timer counter initial setup, only output freq */
};

static XScuGic GicInstancePtr; //GIC
static void TickHandler(void *CallBackRef);


/*
 * memory_test.c: Test memory ranges present in the Hardware Design.
 *
 * This application runs with D-Caches disabled. As a result cacheline requests
 * will not be generated.
 *
 * For MicroBlaze/PowerPC, the BSP doesn't enable caches and this application
 * enables only I-Caches. For ARM, the BSP enables caches by default, so this
 * application disables D-Caches before running memory tests.
 */

void putnum(unsigned int num);

void test_memory_range(struct memory_range_s *range) {
    XStatus status;

    /* This application uses print statements instead of xil_printf/printf
     * to reduce the text size.
     *
     * The default linker script generated for this application does not have
     * heap memory allocated. This implies that this program cannot use any
     * routines that allocate memory on heap (printf is one such function).
     * If you'd like to add such functions, then please generate a linker script
     * that does allocate sufficient heap memory.
     */

    print("Testing memory region: "); print(range->name);  print("\n\r");
    print("    Memory Controller: "); print(range->ip);  print("\n\r");
    #if defined(__MICROBLAZE__) && !defined(__arch64__)
        print("         Base Address: 0x"); putnum(range->base); print("\n\r");
        print("                 Size: 0x"); putnum(range->size); print (" bytes \n\r");
    #else
        xil_printf("         Base Address: 0x%lx \n\r",range->base);
        xil_printf("                 Size: 0x%lx bytes \n\r",range->size);
    #endif

    status = Xil_TestMem32((u32*)range->base, 1024, 0xAAAA5555, XIL_TESTMEM_ALLMEMTESTS);
    print("          32-bit test: "); print(status == XST_SUCCESS? "PASSED!":"FAILED!"); print("\n\r");

    status = Xil_TestMem16((u16*)range->base, 2048, 0xAA55, XIL_TESTMEM_ALLMEMTESTS);
    print("          16-bit test: "); print(status == XST_SUCCESS? "PASSED!":"FAILED!"); print("\n\r");

    status = Xil_TestMem8((u8*)range->base, 4096, 0xA5, XIL_TESTMEM_ALLMEMTESTS);
    print("           8-bit test: "); print(status == XST_SUCCESS? "PASSED!":"FAILED!"); print("\n\r");

}

int main()
{
    int i;

	   XGpio input, output;
	   int button_data;
	   int led_data = 0xF;

	init_platform();

    print("Hello World\n\r");

    // Set up the GPIO for buttons, LEDs
    XGpio_Initialize(&input,  XPAR_AXI_GPIO_1_DEVICE_ID);	//initialize input XGpio variable
	XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	//initialize output XGpio variable

	XGpio_SetDataDirection(&input,  1, 0xF);			//set GPIO  channel tristate buffer to input
	XGpio_SetDataDirection(&output, 2, 0x0);		//set GPIO2 channel tristate buffer to output

	button_data = XGpio_DiscreteRead(&input, 1);
	XGpio_DiscreteWrite(&output, 2, led_data);


	// Set up QSPI controller for reading
	XQspiPs_Config *QSPIConfig;
	XQspiPs         Qspi;

	QSPIConfig = XQspiPs_LookupConfig(QSPI_DEVICE_ID);
	XQspiPs_CfgInitialize(&Qspi, QSPIConfig, QSPIConfig->BaseAddress);

	XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_8);
	XQspiPs_SetOptions(&Qspi, XQSPIPS_LQSPI_MODE_OPTION | XQSPIPS_HOLD_B_DRIVE_OPTION);

	XQspiPs_Enable((&Qspi));


	// Set up TTC Timer as interrupt source
	XTtcPs_Config *TCCConfig;
	XTtcPs Timer;
	TmrCntrSetup *TimerSetup;

	TimerSetup = &SettingsTable[TTC_DEVICE_ID];

 	TCCConfig = XTtcPs_LookupConfig(TTC_DEVICE_ID);
 	XTtcPs_CfgInitialize(&Timer, TCCConfig, TCCConfig->BaseAddress);
	XTtcPs_Stop((&Timer));

 	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
 						      XTTCPS_OPTION_WAVE_DISABLE);

 	XTtcPs_SetOptions(&Timer, TimerSetup->Options);
 	XTtcPs_CalcIntervalFromFreq(&Timer, TimerSetup->OutputHz,&(TimerSetup->Interval), &(TimerSetup->Prescaler));

    XTtcPs_SetInterval(&Timer, TimerSetup->Interval);
    XTtcPs_SetPrescaler(&Timer, TimerSetup->Prescaler);
	XTtcPs_Start((&Timer));

    XTtcPs_GetCounterValue((&Timer));


    // Set up the GIC interrupt controller
	XScuGic_Config *IntcConfig; //GIC config
	Xil_ExceptionInit();

	//initialize the GIC
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);

	XScuGic_CfgInitialize(&GicInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
    	//connect to the hardware
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
				(void*)&GicInstancePtr);

		//add interrupt handler function
	XScuGic_Connect(&GicInstancePtr, TTC_INTR_ID,
			(Xil_ExceptionHandler)TickHandler, (void *)&Timer);

		//enable the interrupt controller and Timer mask
	XScuGic_Enable(&GicInstancePtr, TTC_INTR_ID);


	// Set up TTC Timer as interrupt source
	XTtcPs_EnableInterrupts(&Timer, XTTCPS_IXR_INTERVAL_MASK);

	// Enable interrupts in the Processor.
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);


    print("--Starting Memory Test Application--\n\r");
    print("NOTE: This application runs with D-Cache disabled. ");
    print("As a result, cacheline requests will not be generated\n\r");

    for (i = 0; i < n_memory_ranges; i++) {
        test_memory_range(&memory_ranges[i]);
    }

    print("--Memory Test Application Complete--\n\r");
    print("Successfully ran Memory Test Application\n\r");

    while(1);

    cleanup_platform();
    return 0;
}


static void TickHandler(void *CallBackRef)
{
	u32 StatusEvent;
	static u32 EventNum = 0;

	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);

	EventNum++;
	if(EventNum % 100000 == 0)
		printf("Event: %lu = %lu\n\r", EventNum, StatusEvent);

}
