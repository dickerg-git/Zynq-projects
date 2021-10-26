//============================================================================
// Name        : spi_interface.c
// Author      : Roger Dickerson
// Version     : 2021
// Copyright   : MIT License
// Description : Xilinx SPI setup and NVRAM Read/Write operations.
//============================================================================

#include "spi_interface.h"  // Custom SPI functions from this project
#include "xspips.h"


#define SPI_DEVICE_ID      XPAR_XSPIPS_0_DEVICE_ID

/*  SPI controller instances from GLobal main() */
        static XSpiPs               SpiInstance;        // SPI controller instance
        static XSpiPs_Config*       SpiConfigPtr;       // SPI config pointer

// Internal buffers for non-streaming data
unsigned char WriteBuff[256];
unsigned char ReadBuff[256];



unsigned int NVRAM_Test1()
{
    unsigned int r_word = 0;

    ReadRamWord( CS0, &r_word, 0x7F000);
    ReadRamWord( CS0, &r_word, 0x7F001);
    ReadRamWord( CS0, &r_word, 0x7F002);
    ReadRamWord( CS0, &r_word, 0x7F003);
    ReadRamWord( CS0, &r_word, 0x7F004);

    unsigned int w_word = 0x03040506;
    WriteRamWord( CS0, &w_word, 0x7F010);
    ReadRamWord( CS0, &r_word, 0x7F010);

    w_word = 0;
    WriteRamDisable( CS0 );
    ReadRamStatus( CS0 );
    WriteRamWord( CS0, &w_word, 0x7F010);
    ReadRamWord( CS0, &r_word, 0x7F010);

    return XST_SUCCESS;
}

    //
    // Initialize the Xilinx SPI 0 instance
    //
unsigned int init_spi0_dev()
{
	int error = XST_SUCCESS;

	xil_printf("%s SPI controller init\r\n", __func__);

	//
    // Configure the SPI instance
    //
    SpiConfigPtr = XSpiPs_LookupConfig(XPAR_PS7_SPI_0_DEVICE_ID);

    XSpiPs_CfgInitialize(&SpiInstance, SpiConfigPtr, SpiConfigPtr->BaseAddress);

	//
	// Perform a self-test to check hardware build.
	//
	error = XSpiPs_SelfTest(&SpiInstance);
	if (error != XST_SUCCESS) {
		return XST_FAILURE;
	}
	xil_printf("%s SPI self test success\r\n", __func__);

    //
    // Set the SPI controller as master, manual chip select mode, manual start
    //

    unsigned int  spi_options = XSpiPs_GetOptions(&SpiInstance);

    unsigned int SPI_Options = spi_options;

    SPI_Options = XSPIPS_MASTER_OPTION |
                  XSPIPS_FORCE_SSELECT_OPTION |
                  XSPIPS_MANUAL_START_OPTION;

    error = XSpiPs_SetOptions(&SpiInstance, SPI_Options);

    //
    // Set the transfer length to 8 bits
    //

    //
    // Set the clock polarity to inactive low
    //

        //SPI_Options |= XSPIPS_CLK_ACTIVE_LOW_OPTION;
        SPI_Options &= ~XSPIPS_CLK_ACTIVE_LOW_OPTION;

    //
    // Set the clock phase to capture leading
    //

        //SPI_Options |= XSPIPS_CLK_PHASE_1_OPTION;
        SPI_Options &= ~XSPIPS_CLK_PHASE_1_OPTION;

    //
    // Set the SPI controller options
    //

    error = XSpiPs_SetOptions(&SpiInstance, SPI_Options);

    //
    // Set the SPI controller clock frequency
    //

    unsigned char prescaler;

    //prescaler = XSPIPS_CLK_PRESCALE_16;  // 8.92 MHZ
    prescaler = XSPIPS_CLK_PRESCALE_8; // 17.86 MHZ
    //prescaler = XSPIPS_CLK_PRESCALE_4; // 35.7 MHZ

    error = XSpiPs_SetClkPrescaler(&SpiInstance, prescaler);

    //
    // Enable the SPI controller
    //

    XSpiPs_Enable((&SpiInstance));
	xil_printf("%s SPI controller enable\r\n", __func__);

    return XST_SUCCESS;
}


