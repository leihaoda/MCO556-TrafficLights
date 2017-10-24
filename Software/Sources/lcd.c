/*
    File      : lcd.c
    Project   : MCO556
    Author    : G. VandeBelt
    Created   : 2012/01/09
    Modified  : 2013/06/26  - delay interrupts until configuration complete

  This file contains LCD driver functions required
  for interfacing to a character LCD display in 8 bit mode.
  The LCD data bits are connected to Port B.  The R/W RS
  and E are on Port C.

  The driver is interrupt driven.  The driver uses Timer 2
  Channel 4 in compare mode.  The driver has a 128 byte circular
  buffer into which the software writes all data and commands.
  The Timer interrupt is then enabled.

  The Timer ISR reads the data from the buffer and outputs the
  data to the LCD and restarts the Timer.  When the buffer is
  empty, the Timer interrupt is disabled.

  Instructions are sent to the LCD via an escape sequnce.  All
  instructions are preceded by a 0xFE byte.  The ISR detects and
  discards this byte and reads the next byte as the instruction.

  LCD connection to microcontroller:
    Data - Port B
    RS   - Port C pin 4
    R/W  - Port C pin 5
    EN   - Port C pin 6
  RS R/W must be valid before the rising edge of EN.
  Dn must be valid before the falling edge of EN
  RS R/W and Dn must be held stable after the falling edge of EN.

  The BSY bit of the LCD is not read, so the driver must ensure
  that the processing time for commands is met.  This is done by
  using the Compare Time 2 channel 4.  After every transfer, the
  compare timer is started.  The duration depends on the command.

  Functions:
    LCDopen     - initialize the LCD
    LCDinstruct - output an instruction to the LCD    (MACRO)
    LCDputch    - output a data character to the LCD  (MACRO)
    LCDputbyte  - output a data/instruction to the LCD
    LCDputs     - output a string to the LCD
    LCDline		- move cursor to beginning of line
    LCDclear	- clear screen or line

*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* include peripheral declarations */
#include "lcd.h"

// timer delays with divide by 8 prescaler
#define DLY15ms   ((unsigned int)((15*20000L)/8))	  // 15 ms delay with 8 prescale
#define DLY5ms    ((unsigned int)((5*20000L)/8))	  // 5 ms delay with 8 prescale
#define DLY2ms    ((unsigned int)((4*20000L)/8))	  // 2 ms delay with 8 prescale
                                  // actually 4 ms for old slow LCDs
#define DLY100us  ((unsigned int)((100*20000L)/8000)) // 100 us
#define DLY40us   ((unsigned int)((100*20000L)/8000))  // 40 us
                                  // actually 100 us for old slow LCDs

#define LCDcfg      (0b00111000)  // Function set
//                     ||||||||
//                     |||||||+--  x      - unused
//                     ||||||+---  x      - unused
//                     |||||+----  F      - 5x7 dots
//                     ||||+-----  N      - 2/4 lines
//                     |||+------  DL     - 8 bit interface
//                     ||+-------  1      - function set
//                     |+--------  0      - set CG RAM address
//                     +---------  0      - set data RAM address

#define LCDmode     (0b00000110)  // Entry mode
//                     ||||||||
//                     |||||||+--  S      - no display shift
//                     ||||||+---  I/D    - Increment address
//                     |||||+----  1      - mode
//                     ||||+-----  0      - display
//                     |||+------  0      - shift
//                     ||+-------  0      - function set
//                     |+--------  0      - set CG RAM address
//                     +---------  0      - set data RAM address

// locate buffer indexes on zero page for speed
#pragma DATA_SEG __SHORT_SEG  _DATA_ZEROPAGE
static unsigned char  LCDput;
static unsigned char  LCDtake;
#pragma DATA_SEG DEFAULT

#define LcdRS     PTCD_PTCD4   // RS pin for LCD  : PORT C.4
#define LcdRnW    PTCD_PTCD5   // R/W pin for LCD : PORT C.5
#define LcdEN     PTCD_PTCD6   // EN pin for LCD  : PORT C.6
#define LcdData   PTBD         // data lines      : PORT B
#define LcdDir    PTBDD        // data direction

#define LCDsize   128         // 128 byte buffer
static unsigned char  LCDbuf[LCDsize];

static void initcmd(unsigned char cmd, unsigned int delay);

