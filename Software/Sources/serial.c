/*
    File      : serial.c
    Project   : MCO556
    Author    : G. VandeBelt
    Created   : 2012/02/24

	These are the serial communications functions for the  
	
	
	*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"	 /* derivative information */
#include "serial.h"

// Initialize SCI2
//
//	Arguments:	Baud rate, Enable receive interrupt flag
void SCI2open (unsigned int Baud, char EnaInt)		// configure SCI
{

    // Calculate baud rate divisor  Divisor = bus clock/(16 * baud rate)
    SCI2BD= ((20000000L/16)/Baud) & 0xFFFF;	// 20 MHz is Bus clock
    if (EnaInt)
        SCI2C2=0x2C;	// enable Rx, Tx & Rx interrupt  - other registers left in default
    else
        SCI2C2=0x0C;	// enable Rx & Tx - other registers leftin default
}

//  Output a character
//
//	Argument:	character to send
void SCI2putch(unsigned char Data)
{
	while (SCI2S1_TDRE == 0) ; 	/* Wait for TDRE to be set */
	SCI2D=Data; 			/* then output */
}

//   Get a character
//
//	Returns received character
unsigned char SCI2getch(void)
{
	while(!SCI2S1_RDRF) ; 		/* Wait for RDRF to be set */
	return SCI2D;			// get recived character
}

// Output a string
//
//	Argument:	pointer to string
void SCI2puts(char *s)
{
  while (*s)		// loop until NULL character
    SCI2putch(*s++);  // output the character - advance pointer
}

