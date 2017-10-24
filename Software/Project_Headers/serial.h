#ifndef SERIAL_H
#define SERIAL_H

#define EnaRxInt  1

extern void SCI2open (unsigned int Baud, char EnaInt);		// configure SCI
extern void SCI2putch(unsigned char Data);
extern unsigned char SCI2getch(void);
extern void SCI2puts(char *s);

#endif  // SERIAL_H
