#ifndef KEYPAD_H
#define KEYPAD_H

// define values for special keys
#define KP_A		'A'
#define KP_B		'B'
#define KP_C		'C'
#define KP_D		'D'
#define KP_STAR	'*'
#define KP_NUM	'#'

extern void KPopen(void);
extern char KPhit(void);
extern char KPgetch(void);
extern void KPflush(void);
extern char KPstatus(void);
extern char KPisdown(void);


#endif    // KEYPAD_H