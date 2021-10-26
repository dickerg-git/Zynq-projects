//============================================================================
// Name        : helloworld.c
// Author      : Roger Dickerson
// Version     : 2021
// Copyright   : MIT License
// Description : Xilinx SPI setup and NVRAM Read/Write operations.
//============================================================================

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

/*
 * helloworld.c: test application
 *
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "spi_interface.h"  // Custom SPI functions from this project

#include "xspips.h"

int main()
{
	unsigned char rx_buffer[1024] = {1,2,3,4,5,6,7,8};

    init_platform();
    init_spi0_dev();
    WriteRamEnable( CS0 );
    ReadRamStatus( CS0 );

    unsigned int tx_len = 8;
    WriteRamData( CS0,
    		tx_len,
    		0x7F000,
    		rx_buffer);

    unsigned int rx_len = 8;
    ReadRamData( CS0,
    		rx_len,
    		0x7F000,
    		rx_buffer);

#ifdef TEST_PRINT
    unsigned int d = rx_len;
    while(d--)
        printf("%x: %x\r\n",d,rx_buffer[d]);
#endif

    NVRAM_Test1();

    print("Hello RGD World\n\r");
    print("Successfully ran Hello World application\n\r");

    cleanup_platform();
    return 0;
}
