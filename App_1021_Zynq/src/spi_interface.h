//============================================================================
// Name        : spi_interface.h
// Author      : Roger Dickerson
// Version     : 2021
// Copyright   : MIT License
// Description : Xilinx SPI setup and NVRAM Read/Write operations.
//============================================================================


#define   WRITE_STATUS            (unsigned char)0x01
#define   WRITE_DATA              (unsigned char)0x02
#define   READ_DATA               (unsigned char)0x03
#define   WRITE_DISABLE           (unsigned char)0x04
#define   READ_STATUS             (unsigned char)0x05
#define   WRITE_ENABLE            (unsigned char)0x06

#define   WRITE_ENABLE_LATCH      (unsigned char)0x02

//        static const byte   WRITE_STATUS            = 0x01;
//        static const byte   WRITE_DATA              = 0x02;
//        static const byte   READ_DATA               = 0x03;
//        static const byte   READ_STATUS             = 0x05;
//        static const byte   WRITE_ENABLE            = 0x06;

//        static const byte   WRITE_ENABLE_LATCH      = 0x02;

//        static const ushort COMMAND_OFFSET          = 0;        // NVram command number
//        static const ushort ADDRESS_1_OFFSET        = 1;        // MSB byte of address
//        static const ushort ADDRESS_2_OFFSET        = 2;        // Middle byte of address
//        static const ushort ADDRESS_3_OFFSET        = 3;        // LSB byte of address

//        static const ushort ONE_BYTE_COMMAND        = 1;        // Sends one transmit byte
//        static const ushort TWO_BYTE_COMMAND        = 2;        // Sends two transmit bytes
//        static const ushort THREE_BYTE_COMMAND      = 3;        // Sends three transmit bytes
//        static const ushort FOUR_BYTE_COMMAND       = 4;        // Sends four transmit bytes


unsigned int NVRAM_Test1();

unsigned int init_spi0_dev();

unsigned int ReadRamStatus( unsigned int chip_sel );
unsigned int WriteRamEnable( unsigned int chip_sel );
unsigned int WriteRamDisable( unsigned int chip_sel );
unsigned int WriteRamBlockProtection( unsigned int chip_sel );

unsigned int WriteRamData( unsigned int chip_sel,
		unsigned int tx_length,
		unsigned int write_address,
		unsigned char * tx_buffer);
unsigned int WriteRamWord( unsigned int chip_sel,
		unsigned int * write_word,
		unsigned int write_address);

unsigned int ReadRamData( unsigned int chip_sel,
		unsigned int rx_length,
		unsigned int read_address,
		unsigned char * rx_buffer);
unsigned int ReadRamWord( unsigned int chip_sel,
		unsigned int * read_word,
		unsigned int read_address);

typedef enum
{
	CS0 = 0,
	CS1 = 1
} ChipSelect;

typedef struct TransferParams_s
{
    ChipSelect   Select;
    unsigned int XferLength;      // Total operation stream byte length, command + data
    unsigned int TransferType;    // NVRAM transfer type
    unsigned char * WriteBuffer;  // Write buffer pointer
    unsigned int WriteSize;       // Write data length to store
    unsigned char * ReadBuffer;   // Read buffer pointer
    unsigned int ReadSize;        // Read data length to retrieve
} TransferParams;

unsigned int RamPolledTransfer(TransferParams * Params);

