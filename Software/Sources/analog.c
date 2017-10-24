/*
    Project : MCO556 Drivers
    File    : analog.c
    Author  : G. VandeBelt
    Date    : 2012/03/19

  This file contains the driver for the analog features of the
  DE1 plus interface boards. The driver uses the SPI module to
  interface to the DAC and ADC chips on the interface board.
    The DAC operation operates at 10 Mb/s with no interrupts.  The
  ADC operates at ~713kb/s and can be configured for interrupt or
  non-interrupt operation.  All transfers require 16 clock pulses.
    Since both the SPI transmitter and receiver are double buffered,
  transfers are initiated by two successive writes to the transmit
  buffer.  To ensure that the SPI slave select line (SS) is active
  for the entire 16 bit transfer, interrupts are disabled betwwn the
  two writes.
    For ADC operation, the data written to the ADC is all 1's. If
  ADC interrupts are enabled, the function ADCstart is called to
  initiate the transfer.  This will generate 2 SPI Rx interrupts.  The
  SPI ISR will set a flag (SPIrxDone) indicating that a sample is available.
  The software can read the results by calling the function ADCgetSample.
  If ADC interrupts have not been enabled, the transfer is initiated by
  calling ADCgetSample.  The function waits until the transfer is complete
  and returns the sample.

 */
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"	 /* derivative information */
#include "analog.h"     // function prototypes for analog driver


#define SPI1C1_init (0b01011110)
//                     ||||||||
//                     |||||||+--  LSBFE  - MSB first
//                     ||||||+---  SSOE   - Automatic SS output
//                     |||||+----  CPHA   - sample on rising edge
//                     ||||+-----  CPOL   - clock idles high
//                     |||+------  MSTR   - master mode
//                     ||+-------  SPTIE  - no Rx interrupts
//                     |+--------  SPE    - module enabled
//                     +---------  SPIE   - no Rx interrupts
#define SPI1C2_init (0b00010000)
//                     ||||||||
//                     |||||||+--  CPC0    	- separate pins for in and output
//                     ||||||+---  SPISWAI 	- clocks continue in wait
//                     |||||+----  0      	- unused
//                     ||||+-----  BIDIROE	- 0 -
//                     |||+------  MODFEN 	- Automatic SS output
//                     ||+-------  DEVSEL0  - 00 = ADC channel 0	01 = ADC channel 1
//                     |+--------  DEVSEL1	- 10 = DAC channels		11 = external SPI dev1ce
//                     +---------  0      	- unused

// locate ADC control on page zero
#pragma DATA_SEG __SHORT_SEG  _DATA_ZEROPAGE
static unsigned char  SPIflags;
#define SPIRxInt  0x10	// SPI interrupt operation enabled
#define SPIdac		0x01		// SPI dac
#define SPIadc		0x02		// SPI used by adc
#define SPIext		0x04		// SPI used by external device
#define SPIsecond	0x40		// SPI waiting for second interrupt
#define SPIrxDone	0x80		// SPI receive done

static union		// simple way to access results as char and int
{
        unsigned int w;		// int
        unsigned char b[2];	// 2 char
} ADCdata;			// ADC conversion result from interrupt
#pragma DATA_SEG DEFAULT

#define ADCdataH  	ADCdata.b[0]	// high byte of result
#define ADCdataL 	ADCdata.b[1] 	// low byte of result
#define ADCdataW 	ADCdata.w		// result as a word

	// save current interrupt status and disable interrupts
	// 		copy CCR to A
	//		save on stack
	// 		disable interrupts
#define	SnDInterrupts	  __asm TPA; __asm PSHA; __asm SEI
	// restore interrupt status
	//		restore status to A
	//		copy A to CCR
#define	RestoreInterrupts	__asm PULA; __asm TAP;

//
//	Configure SPI module
//
//	Set Baud rate to 10 MHz
//
//
void ANALOGopen(unsigned char RxIntEna)
{
	PTEDD = 0x00;		// set PTE pins as inputs - can be read
	SPI1BR = 0;			// 10 MHz - bus clock / 2
	SPI1C2 = SPI1C2_init;
	SPI1C1 = SPI1C1_init;
	if (RxIntEna) SPIflags = SPIRxInt;	// ADC interrupts
	else SPIflags = 0;
}

