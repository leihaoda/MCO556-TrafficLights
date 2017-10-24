/*
    File      : keypad.c
    Project   : MCO556
    Author    : G. VandeBelt
    Created   : 2012/02/24

    The keypad interfaces to the EVB board via PORT A.  The keypad is a 4 x 4 matrix.
    The keypad driver is designed as a state machine that is run every 10 ms.  Timer 2 Channel 3
    is used in compare mode to generate a 10 ms interrupt.  The state machine drives the rows
    LOW one at a time and checks the columns.  If any column is LOW, the contact is de-bounced.

  Resources used:
    Rows    - PORT A.4 - A.7
    Columns - PORT A.0 - A.3
    Timer 2 Channel 3
    Timer clock must be 2.5 MHz for proper operation

    Driver functions:
      KPopen     initialize keypad driver
      KPhit      check for new key press: = 0 no new press
      KPgetch    waits for new key press and returns ASCII code for the key
      KPflush    discards any key press
      KPstatus   returns status of keypad driver

*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"     /* derivative information */
#include "keypad.h"

#define INTERVAL ((unsigned int)(10*20000L/8))	// 10ms delay with 8 prescale
												// # of clocks = (10 ms * bus clock/8)


//  Variables local to file
//
// locate static and global variables on zero page for speed
#pragma DATA_SEG __SHORT_SEG  _DATA_ZEROPAGE
static volatile unsigned char keypress;   // keycode and flags
/*          bit 7     : key down  : 1 = any key pressed
            bit 6     : key press : 1 = new key has been pressed
            bit 5,4   : unused
            bit 3 - 0 : key code
 */
static unsigned char row;      // scan row: 0 - 3
static unsigned char col;      // column detect: 0 - 3
static unsigned char KeyState; // machine state
enum { SCAN, DEB_PRESS, PRESSED, DEB_RELEASE};  // Keypad machine states

#pragma DATA_SEG DEFAULT

//
//  Look-up table to convert keycode to ASCII code
const char KPtable[] = {
	'1',
	'2',
	'3',
	KP_A,     // A
	'4',
	'5',
	'6',
	KP_B,     // B
	'7',
	'8',
	'9',
	KP_C,     // C
	KP_STAR,  // *
	'0',
	KP_NUM,   // #
	KP_D      // D

};

/******************************************************************

  Driver functions

      KPopen
      KPhit
      KPgetch
      KPflush
      KPstatus
*/

//  KPhit
//
//  Check for new keypress
//    Return 0 if no new keypress
//
char KPhit(void)
{
	return (keypress & 0x40);  // check the keypress flag
}

//      KPstatus
//
//  Get keypad status
//    Return value of keypress
//
unsigned char KPstatus(void)
{
	return (keypress);  // return status
}

//      KPgetch
//
//  Wait for new keypress
//
//    Return ASCII code for the key
//
char KPgetch(void)
{
	while (!(keypress & 0x40))  ;  // wait for keypress

	keypress &= ~0x40;             // clear keypress flag
	return KPtable[keypress&0x0F]; // translate keypress to ASCII code
}

//      KPflush
//
//  Flush the keypad interface - discard any keypress
//
void KPflush(void)
{
	keypress &= ~0x40;            // clear the keypress flag
}

//      KPopen
//
//  Initialize the keypad driver
//	  Note: TPM prescale factor must be set to 8 in main
//   	1) Initialize PORT A pins
//   	2) Initialize Timer 2 channel 3
//   	3) Initialize state machine
//
void KPopen(void)
{
  // lower 4 bits of Port A detect the column inputs
  PTADD = 0x10;    // all pins input except row 0
  PTAD = 0x00;    // pins low when used as outputs

  // initialize timer 2 channel 3 for compare mode, no output, 10ms interval
  TPM2C3SC = 0x10;      // set software for compare mode
  TPM2C3V = TPM2CNT + INTERVAL; // compare in 10 ms
  TPM2C3SC_CH3IE = 1;   // enable timer interrupt
  TPM2C3SC_CH3F = 0;   // clear interrupt flag

  KeyState = SCAN;
  row = 0;
  keypress = 0; // no keypress
}

/*************************************************************************

  Interrupt driven state machine for Keypad Driver

 *************************************************************************/

// This table converts column contacts to ground into column number
//
//  No contact to ground        -- code = 4
//  Single contact to ground    -- code = 0 - 3 : value is the column number
//  Multiple contacts to ground -- code = F

const unsigned char ColTable[] = {
      0x04,     // 0000 :no column at ground
      0x00,     // 0001 :column 0 selected
      0x01,     // 0010 :column 1 selected
      0x0F,     // 0011 :multiple columns selected
      0x02,     // 0100 :column 2 selected
      0x0F,     // 0101 :multiple columns selected
      0x0F,     // 0110 :multiple columns selected
      0x0F,     // 0111 :multiple columns selected
      0x03,     // 1000 :column 3 selected
      0x0F,     // 1001 :multiple columns selected
      0x0F,     // 1010 :multiple columns selected
      0x0F,     // 1011 :multiple columns selected
      0x0F,     // 1100 :multiple columns selected
      0x0F,     // 1101 :multiple columns selected
      0x0F,     // 1110 :multiple columns selected
      0x0F      // 1111 :multiple columns selected
};

//
//  Interrupt driven keypad state machine
//
interrupt void KPisr(void)
{
  unsigned char x;

  TPM2C3SC_CH3F = 0;   // clear interrupt flag
  TPM2C3V = TPM2C3V + INTERVAL; // compare in 10 ms

  x = (~PTAD) & 0x0F;    // get column info in lower digit
  x &= 0x0F;      // mask upper digit
  switch (KeyState) {
    case SCAN:           // scanning for key press
      col = ColTable[x];
      if (col < 4) {
        KeyState = DEB_PRESS;  // debounce the press
      } else if (col == 4) {
        if (row < 3) {      // no press - continue the scan
          row++;
          PTADD <<= 1;
        } else {
          row = 0;          // scan row 0
          PTADD = 0x10;
        }
      }
      break;

    case DEB_PRESS:   // debouncing a keypress
      if ( col == ColTable[x]) { // check row - column connection
        KeyState = PRESSED;       // good key press
        keypress = 0xC0 + (row << 2) + col;
      } else {       // column data has changed - bounce or roll over
        KeyState = SCAN;  // continue scanning
      }
      break;

    case PRESSED:     // waiting for key release
      if ( (x & (1 << col)) == 0) { // check if key still pressed
        KeyState = DEB_RELEASE;  // key released
        keypress &= 0x7f;     // clear key down flag
      }
      break;

    case DEB_RELEASE:   // debouncing a key release
      KeyState = SCAN;  // start scanning for next key press
      row = 0;
      PTADD = 0x10;
      break;

    default:            // serious problem
      keypress = 0;
      KeyState = SCAN;  // restart scan from row 0
      row = 0;
      PTADD = 0x10;
      break;
  }
}