unsigned int ReadRamStatus( unsigned int chip_sel )
{
		TransferParams Params;

	    WriteBuff[0] = READ_STATUS;

	    Params.Select = CS0;
	    Params.XferLength = 2;
	    Params.WriteSize = 1;
	    Params.WriteBuffer = WriteBuff;
	    Params.ReadSize = 1;
	    Params.ReadBuffer = ReadBuff;

	    RamPolledTransfer(&Params);

        if ((ReadBuff[1] & WRITE_ENABLE_LATCH) == WRITE_ENABLE_LATCH)
        	xil_printf("%s RAM Write enabled\r\n", __func__);
        else
        	xil_printf("%s RAM Write disabled\r\n", __func__);

	    return XST_SUCCESS;
}

unsigned int WriteRamEnable( unsigned int chip_sel )
{
	TransferParams Params;

    WriteBuff[0] = WRITE_ENABLE;

    Params.Select = CS0;
    Params.XferLength = 1;
    Params.WriteSize = 1;
    Params.WriteBuffer = WriteBuff;
    Params.ReadSize = 0;
    Params.ReadBuffer = ReadBuff;

    RamPolledTransfer(&Params);

    return XST_SUCCESS;
}

unsigned int WriteRamDisable( unsigned int chip_sel )
{
	TransferParams Params;

    WriteBuff[0] = WRITE_DISABLE;

    Params.Select = CS0;
    Params.XferLength = 1;
    Params.WriteSize = 1;
    Params.WriteBuffer = WriteBuff;
    Params.ReadSize = 0;
    Params.ReadBuffer = ReadBuff;

    RamPolledTransfer(&Params);

    return XST_SUCCESS;
}

unsigned int WriteRamBlockProtection( unsigned int chip_sel )
{
	TransferParams Params;

    WriteBuff[0] = WRITE_STATUS;
    WriteBuff[1] = 0;

    Params.Select = CS0;
    Params.XferLength = 2;
    Params.WriteSize = 2;
    Params.WriteBuffer = WriteBuff;
    Params.ReadSize = 0;
    Params.ReadBuffer = ReadBuff;

    RamPolledTransfer(&Params);

    return XST_SUCCESS;
}

unsigned int ReadRamData( unsigned int chip_sel,
		unsigned int rx_length,
		unsigned int read_address,
		unsigned char * rx_buffer)
{
	unsigned int error = XST_SUCCESS;

	    // Use one load of FIFO, single transfer only.
	    if( rx_length > 120 ) return XST_INVALID_PARAM;

		TransferParams Params;
	    WriteBuff[0] = READ_DATA;
	    WriteBuff[1] = (unsigned char)(read_address >> 16);
	    WriteBuff[2] = (unsigned char)(read_address >>  8);
	    WriteBuff[3] = (unsigned char)(read_address);

	    Params.Select = CS0;
	    Params.XferLength = 4 + rx_length;
	    Params.WriteSize = 4; // 4 byte command data
	    Params.WriteBuffer = WriteBuff;
	    Params.ReadSize = rx_length;
	    Params.ReadBuffer = ReadBuff;

	    // Begin Read operation
	    error = RamPolledTransfer(&Params);

	    // Copy working buffer to the user buffer, skip over command
	    memcpy((rx_buffer), &ReadBuff[4], rx_length);

	    return error;
}

