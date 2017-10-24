#ifndef LCD_H
#define LCD_H
 /*
    File      : lcd.h
    Project   : ECT9S08
    Author    : G. VandeBelt
    Created   : 2012/02/04

   This file contains the macros and function protypes

 */
#define LCDdsplyOFF 0x08        // display OFF command
#define LCDdsplyON  0x0C        // display ON, cursor OFF
#define LCDcursorOFF 0x0C       // display ON, cursor OFF
#define LCDcursorON 0x0E        // display ON, cursor ON
#define LCDblink    0x0F        // display ON, cursor blink
#define LCDshiftR   0x14        // shift cursor right
#define LCDshiftL   0x10        // shift cursor left


extern void LCDopen(void);
extern void LCDputs(const unsigned char *s);
extern void LCDputbyte(unsigned char data, unsigned char type);
extern void LCDclear(unsigned char Line);
extern void LCDline(unsigned char Line);

#define LCDputch(x)     LCDputbyte(x, 0)
#define LCDinstruct(x)  LCDputbyte(x, 1)

#define LCDhome()	  LCDputbyte(0x02, 1)		// move cursor to home position

#endif  // LCD_H