//
//  LCDopen
//
//  Initialize the LCD display following a power on reset.
//  The algorithm is taken from the OPTREX User's Manual.
//
void LCDopen(void)
{
  LCDput = 0;    // FIFO pointers
  LCDtake = 0;

  // set up Port B and Port C
  LcdData = 0xFF;
  PTCD &= 0x8F;   // default to write, instruction, E low

  LcdDir = 0xFF;          // set direction to output
  PTCDD |= 0x70;

  // 1) 15 ms delay after power-on
  TPM2C4V = TPM2CNT + DLY15ms;
  TPM2C4SC = 0x10;            // set software compare mode for ch1

  // 2) function set command
  initcmd(LCDcfg, DLY5ms); // function set - > 4.1 ms delay

  // 3) function set command
  initcmd(LCDcfg, DLY100us); // function set - > 100us delay

  // 4) function set command
  initcmd(LCDcfg, DLY40us); // function set - > 40us delay

  // LCD reset complete - now configure the LCD interface width
  initcmd(LCDcfg, DLY40us); // function set - > 40us delay

  // do not use the normal LCD commands to complete the configuration
  //  programmer may clear the screen - flushes the buffer

  initcmd(LCDcfg, DLY40us);       // the real function set
  initcmd(LCDdsplyOFF, DLY40us);  // display OFF
  initcmd(0x01,DLY2ms);	          // clear display
  initcmd(LCDmode, DLY40us);      // set mode
  initcmd(LCDcursorON, DLY40us);  // display ON - cursor ON
  // display now configured - can use interrupts
}

static void initcmd(unsigned char cmd, unsigned int delay)
{
  while (!TPM2C4SC_CH4F) ;  // wait for previous command to complete

  LcdEN = 1;          // EN set HIGH
  LcdData = cmd;      // output the command
  LcdEN = 0;          // EN is now LOW

  TPM2C4V = TPM2CNT + delay;
  TPM2C4SC_CH4F = 0;        // clear time-out flag

}

//
//  LCDputbyte
//
//  This function sends a byte to the LCD.  The "type"
//  defines the data is instructions or display character
//  Procedure:
//    1) if type is non-zero, insert 0xFE into FIFO to signal instruction
//    2) insert data into FIFO
//    3) disable interrupts
//    4) advance FIFO pointer
//    5) enable Timer interrupt
//    6) enable interrupts
//
void LCDputbyte(unsigned char data, unsigned char type)
{
  byte  idx;

  idx = LCDput;
  if (type)
  {
    LCDbuf[idx] = 0xFE;     // flag instruction
    if (idx == LCDsize - 1) idx = 0;
    else idx++;
    if (idx == LCDtake) return;   // FIFO is full
  }
  LCDbuf[idx] = data;     // send data
  if (idx == LCDsize - 1) idx = 0;
  else idx++;
  if (idx == LCDtake) return;   // FIFO is full
  LCDput = idx;

  TPM2C4SC_CH4IE = 1;   // LCD active
}
//
//  LCDputs
//
//  This function outputs a NULL terminated string to
//  the LCD display.  The function does NOT handle line
//  wrapping.
//

void LCDputs(const unsigned char *s)
{

  for ( ;*s != 0; s++)
    LCDputch(*s);

}

/*
   Interrupt routine for LCD.

 */
interrupt void LCDisr(void)
{
  unsigned char data;

  // first check for more data to display
  if (LCDtake == LCDput)
  {
    // FIFO is empty
    //  disable interrupts but DON'T clear the flag
    TPM2C4SC_CH4IE = 0;   // LCD inactive
    return;
  }

  data = LCDbuf[LCDtake]; // get data
  if (data == 0xFE)
  {
    // this is an instruction
    if (LCDtake == LCDsize - 1) LCDtake = 0; // handle wrapping
    else LCDtake++;
    data = LCDbuf[LCDtake]; // get instruction
    LcdRS = 0;
  } else LcdRS = 1;
  LcdEN = 1;          // EN set HIGH
  LcdData = data;       // output the byte
  LcdEN = 0;          // EN is now LOW

  // start the delay timer
  if ((LcdRS == 0) && (data < 4))
  {
    // CLEAR or HOME instruction
    TPM2C4V = TPM2CNT + DLY2ms;
  }
  else TPM2C4V = TPM2CNT + DLY40us;

  TPM2C4SC_CH4F = 0;      // clear interrupt flag

  if (LCDtake == LCDsize - 1) LCDtake = 0; // handle wrapping
  else LCDtake++;
}

// Look up table to convert line number to cursor location
static const char LineCode[5] =
{
    0x02,     // home
    0x80,     // cursor at beginning of line 1
    0xC0,     // cursor at beginning of line 2
    0x90,     // cursor at beginning of line 3
    0xD0,     // cursor at beginning of line 4
};

//
//  Clear LCD line or entire display
//
//
void LCDclear(unsigned char Line)
{
  char code;

  if (Line > 4) Line = 0;
  code = LineCode[Line];		// convert line number to cursor location
  if (code == 2)
  { // clear display
    TPM2C4SC_CH4IE = 0;			// disable LCD interrupts
    LCDput = 0;                 // flush the buffer
    LCDtake = 0;
    code = 0x01;				// clear screen code
  } else
  {
    LCDinstruct(code);           // move to start of line
    LCDputs("                ");    // blank the line - output 16 spaces
  }
  LCDinstruct(code);           // move to start of line  or  clear screen
}

//
//    Move cursor to start of line
//
void LCDline(unsigned char Line)
{
  char code;

  if (Line > 4) Line = 0;
  code = LineCode[Line];       // convert Line to cursor location
  LCDinstruct(code);
}