//
//	DAC operation (SPI may be interrupt driven for ADC)
//
void DACputSample(char chan, int sample)
{
	unsigned char x;

	if (SPIflags & SPIadc)		// SPI in use by ADC?
		return;

// wait for any previous transaction to complete
	while ((PTED & 0xC6) != 0xC6) {}	// wait for SPI idle - all SS lines HIGH

// clear SPI receive buffer
	while (SPI1S_SPRF) x = SPI1D;

//	configure SPI for DAC transfer
	SPI1BR = 0x00;		// 10 MHz - bus clock / 2
	SPI1C1_SPIE = 0;					// disable - Rx interrupts
	SPI1C2 = SPI1C2_init | (2 << 6) ;	// select DAC device - Rx interrupts

	x = 0x0F & (sample >> 8);
	if (chan == 0)
		x |= 0x70;	// ch A, buffered, gain = 1, active mode
	else
		x |= 0xF0;	// ch B, buffered, gain = 1, active mode
	while (!SPI1S_SPTEF) ;		// wait for Tx empty
    SnDInterrupts;		// no interrupts between byte transfers
	SPI1D = x;					// send MSB
	while (!SPI1S_SPTEF) ;		// wait for Tx empty
	SPI1D = sample & 0xFF;		// send LSB
    RestoreInterrupts;
}

/*
	Start ADC conversion - used only in interrupt mode
*/
void ADCstart(char chan)
{   register char Pflags;

	while ((PTED & 0xC6) != 0xC6) {}	// wait for SPI idle - all SS lines HIGH

  if (!(SPIflags & SPIRxInt)) return;   // not in interrupt mode
// clear SPI receive buffer
	while (SPI1S_SPRF) Pflags = SPI1D;

//	configure SPI for ADC transfer
 	SPIflags = SPIadc | SPIRxInt ;	// mark SPI used by ADC using interrupts
	SPI1C1_SPIE = 1;		// enable - Rx interrupts
	SPI1BR = 0x61;				// 714 kHz - bus clock / 28
	if (chan == 0)
		SPI1C2 = SPI1C2_init;				// select ADC0
	else
		SPI1C2 = SPI1C2_init | (1 << 6);	// select ADC 1

// start the 16 bit transfer
    SnDInterrupts;	// no interrupts between byte transfers
	SPI1D = 0xFF;			// first byte
	while (!SPI1S_SPTEF) ;	// wait for Tx empty
	SPI1D = 0xFF;			// second byte
	RestoreInterrupts;
	ADCdataW = 0;			// clear ADC result
}

unsigned char ADCgetSample(char chan, unsigned int *sample)
{
	unsigned int x;

	while ((PTED & 0xC6) != 0xC6) {}	// wait for SPI idle - all SS lines HIGH

	if (SPIflags & SPIRxInt) {
	// ADC interrupt operation
        if (!(SPIflags & SPIrxDone)) return 0;  // no new data
		SPIflags = SPIRxInt;				// clear ADC flags
    *sample = ADCdataW ;     	  // return sample
		return 1;			              // valid data
	}
// non-interrupt operation

// clear SPI receive buffer
	while (SPI1S_SPRF) x = SPI1D;

//	configure SPI for ADC transfer
	SPI1BR = 0x61;				// 714 kHz - bus clock / 28
	if (chan == 0)
		SPI1C2 = SPI1C2_init;				// select ADC0
	else
		SPI1C2 = SPI1C2_init | (1 << 6);	// select ADC 1
	SPI1C1_SPIE = 0;			// disable - Rx interrupts

// start the 16 bit transfer
	SnDInterrupts;		// no interrupts between byte transfers
	SPI1D = 0xFF;				// first byte
	while (!SPI1S_SPTEF) ;		// wait for Tx empty
	SPI1D = 0xFF;				// second byte
	RestoreInterrupts;
	while (!SPI1S_SPRF) ;		// wait for Rx full
	x = (SPI1D & 0x1F) << 8;

	while (!SPI1S_SPRF) ;		// wait for Rx full
	x |= SPI1D;
	x >>= 1;
	SPIflags = 0;
    *sample = x;
	return 1;
}

//
//		SPI receive interrupt for ADC and DAC operation
//
interrupt void SPIisr(void)
{
	unsigned char x;

	x = SPI1S;		// read status
	x = SPI1D;		// get data and clear interrupt
	if (SPIflags & SPIsecond) {
		SPI1C1_SPIE = 0;	// disable interrupts
		ADCdataL = x;
		ADCdataW >>= 1;
		SPIflags &= ~SPIadc;	// clear SPI in use by ADC
		SPIflags |= SPIrxDone;
	} else {
		SPIflags |= SPIsecond; // set waiting for first byte
		ADCdataH = x & 0x1F;
	}
}