unsigned int ReadRamWord( unsigned int chip_sel,
		unsigned int * read_word,
		unsigned int read_address)
{
	unsigned int error = XST_SUCCESS;
	unsigned int word = 0;

	    // Use one load of FIFO, single transfer only.
	    //if( rx_length > 120 ) return XST_INVALID_PARAM;

		TransferParams Params;
	    WriteBuff[0] = READ_DATA;
	    WriteBuff[1] = (unsigned char)(read_address >> 16);
	    WriteBuff[2] = (unsigned char)(read_address >>  8);
	    WriteBuff[3] = (unsigned char)(read_address);

	    Params.Select = CS0;
	    Params.XferLength = 4 + 4;
	    Params.WriteSize = 4; // 4 byte command data
	    Params.WriteBuffer = WriteBuff;
	    Params.ReadSize = 4;
	    Params.ReadBuffer = ReadBuff;

	    // Begin Read operation
	    error = RamPolledTransfer(&Params);

	    // Convert the 4 byte response to a word.
	    word  = ReadBuff[7] << 24;
	    word += ReadBuff[6] << 16;
	    word += ReadBuff[5] << 8;
	    word += ReadBuff[4];
	    *read_word = word;

	    return error;
}

unsigned int WriteRamData( unsigned int chip_sel,
		unsigned int tx_length,
		unsigned int write_address,
		unsigned char * tx_buffer)
{
	unsigned int error = XST_SUCCESS;

        // Use one load of FIFO, single transfer only.
        if( tx_length > 120 ) return XST_INVALID_PARAM;

		TransferParams Params;
	    WriteBuff[0] = WRITE_DATA;
	    WriteBuff[1] = (unsigned char)(write_address >> 16);
	    WriteBuff[2] = (unsigned char)(write_address >>  8);
	    WriteBuff[3] = (unsigned char)(write_address);

	    Params.Select = CS0;
	    Params.XferLength = 4 + tx_length;
	    Params.WriteSize = 4 + tx_length; // Command + data stream length
	    Params.WriteBuffer = WriteBuff;
	    Params.ReadSize = 0;
	    Params.ReadBuffer = ReadBuff;

	    // Append the user buffer to the working buffer, skip over command
	    memcpy(&WriteBuff[4], (tx_buffer),  tx_length);

	    // Begin Write operation
	    error = RamPolledTransfer(&Params);

	    return error;
}

unsigned int WriteRamWord( unsigned int chip_sel,
		unsigned int * write_word,
		unsigned int write_address)
{
	unsigned int error = XST_SUCCESS;
	unsigned int word = 0;

        // Use one load of FIFO, single transfer only.
        //if( tx_length > 120 ) return XST_INVALID_PARAM;

		TransferParams Params;
	    WriteBuff[0] = WRITE_DATA;
	    WriteBuff[1] = (unsigned char)(write_address >> 16);
	    WriteBuff[2] = (unsigned char)(write_address >>  8);
	    WriteBuff[3] = (unsigned char)(write_address);

	    Params.Select = CS0;
	    Params.XferLength = 4 + 4;
	    Params.WriteSize = 4 + 4; // Command + data stream length
	    Params.WriteBuffer = WriteBuff;
	    Params.ReadSize = 0;
	    Params.ReadBuffer = ReadBuff;

	    word = *write_word;
	    WriteBuff[4] = word & 0x0FF; word = word >> 8;
	    WriteBuff[5] = word & 0x0FF; word = word >> 8;
	    WriteBuff[6] = word & 0x0FF; word = word >> 8;
	    WriteBuff[7] = word & 0x0FF;

	    // Begin Write operation
	    error = RamPolledTransfer(&Params);

	    return error;
}

unsigned int RamPolledTransfer(TransferParams * Params)
{
	unsigned int error = XST_SUCCESS;

    error = XSpiPs_SetSlaveSelect(&SpiInstance, Params->Select);
	if (error != XST_SUCCESS) {
		return XST_FAILURE;
	}

    //
    // Initiate the SPI transfer in polled mode
    //
    error = XSpiPs_PolledTransfer(&SpiInstance, Params->WriteBuffer,
                                  Params->ReadBuffer, Params->XferLength);

	if (error != XST_SUCCESS) {
	    xil_printf("%s SPI Transfer failed!: %x\r\n", __func__, error);
	}

	return error;
}
