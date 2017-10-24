
/* Based on CPU DB MC9S08GB60, version 2.87.208 (RegistersPrg V2.28) */
/*
** ###################################################################
**     Filename  : mc9s08gb32.h
**     Processor : MC9S08GB32CFU
**     FileFormat: V2.28
**     DataSheet : MC9S08GB60/D Rev. 2.3 12/2004
**     Compiler  : CodeWarrior compiler
**     Date/Time : 27.5.2009, 10:26
**     Abstract  :
**         This header implements the mapping of I/O devices.
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
**
**     CPU Registers Revisions:
**      - 11.04.2006, V2.87.174:
**              - Renamed bits IIC1A_ADDR0..6 ==> IIC1A_ADDR1..7 REASON: Bug-fix (#3047 in Issue Manager)
**
**     File-Format-Revisions:
**      - 14.11.2005, V2.00 :
**               - Deprecated symbols added for backward compatibility (section at the end of this file)
**      - 15.11.2005, V2.01 :
**               - Changes have not affected this file (because they are related to another family)
**      - 17.12.2005, V2.02 :
**               - Arrays (symbols xx_ARR) are defined as pointer to volatile, see issue #2778
**      - 16.01.2006, V2.03 :
**               - Fixed declaration of non volatile registers. Now it does not require (but allows) their initialization, see issue #2920.
**               - "volatile" modifier removed from declaration of non volatile registers (that contain modifier "const")
**      - 08.03.2006, V2.04 :
**               - Support for bit(s) names duplicated with any register name in .h header files
**      - 24.03.2006, V2.05 :
**               - Changes have not affected this file (because they are related to another family)
**      - 26.04.2006, V2.06 :
**               - Absolute assembly supported (depreciated symbols are not defined)
**      - 27.04.2006, V2.07 :
**               - Fixed macro __RESET_WATCHDOG for HCS12, HCS12X ,HCS08 DZ and HCS08 EN derivatives (write 0x55,0xAA).
**      - 07.06.2006, V2.08 :
**               - For .inc files added constants "RAMStart" and "RAMEnd" even there is only Z_RAM.
**      - 03.07.2006, V2.09 :
**               - Flash commands constants supported
**      - 27.10.2006, V2.10 :
**               - __RESET_WATCHDOG improved formating and re-definition
**      - 23.11.2006, V2.11 :
**               - Changes have not affected this file (because they are related to another family)
**      - 22.01.2007, V2.12 :
**               - Changes have not affected this file (because they are related to another family)
**      - 01.03.2007, V2.13 :
**               - Flash commands constants values converted to HEX format
**      - 02.03.2007, V2.14 :
**               - Interrupt vector numbers added into .H, see VectorNumber_*
**      - 26.03.2007, V2.15 :
**               - Changes have not affected this file (because they are related to another family)
**      - 10.05.2007, V2.16 :
**               - Fixed flash commands definition for ColdFireV1 assembler (equ -> .equ)
**      - 05.06.2007, V2.17 :
**               - Changes have not affected this file (because they are related to another family)
**      - 19.07.2007, V2.18 :
**               - Improved number of blanked lines inside register structures
**      - 06.08.2007, V2.19 :
**               - CPUDB revisions generated ahead of the file-format revisions.
**      - 11.09.2007, V2.20 :
**               - Added comment about initialization of unbonded pins.
**      - 02.01.2008, V2.21 :
**               - Changes have not affected this file (because they are related to another family)
**      - 13.02.2008, V2.22 :
**               - Changes have not affected this file (because they are related to another family)
**      - 20.02.2008, V2.23 :
**               - Changes have not affected this file (because they are related to another family)
**      - 03.07.2008, V2.24 :
**               - Added support for bits with name starting with number (like "1HZ")
**      - 28.11.2008, V2.25 :
**               - StandBy RAM array declaration for ANSI-C added
**      - 1.12.2008, V2.26 :
**               - Duplication of bit (or bit-group) name with register name is not marked as a problem, is register is internal only and it is not displayed in I/O map.
**      - 17.3.2009, V2.27 :
**               - Merged bit-group is not generated, if the name matchs with anouther bit name in the register
**      - 6.4.2009, V2.28 :
**               - Fixed generation of merged bits for bit-groups with a digit at the end, if group-name is defined in CPUDB
**
**     Not all general-purpose I/O pins are available on all packages or on all mask sets of a specific
**     derivative device. To avoid extra current drain from floating input pins, the user’s reset
**     initialization routine in the application program must either enable on-chip pull-up devices
**     or change the direction of unconnected pins to outputs so the pins do not float.
** ###################################################################
*/

#ifndef _MC9S08GB32_H
#define _MC9S08GB32_H


/*lint -save  -e950 -esym(960,18.4) -e46 -esym(961,19.7) Disable MISRA rule (1.1,18.4,6.4,19.7) checking. */
/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];

/* Watchdog reset macro */
#ifndef __RESET_WATCHDOG
#ifdef _lint
  #define __RESET_WATCHDOG()  /* empty */
#else
  #define __RESET_WATCHDOG() {asm sta SRS;}
#endif
#endif /* __RESET_WATCHDOG */

#define REG_BASE 0x0000                /* Base address for the I/O register block */


#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

/**************** interrupt vector numbers ****************/
#define VectorNumber_Vfir               27U
//#define VectorNumber_Vlcd               26U
#define VectorNumber_Vrti               25U
#define VectorNumber_Viic1              24U
//#define VectorNumber_Vatd1              23U
#define VectorNumber_Vkeyboard1         22U
#define VectorNumber_Vsci2tx            21U
#define VectorNumber_Vsci2rx            20U
#define VectorNumber_Vsci2err           19U
#define VectorNumber_Vsci1tx            18U
#define VectorNumber_Vsci1rx            17U
#define VectorNumber_Vsci1err           16U
#define VectorNumber_Vspi1              15U
#define VectorNumber_Vtpm2ovf           14U
#define VectorNumber_Vtpm2ch4           13U
#define VectorNumber_Vtpm2ch3           12U
#define VectorNumber_Vtpm2ch2           11U
#define VectorNumber_Vtpm2ch1           10U
#define VectorNumber_Vtpm2ch0           9U
#define VectorNumber_Vtpm1ovf           8U
#define VectorNumber_Vtpm1ch2           7U
#define VectorNumber_Vtpm1ch1           6U
#define VectorNumber_Vtpm1ch0           5U
//#define VectorNumber_Vicg               4U
#define VectorNumber_Vcodec             3U
#define VectorNumber_Virq               2U
#define VectorNumber_Vswi               1U
#define VectorNumber_Vreset             0U

/**************** interrupt vector table ****************/
#define Vfir                            0xFFC8U
//#define Vlcd                            0xFFCAU
#define Vrti                            0xFFCCU
#define Viic1                           0xFFCEU
//#define Vatd1                           0xFFD0U
#define Vkeyboard1                      0xFFD2U
#define Vsci2tx                         0xFFD4U
#define Vsci2rx                         0xFFD6U
#define Vsci2err                        0xFFD8U
#define Vsci1tx                         0xFFDAU
#define Vsci1rx                         0xFFDCU
#define Vsci1err                        0xFFDEU
#define Vspi1                           0xFFE0U
#define Vtpm2ovf                        0xFFE2U
#define Vtpm2ch4                        0xFFE4U
#define Vtpm2ch3                        0xFFE6U
#define Vtpm2ch2                        0xFFE8U
#define Vtpm2ch1                        0xFFEAU
#define Vtpm2ch0                        0xFFECU
#define Vtpm1ovf                        0xFFEEU
#define Vtpm1ch2                        0xFFF0U
#define Vtpm1ch1                        0xFFF2U
#define Vtpm1ch0                        0xFFF4U
// #define Vicg                            0xFFF6U
#define Vcodec                          0xFFF8U
#define Virq                            0xFFFAU
#define Vswi                            0xFFFCU
#define Vreset                          0xFFFEU

/**************** registers I/O map ****************/

/*** PTAD - Port A Data Register; 0x00000000 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAD0       :1;                                       /* Port A Data Register Bit 0 */
    byte PTAD1       :1;                                       /* Port A Data Register Bit 1 */
    byte PTAD2       :1;                                       /* Port A Data Register Bit 2 */
    byte PTAD3       :1;                                       /* Port A Data Register Bit 3 */
    byte PTAD4       :1;                                       /* Port A Data Register Bit 4 */
    byte PTAD5       :1;                                       /* Port A Data Register Bit 5 */
    byte PTAD6       :1;                                       /* Port A Data Register Bit 6 */
    byte PTAD7       :1;                                       /* Port A Data Register Bit 7 */
  } Bits;
} PTADSTR;
extern volatile PTADSTR _PTAD @0x00000000;
#define PTAD                            _PTAD.Byte
#define PTAD_PTAD0                      _PTAD.Bits.PTAD0
#define PTAD_PTAD1                      _PTAD.Bits.PTAD1
#define PTAD_PTAD2                      _PTAD.Bits.PTAD2
#define PTAD_PTAD3                      _PTAD.Bits.PTAD3
#define PTAD_PTAD4                      _PTAD.Bits.PTAD4
#define PTAD_PTAD5                      _PTAD.Bits.PTAD5
#define PTAD_PTAD6                      _PTAD.Bits.PTAD6
#define PTAD_PTAD7                      _PTAD.Bits.PTAD7

#define PTAD_PTAD0_MASK                 1U
#define PTAD_PTAD1_MASK                 2U
#define PTAD_PTAD2_MASK                 4U
#define PTAD_PTAD3_MASK                 8U
#define PTAD_PTAD4_MASK                 16U
#define PTAD_PTAD5_MASK                 32U
#define PTAD_PTAD6_MASK                 64U
#define PTAD_PTAD7_MASK                 128U

/*** PTADD - Data Direction Register A; 0x00000003 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADD0      :1;                                       /* Data Direction for Port A Bit 0 */
    byte PTADD1      :1;                                       /* Data Direction for Port A Bit 1 */
    byte PTADD2      :1;                                       /* Data Direction for Port A Bit 2 */
    byte PTADD3      :1;                                       /* Data Direction for Port A Bit 3 */
    byte PTADD4      :1;                                       /* Data Direction for Port A Bit 4 */
    byte PTADD5      :1;                                       /* Data Direction for Port A Bit 5 */
    byte PTADD6      :1;                                       /* Data Direction for Port A Bit 6 */
    byte PTADD7      :1;                                       /* Data Direction for Port A Bit 7 */
  } Bits;
} PTADDSTR;
extern volatile PTADDSTR _PTADD @0x00000003;
#define PTADD                           _PTADD.Byte
#define PTADD_PTADD0                    _PTADD.Bits.PTADD0
#define PTADD_PTADD1                    _PTADD.Bits.PTADD1
#define PTADD_PTADD2                    _PTADD.Bits.PTADD2
#define PTADD_PTADD3                    _PTADD.Bits.PTADD3
#define PTADD_PTADD4                    _PTADD.Bits.PTADD4
#define PTADD_PTADD5                    _PTADD.Bits.PTADD5
#define PTADD_PTADD6                    _PTADD.Bits.PTADD6
#define PTADD_PTADD7                    _PTADD.Bits.PTADD7

#define PTADD_PTADD0_MASK               1U
#define PTADD_PTADD1_MASK               2U
#define PTADD_PTADD2_MASK               4U
#define PTADD_PTADD3_MASK               8U
#define PTADD_PTADD4_MASK               16U
#define PTADD_PTADD5_MASK               32U
#define PTADD_PTADD6_MASK               64U
#define PTADD_PTADD7_MASK               128U


/*** PTBD - Port B Data Register; 0x00000004 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBD0       :1;                                       /* Port B Data Register Bit 0 */
    byte PTBD1       :1;                                       /* Port B Data Register Bit 1 */
    byte PTBD2       :1;                                       /* Port B Data Register Bit 2 */
    byte PTBD3       :1;                                       /* Port B Data Register Bit 3 */
    byte PTBD4       :1;                                       /* Port B Data Register Bit 4 */
    byte PTBD5       :1;                                       /* Port B Data Register Bit 5 */
    byte PTBD6       :1;                                       /* Port B Data Register Bit 6 */
    byte PTBD7       :1;                                       /* Port B Data Register Bit 7 */
  } Bits;
} PTBDSTR;
extern volatile PTBDSTR _PTBD @0x00000004;
#define PTBD                            _PTBD.Byte
#define PTBD_PTBD0                      _PTBD.Bits.PTBD0
#define PTBD_PTBD1                      _PTBD.Bits.PTBD1
#define PTBD_PTBD2                      _PTBD.Bits.PTBD2
#define PTBD_PTBD3                      _PTBD.Bits.PTBD3
#define PTBD_PTBD4                      _PTBD.Bits.PTBD4
#define PTBD_PTBD5                      _PTBD.Bits.PTBD5
#define PTBD_PTBD6                      _PTBD.Bits.PTBD6
#define PTBD_PTBD7                      _PTBD.Bits.PTBD7

#define PTBD_PTBD0_MASK                 1U
#define PTBD_PTBD1_MASK                 2U
#define PTBD_PTBD2_MASK                 4U
#define PTBD_PTBD3_MASK                 8U
#define PTBD_PTBD4_MASK                 16U
#define PTBD_PTBD5_MASK                 32U
#define PTBD_PTBD6_MASK                 64U
#define PTBD_PTBD7_MASK                 128U


/*** PTBDD - Data Direction Register B; 0x00000007 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDD0      :1;                                       /* Data Direction for Port B Bit 0 */
    byte PTBDD1      :1;                                       /* Data Direction for Port B Bit 1 */
    byte PTBDD2      :1;                                       /* Data Direction for Port B Bit 2 */
    byte PTBDD3      :1;                                       /* Data Direction for Port B Bit 3 */
    byte PTBDD4      :1;                                       /* Data Direction for Port B Bit 4 */
    byte PTBDD5      :1;                                       /* Data Direction for Port B Bit 5 */
    byte PTBDD6      :1;                                       /* Data Direction for Port B Bit 6 */
    byte PTBDD7      :1;                                       /* Data Direction for Port B Bit 7 */
  } Bits;
} PTBDDSTR;
extern volatile PTBDDSTR _PTBDD @0x00000007;
#define PTBDD                           _PTBDD.Byte
#define PTBDD_PTBDD0                    _PTBDD.Bits.PTBDD0
#define PTBDD_PTBDD1                    _PTBDD.Bits.PTBDD1
#define PTBDD_PTBDD2                    _PTBDD.Bits.PTBDD2
#define PTBDD_PTBDD3                    _PTBDD.Bits.PTBDD3
#define PTBDD_PTBDD4                    _PTBDD.Bits.PTBDD4
#define PTBDD_PTBDD5                    _PTBDD.Bits.PTBDD5
#define PTBDD_PTBDD6                    _PTBDD.Bits.PTBDD6
#define PTBDD_PTBDD7                    _PTBDD.Bits.PTBDD7

#define PTBDD_PTBDD0_MASK               1U
#define PTBDD_PTBDD1_MASK               2U
#define PTBDD_PTBDD2_MASK               4U
#define PTBDD_PTBDD3_MASK               8U
#define PTBDD_PTBDD4_MASK               16U
#define PTBDD_PTBDD5_MASK               32U
#define PTBDD_PTBDD6_MASK               64U
#define PTBDD_PTBDD7_MASK               128U


/*** PTCD - Port C Data Register; 0x00000008 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCD0       :1;                                       /* Port C Data Register Bit 0 */
    byte PTCD1       :1;                                       /* Port C Data Register Bit 1 */
    byte PTCD2       :1;                                       /* Port C Data Register Bit 2 */
    byte PTCD3       :1;                                       /* Port C Data Register Bit 3 */
    byte PTCD4       :1;                                       /* Port C Data Register Bit 4 */
    byte PTCD5       :1;                                       /* Port C Data Register Bit 5 */
    byte PTCD6       :1;                                       /* Port C Data Register Bit 6 */
    byte PTCD7       :1;                                       /* Port C Data Register Bit 7 */
  } Bits;
} PTCDSTR;
extern volatile PTCDSTR _PTCD @0x00000008;
#define PTCD                            _PTCD.Byte
#define PTCD_PTCD0                      _PTCD.Bits.PTCD0
#define PTCD_PTCD1                      _PTCD.Bits.PTCD1
#define PTCD_PTCD2                      _PTCD.Bits.PTCD2
#define PTCD_PTCD3                      _PTCD.Bits.PTCD3
#define PTCD_PTCD4                      _PTCD.Bits.PTCD4
#define PTCD_PTCD5                      _PTCD.Bits.PTCD5
#define PTCD_PTCD6                      _PTCD.Bits.PTCD6
#define PTCD_PTCD7                      _PTCD.Bits.PTCD7

#define PTCD_PTCD0_MASK                 1U
#define PTCD_PTCD1_MASK                 2U
#define PTCD_PTCD2_MASK                 4U
#define PTCD_PTCD3_MASK                 8U
#define PTCD_PTCD4_MASK                 16U
#define PTCD_PTCD5_MASK                 32U
#define PTCD_PTCD6_MASK                 64U
#define PTCD_PTCD7_MASK                 128U


/*** PTCDD - Data Direction Register C; 0x0000000B ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDD0      :1;                                       /* Data Direction for Port C Bit 0 */
    byte PTCDD1      :1;                                       /* Data Direction for Port C Bit 1 */
    byte PTCDD2      :1;                                       /* Data Direction for Port C Bit 2 */
    byte PTCDD3      :1;                                       /* Data Direction for Port C Bit 3 */
    byte PTCDD4      :1;                                       /* Data Direction for Port C Bit 4 */
    byte PTCDD5      :1;                                       /* Data Direction for Port C Bit 5 */
    byte PTCDD6      :1;                                       /* Data Direction for Port C Bit 6 */
    byte PTCDD7      :1;                                       /* Data Direction for Port C Bit 7 */
  } Bits;
} PTCDDSTR;
extern volatile PTCDDSTR _PTCDD @0x0000000B;
#define PTCDD                           _PTCDD.Byte
#define PTCDD_PTCDD0                    _PTCDD.Bits.PTCDD0
#define PTCDD_PTCDD1                    _PTCDD.Bits.PTCDD1
#define PTCDD_PTCDD2                    _PTCDD.Bits.PTCDD2
#define PTCDD_PTCDD3                    _PTCDD.Bits.PTCDD3
#define PTCDD_PTCDD4                    _PTCDD.Bits.PTCDD4
#define PTCDD_PTCDD5                    _PTCDD.Bits.PTCDD5
#define PTCDD_PTCDD6                    _PTCDD.Bits.PTCDD6
#define PTCDD_PTCDD7                    _PTCDD.Bits.PTCDD7

#define PTCDD_PTCDD0_MASK               1U
#define PTCDD_PTCDD1_MASK               2U
#define PTCDD_PTCDD2_MASK               4U
#define PTCDD_PTCDD3_MASK               8U
#define PTCDD_PTCDD4_MASK               16U
#define PTCDD_PTCDD5_MASK               32U
#define PTCDD_PTCDD6_MASK               64U
#define PTCDD_PTCDD7_MASK               128U


/*** PTDD - Port D Data Register; 0x0000000C ***/
typedef union {
  byte Byte;
  struct {
    byte PTDD0       :1;                                       /* Port D Data Register Bit 0 */
    byte PTDD1       :1;                                       /* Port D Data Register Bit 1 */
    byte PTDD2       :1;                                       /* Port D Data Register Bit 2 */
    byte PTDD3       :1;                                       /* Port D Data Register Bit 3 */
    byte PTDD4       :1;                                       /* Port D Data Register Bit 4 */
    byte PTDD5       :1;                                       /* Port D Data Register Bit 5 */
    byte PTDD6       :1;                                       /* Port D Data Register Bit 6 */
    byte PTDD7       :1;                                       /* Port D Data Register Bit 7 */
  } Bits;
} PTDDSTR;
extern volatile PTDDSTR _PTDD @0x0000000C;
#define PTDD                            _PTDD.Byte
#define PTDD_PTDD0                      _PTDD.Bits.PTDD0
#define PTDD_PTDD1                      _PTDD.Bits.PTDD1
#define PTDD_PTDD2                      _PTDD.Bits.PTDD2
#define PTDD_PTDD3                      _PTDD.Bits.PTDD3
#define PTDD_PTDD4                      _PTDD.Bits.PTDD4
#define PTDD_PTDD5                      _PTDD.Bits.PTDD5
#define PTDD_PTDD6                      _PTDD.Bits.PTDD6
#define PTDD_PTDD7                      _PTDD.Bits.PTDD7

#define PTDD_PTDD0_MASK                 1U
#define PTDD_PTDD1_MASK                 2U
#define PTDD_PTDD2_MASK                 4U
#define PTDD_PTDD3_MASK                 8U
#define PTDD_PTDD4_MASK                 16U
#define PTDD_PTDD5_MASK                 32U
#define PTDD_PTDD6_MASK                 64U
#define PTDD_PTDD7_MASK                 128U


/*** PTDDD - Data Direction Register D; 0x0000000F ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDD0      :1;                                       /* Data Direction for Port D Bit 0 */
    byte PTDDD1      :1;                                       /* Data Direction for Port D Bit 1 */
    byte PTDDD2      :1;                                       /* Data Direction for Port D Bit 2 */
    byte PTDDD3      :1;                                       /* Data Direction for Port D Bit 3 */
    byte PTDDD4      :1;                                       /* Data Direction for Port D Bit 4 */
    byte PTDDD5      :1;                                       /* Data Direction for Port D Bit 5 */
    byte PTDDD6      :1;                                       /* Data Direction for Port D Bit 6 */
    byte PTDDD7      :1;                                       /* Data Direction for Port D Bit 7 */
  } Bits;
} PTDDDSTR;
extern volatile PTDDDSTR _PTDDD @0x0000000F;
#define PTDDD                           _PTDDD.Byte
#define PTDDD_PTDDD0                    _PTDDD.Bits.PTDDD0
#define PTDDD_PTDDD1                    _PTDDD.Bits.PTDDD1
#define PTDDD_PTDDD2                    _PTDDD.Bits.PTDDD2
#define PTDDD_PTDDD3                    _PTDDD.Bits.PTDDD3
#define PTDDD_PTDDD4                    _PTDDD.Bits.PTDDD4
#define PTDDD_PTDDD5                    _PTDDD.Bits.PTDDD5
#define PTDDD_PTDDD6                    _PTDDD.Bits.PTDDD6
#define PTDDD_PTDDD7                    _PTDDD.Bits.PTDDD7

#define PTDDD_PTDDD0_MASK               1U
#define PTDDD_PTDDD1_MASK               2U
#define PTDDD_PTDDD2_MASK               4U
#define PTDDD_PTDDD3_MASK               8U
#define PTDDD_PTDDD4_MASK               16U
#define PTDDD_PTDDD5_MASK               32U
#define PTDDD_PTDDD6_MASK               64U
#define PTDDD_PTDDD7_MASK               128U


/*** PTED - Port E Data Register; 0x00000010 ***/
typedef union {
  byte Byte;
  struct {
    byte PTED0       :1;                                       /* Port E Data Register Bit 0 */
    byte PTED1       :1;                                       /* Port E Data Register Bit 1 */
    byte PTED2       :1;                                       /* Port E Data Register Bit 2 */
    byte PTED3       :1;                                       /* Port E Data Register Bit 3 */
    byte PTED4       :1;                                       /* Port E Data Register Bit 4 */
    byte PTED5       :1;                                       /* Port E Data Register Bit 5 */
    byte PTED6       :1;                                       /* Port E Data Register Bit 6 */
    byte PTED7       :1;                                       /* Port E Data Register Bit 7 */
  } Bits;
} PTEDSTR;
extern volatile PTEDSTR _PTED @0x00000010;
#define PTED                            _PTED.Byte
#define PTED_PTED0                      _PTED.Bits.PTED0
#define PTED_PTED1                      _PTED.Bits.PTED1
#define PTED_PTED2                      _PTED.Bits.PTED2
#define PTED_PTED3                      _PTED.Bits.PTED3
#define PTED_PTED4                      _PTED.Bits.PTED4
#define PTED_PTED5                      _PTED.Bits.PTED5
#define PTED_PTED6                      _PTED.Bits.PTED6
#define PTED_PTED7                      _PTED.Bits.PTED7

#define PTED_PTED0_MASK                 1U
#define PTED_PTED1_MASK                 2U
#define PTED_PTED2_MASK                 4U
#define PTED_PTED3_MASK                 8U
#define PTED_PTED4_MASK                 16U
#define PTED_PTED5_MASK                 32U
#define PTED_PTED6_MASK                 64U
#define PTED_PTED7_MASK                 128U


/*** PTEDD - Data Direction Register E; 0x00000013 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDD0      :1;                                       /* Data Direction for Port E Bit 0 */
    byte PTEDD1      :1;                                       /* Data Direction for Port E Bit 1 */
    byte PTEDD2      :1;                                       /* Data Direction for Port E Bit 2 */
    byte PTEDD3      :1;                                       /* Data Direction for Port E Bit 3 */
    byte PTEDD4      :1;                                       /* Data Direction for Port E Bit 4 */
    byte PTEDD5      :1;                                       /* Data Direction for Port E Bit 5 */
    byte PTEDD6      :1;                                       /* Data Direction for Port E Bit 6 */
    byte PTEDD7      :1;                                       /* Data Direction for Port E Bit 7 */
  } Bits;
} PTEDDSTR;
extern volatile PTEDDSTR _PTEDD @0x00000013;
#define PTEDD                           _PTEDD.Byte
#define PTEDD_PTEDD0                    _PTEDD.Bits.PTEDD0
#define PTEDD_PTEDD1                    _PTEDD.Bits.PTEDD1
#define PTEDD_PTEDD2                    _PTEDD.Bits.PTEDD2
#define PTEDD_PTEDD3                    _PTEDD.Bits.PTEDD3
#define PTEDD_PTEDD4                    _PTEDD.Bits.PTEDD4
#define PTEDD_PTEDD5                    _PTEDD.Bits.PTEDD5
#define PTEDD_PTEDD6                    _PTEDD.Bits.PTEDD6
#define PTEDD_PTEDD7                    _PTEDD.Bits.PTEDD7

#define PTEDD_PTEDD0_MASK               1U
#define PTEDD_PTEDD1_MASK               2U
#define PTEDD_PTEDD2_MASK               4U
#define PTEDD_PTEDD3_MASK               8U
#define PTEDD_PTEDD4_MASK               16U
#define PTEDD_PTEDD5_MASK               32U
#define PTEDD_PTEDD6_MASK               64U
#define PTEDD_PTEDD7_MASK               128U


/*** IRQSC - Interrupt Request Status and Control Register; 0x00000014 ***/
typedef union {
  byte Byte;
  struct {
    byte IRQMOD      :1;                                       /* IRQ Detection Mode */
    byte IRQIE       :1;                                       /* IRQ Interrupt Enable */
    byte IRQACK      :1;                                       /* IRQ Acknowledge */
    byte IRQF        :1;                                       /* IRQ Flag */
    byte IRQPE       :1;                                       /* IRQ Pin Enable */
    byte IRQEDG      :1;                                       /* Interrupt Request (IRQ) Edge Select */
    byte             :1;
    byte             :1;
  } Bits;
} IRQSCSTR;
extern volatile IRQSCSTR _IRQSC @0x00000014;
#define IRQSC                           _IRQSC.Byte
#define IRQSC_IRQMOD                    _IRQSC.Bits.IRQMOD
#define IRQSC_IRQIE                     _IRQSC.Bits.IRQIE
#define IRQSC_IRQACK                    _IRQSC.Bits.IRQACK
#define IRQSC_IRQF                      _IRQSC.Bits.IRQF
#define IRQSC_IRQPE                     _IRQSC.Bits.IRQPE
#define IRQSC_IRQEDG                    _IRQSC.Bits.IRQEDG

#define IRQSC_IRQMOD_MASK               1U
#define IRQSC_IRQIE_MASK                2U
#define IRQSC_IRQACK_MASK               4U
#define IRQSC_IRQF_MASK                 8U
#define IRQSC_IRQPE_MASK                16U
#define IRQSC_IRQEDG_MASK               32U


/*** KBI1SC - KBI1 Status and Control; 0x00000016 ***/
typedef union {
  byte Byte;
  struct {
    byte KBIMOD      :1;                                       /* Keyboard Detection Mode */
    byte KBIE        :1;                                       /* Keyboard Interrupt Enable */
    byte KBACK       :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KBF         :1;                                       /* Keyboard Interrupt Flag */
    byte KBEDG4      :1;                                       /* Keyboard Edge Select for Port A Bit 4 */
    byte KBEDG5      :1;                                       /* Keyboard Edge Select for Port A Bit 5 */
    byte KBEDG6      :1;                                       /* Keyboard Edge Select for Port A Bit 6 */
    byte KBEDG7      :1;                                       /* Keyboard Edge Select for Port A Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKBEDG_4 :4;
  } MergedBits;
} KBI1SCSTR;
extern volatile KBI1SCSTR _KBI1SC @0x00000016;
#define KBI1SC                          _KBI1SC.Byte
#define KBI1SC_KBIMOD                   _KBI1SC.Bits.KBIMOD
#define KBI1SC_KBIE                     _KBI1SC.Bits.KBIE
#define KBI1SC_KBACK                    _KBI1SC.Bits.KBACK
#define KBI1SC_KBF                      _KBI1SC.Bits.KBF
#define KBI1SC_KBEDG4                   _KBI1SC.Bits.KBEDG4
#define KBI1SC_KBEDG5                   _KBI1SC.Bits.KBEDG5
#define KBI1SC_KBEDG6                   _KBI1SC.Bits.KBEDG6
#define KBI1SC_KBEDG7                   _KBI1SC.Bits.KBEDG7
#define KBI1SC_KBEDG_4                  _KBI1SC.MergedBits.grpKBEDG_4
#define KBI1SC_KBEDG                    KBI1SC_KBEDG_4

#define KBI1SC_KBIMOD_MASK              1U
#define KBI1SC_KBIE_MASK                2U
#define KBI1SC_KBACK_MASK               4U
#define KBI1SC_KBF_MASK                 8U
#define KBI1SC_KBEDG4_MASK              16U
#define KBI1SC_KBEDG5_MASK              32U
#define KBI1SC_KBEDG6_MASK              64U
#define KBI1SC_KBEDG7_MASK              128U
#define KBI1SC_KBEDG_4_MASK             240U
#define KBI1SC_KBEDG_4_BITNUM           4U


/*** KBI1PE - KBI1 Pin Enable Register; 0x00000017 ***/
typedef union {
  byte Byte;
  struct {
    byte KBIPE0      :1;                                       /* Keyboard Pin Enable for Port A Bit 0 */
    byte KBIPE1      :1;                                       /* Keyboard Pin Enable for Port A Bit 1 */
    byte KBIPE2      :1;                                       /* Keyboard Pin Enable for Port A Bit 2 */
    byte KBIPE3      :1;                                       /* Keyboard Pin Enable for Port A Bit 3 */
    byte KBIPE4      :1;                                       /* Keyboard Pin Enable for Port A Bit 4 */
    byte KBIPE5      :1;                                       /* Keyboard Pin Enable for Port A Bit 5 */
    byte KBIPE6      :1;                                       /* Keyboard Pin Enable for Port A Bit 6 */
    byte KBIPE7      :1;                                       /* Keyboard Pin Enable for Port A Bit 7 */
  } Bits;
} KBI1PESTR;
extern volatile KBI1PESTR _KBI1PE @0x00000017;
#define KBI1PE                          _KBI1PE.Byte
#define KBI1PE_KBIPE0                   _KBI1PE.Bits.KBIPE0
#define KBI1PE_KBIPE1                   _KBI1PE.Bits.KBIPE1
#define KBI1PE_KBIPE2                   _KBI1PE.Bits.KBIPE2
#define KBI1PE_KBIPE3                   _KBI1PE.Bits.KBIPE3
#define KBI1PE_KBIPE4                   _KBI1PE.Bits.KBIPE4
#define KBI1PE_KBIPE5                   _KBI1PE.Bits.KBIPE5
#define KBI1PE_KBIPE6                   _KBI1PE.Bits.KBIPE6
#define KBI1PE_KBIPE7                   _KBI1PE.Bits.KBIPE7

#define KBI1PE_KBIPE0_MASK              1U
#define KBI1PE_KBIPE1_MASK              2U
#define KBI1PE_KBIPE2_MASK              4U
#define KBI1PE_KBIPE3_MASK              8U
#define KBI1PE_KBIPE4_MASK              16U
#define KBI1PE_KBIPE5_MASK              32U
#define KBI1PE_KBIPE6_MASK              64U
#define KBI1PE_KBIPE7_MASK              128U


/*** SCI1BD - SCI1 Baud Rate Register; 0x00000018 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000018 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1;
        byte             :1;
        byte             :1;
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI1BDHSTR;
    #define SCI1BDH                     _SCI1BD.Overlap_STR.SCI1BDHSTR.Byte
    #define SCI1BDH_SBR8                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR8
    #define SCI1BDH_SBR9                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR9
    #define SCI1BDH_SBR10               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR10
    #define SCI1BDH_SBR11               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR11
    #define SCI1BDH_SBR12               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR12
    #define SCI1BDH_SBR_8               _SCI1BD.Overlap_STR.SCI1BDHSTR.MergedBits.grpSBR_8
    #define SCI1BDH_SBR                 SCI1BDH_SBR_8

    #define SCI1BDH_SBR8_MASK           1U
    #define SCI1BDH_SBR9_MASK           2U
    #define SCI1BDH_SBR10_MASK          4U
    #define SCI1BDH_SBR11_MASK          8U
    #define SCI1BDH_SBR12_MASK          16U
    #define SCI1BDH_SBR_8_MASK          31U
    #define SCI1BDH_SBR_8_BITNUM        0U


    /*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000019 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI1BDLSTR;
    #define SCI1BDL                     _SCI1BD.Overlap_STR.SCI1BDLSTR.Byte
    #define SCI1BDL_SBR0                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR0
    #define SCI1BDL_SBR1                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR1
    #define SCI1BDL_SBR2                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR2
    #define SCI1BDL_SBR3                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR3
    #define SCI1BDL_SBR4                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR4
    #define SCI1BDL_SBR5                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR5
    #define SCI1BDL_SBR6                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR6
    #define SCI1BDL_SBR7                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR7

    #define SCI1BDL_SBR0_MASK           1U
    #define SCI1BDL_SBR1_MASK           2U
    #define SCI1BDL_SBR2_MASK           4U
    #define SCI1BDL_SBR3_MASK           8U
    #define SCI1BDL_SBR4_MASK           16U
    #define SCI1BDL_SBR5_MASK           32U
    #define SCI1BDL_SBR6_MASK           64U
    #define SCI1BDL_SBR7_MASK           128U

  } Overlap_STR;

} SCI1BDSTR;
extern volatile SCI1BDSTR _SCI1BD @0x00000018;
#define SCI1BD                          _SCI1BD.Word


/*** SCI1C1 - SCI1 Control Register 1; 0x0000001A ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI1C1STR;
extern volatile SCI1C1STR _SCI1C1 @0x0000001A;
#define SCI1C1                          _SCI1C1.Byte
#define SCI1C1_PT                       _SCI1C1.Bits.PT
#define SCI1C1_PE                       _SCI1C1.Bits.PE
#define SCI1C1_ILT                      _SCI1C1.Bits.ILT
#define SCI1C1_WAKE                     _SCI1C1.Bits.WAKE
#define SCI1C1_M                        _SCI1C1.Bits.M
#define SCI1C1_RSRC                     _SCI1C1.Bits.RSRC
#define SCI1C1_SCISWAI                  _SCI1C1.Bits.SCISWAI
#define SCI1C1_LOOPS                    _SCI1C1.Bits.LOOPS

#define SCI1C1_PT_MASK                  1U
#define SCI1C1_PE_MASK                  2U
#define SCI1C1_ILT_MASK                 4U
#define SCI1C1_WAKE_MASK                8U
#define SCI1C1_M_MASK                   16U
#define SCI1C1_RSRC_MASK                32U
#define SCI1C1_SCISWAI_MASK             64U
#define SCI1C1_LOOPS_MASK               128U


/*** SCI1C2 - SCI1 Control Register 2; 0x0000001B ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI1C2STR;
extern volatile SCI1C2STR _SCI1C2 @0x0000001B;
#define SCI1C2                          _SCI1C2.Byte
#define SCI1C2_SBK                      _SCI1C2.Bits.SBK
#define SCI1C2_RWU                      _SCI1C2.Bits.RWU
#define SCI1C2_RE                       _SCI1C2.Bits.RE
#define SCI1C2_TE                       _SCI1C2.Bits.TE
#define SCI1C2_ILIE                     _SCI1C2.Bits.ILIE
#define SCI1C2_RIE                      _SCI1C2.Bits.RIE
#define SCI1C2_TCIE                     _SCI1C2.Bits.TCIE
#define SCI1C2_TIE                      _SCI1C2.Bits.TIE

#define SCI1C2_SBK_MASK                 1U
#define SCI1C2_RWU_MASK                 2U
#define SCI1C2_RE_MASK                  4U
#define SCI1C2_TE_MASK                  8U
#define SCI1C2_ILIE_MASK                16U
#define SCI1C2_RIE_MASK                 32U
#define SCI1C2_TCIE_MASK                64U
#define SCI1C2_TIE_MASK                 128U


/*** SCI1S1 - SCI1 Status Register 1; 0x0000001C ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI1S1STR;
extern volatile SCI1S1STR _SCI1S1 @0x0000001C;
#define SCI1S1                          _SCI1S1.Byte
#define SCI1S1_PF                       _SCI1S1.Bits.PF
#define SCI1S1_FE                       _SCI1S1.Bits.FE
#define SCI1S1_NF                       _SCI1S1.Bits.NF
#define SCI1S1_OR                       _SCI1S1.Bits.OR
#define SCI1S1_IDLE                     _SCI1S1.Bits.IDLE
#define SCI1S1_RDRF                     _SCI1S1.Bits.RDRF
#define SCI1S1_TC                       _SCI1S1.Bits.TC
#define SCI1S1_TDRE                     _SCI1S1.Bits.TDRE

#define SCI1S1_PF_MASK                  1U
#define SCI1S1_FE_MASK                  2U
#define SCI1S1_NF_MASK                  4U
#define SCI1S1_OR_MASK                  8U
#define SCI1S1_IDLE_MASK                16U
#define SCI1S1_RDRF_MASK                32U
#define SCI1S1_TC_MASK                  64U
#define SCI1S1_TDRE_MASK                128U


/*** SCI1S2 - SCI1 Status Register 2; 0x0000001D ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
  } Bits;
} SCI1S2STR;
extern volatile SCI1S2STR _SCI1S2 @0x0000001D;
#define SCI1S2                          _SCI1S2.Byte
#define SCI1S2_RAF                      _SCI1S2.Bits.RAF

#define SCI1S2_RAF_MASK                 1U


/*** SCI1C3 - SCI1 Control Register 3; 0x0000001E ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte             :1;
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI1C3STR;
extern volatile SCI1C3STR _SCI1C3 @0x0000001E;
#define SCI1C3                          _SCI1C3.Byte
#define SCI1C3_PEIE                     _SCI1C3.Bits.PEIE
#define SCI1C3_FEIE                     _SCI1C3.Bits.FEIE
#define SCI1C3_NEIE                     _SCI1C3.Bits.NEIE
#define SCI1C3_ORIE                     _SCI1C3.Bits.ORIE
#define SCI1C3_TXDIR                    _SCI1C3.Bits.TXDIR
#define SCI1C3_T8                       _SCI1C3.Bits.T8
#define SCI1C3_R8                       _SCI1C3.Bits.R8

#define SCI1C3_PEIE_MASK                1U
#define SCI1C3_FEIE_MASK                2U
#define SCI1C3_NEIE_MASK                4U
#define SCI1C3_ORIE_MASK                8U
#define SCI1C3_TXDIR_MASK               32U
#define SCI1C3_T8_MASK                  64U
#define SCI1C3_R8_MASK                  128U


/*** SCI1D - SCI1 Data Register; 0x0000001F ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI1DSTR;
extern volatile SCI1DSTR _SCI1D @0x0000001F;
#define SCI1D                           _SCI1D.Byte
#define SCI1D_R0_T0                     _SCI1D.Bits.R0_T0
#define SCI1D_R1_T1                     _SCI1D.Bits.R1_T1
#define SCI1D_R2_T2                     _SCI1D.Bits.R2_T2
#define SCI1D_R3_T3                     _SCI1D.Bits.R3_T3
#define SCI1D_R4_T4                     _SCI1D.Bits.R4_T4
#define SCI1D_R5_T5                     _SCI1D.Bits.R5_T5
#define SCI1D_R6_T6                     _SCI1D.Bits.R6_T6
#define SCI1D_R7_T7                     _SCI1D.Bits.R7_T7

#define SCI1D_R0_T0_MASK                1U
#define SCI1D_R1_T1_MASK                2U
#define SCI1D_R2_T2_MASK                4U
#define SCI1D_R3_T3_MASK                8U
#define SCI1D_R4_T4_MASK                16U
#define SCI1D_R5_T5_MASK                32U
#define SCI1D_R6_T6_MASK                64U
#define SCI1D_R7_T7_MASK                128U


/*** SCI2BD - SCI2 Baud Rate Register; 0x00000020 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI2BDH - SCI2 Baud Rate Register High; 0x00000020 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1;
        byte             :1;
        byte             :1;
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI2BDHSTR;
    #define SCI2BDH                     _SCI2BD.Overlap_STR.SCI2BDHSTR.Byte
    #define SCI2BDH_SBR8                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR8
    #define SCI2BDH_SBR9                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR9
    #define SCI2BDH_SBR10               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR10
    #define SCI2BDH_SBR11               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR11
    #define SCI2BDH_SBR12               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR12
    #define SCI2BDH_SBR_8               _SCI2BD.Overlap_STR.SCI2BDHSTR.MergedBits.grpSBR_8
    #define SCI2BDH_SBR                 SCI2BDH_SBR_8

    #define SCI2BDH_SBR8_MASK           1U
    #define SCI2BDH_SBR9_MASK           2U
    #define SCI2BDH_SBR10_MASK          4U
    #define SCI2BDH_SBR11_MASK          8U
    #define SCI2BDH_SBR12_MASK          16U
    #define SCI2BDH_SBR_8_MASK          31U
    #define SCI2BDH_SBR_8_BITNUM        0U


    /*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00000021 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI2BDLSTR;
    #define SCI2BDL                     _SCI2BD.Overlap_STR.SCI2BDLSTR.Byte
    #define SCI2BDL_SBR0                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR0
    #define SCI2BDL_SBR1                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR1
    #define SCI2BDL_SBR2                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR2
    #define SCI2BDL_SBR3                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR3
    #define SCI2BDL_SBR4                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR4
    #define SCI2BDL_SBR5                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR5
    #define SCI2BDL_SBR6                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR6
    #define SCI2BDL_SBR7                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR7

    #define SCI2BDL_SBR0_MASK           1U
    #define SCI2BDL_SBR1_MASK           2U
    #define SCI2BDL_SBR2_MASK           4U
    #define SCI2BDL_SBR3_MASK           8U
    #define SCI2BDL_SBR4_MASK           16U
    #define SCI2BDL_SBR5_MASK           32U
    #define SCI2BDL_SBR6_MASK           64U
    #define SCI2BDL_SBR7_MASK           128U

  } Overlap_STR;

} SCI2BDSTR;
extern volatile SCI2BDSTR _SCI2BD @0x00000020;
#define SCI2BD                          _SCI2BD.Word


/*** SCI2C1 - SCI1 Control Register 1; 0x00000022 ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI2C1STR;
extern volatile SCI2C1STR _SCI2C1 @0x00000022;
#define SCI2C1                          _SCI2C1.Byte
#define SCI2C1_PT                       _SCI2C1.Bits.PT
#define SCI2C1_PE                       _SCI2C1.Bits.PE
#define SCI2C1_ILT                      _SCI2C1.Bits.ILT
#define SCI2C1_WAKE                     _SCI2C1.Bits.WAKE
#define SCI2C1_M                        _SCI2C1.Bits.M
#define SCI2C1_RSRC                     _SCI2C1.Bits.RSRC
#define SCI2C1_SCISWAI                  _SCI2C1.Bits.SCISWAI
#define SCI2C1_LOOPS                    _SCI2C1.Bits.LOOPS

#define SCI2C1_PT_MASK                  1U
#define SCI2C1_PE_MASK                  2U
#define SCI2C1_ILT_MASK                 4U
#define SCI2C1_WAKE_MASK                8U
#define SCI2C1_M_MASK                   16U
#define SCI2C1_RSRC_MASK                32U
#define SCI2C1_SCISWAI_MASK             64U
#define SCI2C1_LOOPS_MASK               128U


/*** SCI2C2 - SCI2 Control Register 2; 0x00000023 ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI2C2STR;
extern volatile SCI2C2STR _SCI2C2 @0x00000023;
#define SCI2C2                          _SCI2C2.Byte
#define SCI2C2_SBK                      _SCI2C2.Bits.SBK
#define SCI2C2_RWU                      _SCI2C2.Bits.RWU
#define SCI2C2_RE                       _SCI2C2.Bits.RE
#define SCI2C2_TE                       _SCI2C2.Bits.TE
#define SCI2C2_ILIE                     _SCI2C2.Bits.ILIE
#define SCI2C2_RIE                      _SCI2C2.Bits.RIE
#define SCI2C2_TCIE                     _SCI2C2.Bits.TCIE
#define SCI2C2_TIE                      _SCI2C2.Bits.TIE

#define SCI2C2_SBK_MASK                 1U
#define SCI2C2_RWU_MASK                 2U
#define SCI2C2_RE_MASK                  4U
#define SCI2C2_TE_MASK                  8U
#define SCI2C2_ILIE_MASK                16U
#define SCI2C2_RIE_MASK                 32U
#define SCI2C2_TCIE_MASK                64U
#define SCI2C2_TIE_MASK                 128U


/*** SCI2S1 - SCI2 Status Register 1; 0x00000024 ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI2S1STR;
extern volatile SCI2S1STR _SCI2S1 @0x00000024;
#define SCI2S1                          _SCI2S1.Byte
#define SCI2S1_PF                       _SCI2S1.Bits.PF
#define SCI2S1_FE                       _SCI2S1.Bits.FE
#define SCI2S1_NF                       _SCI2S1.Bits.NF
#define SCI2S1_OR                       _SCI2S1.Bits.OR
#define SCI2S1_IDLE                     _SCI2S1.Bits.IDLE
#define SCI2S1_RDRF                     _SCI2S1.Bits.RDRF
#define SCI2S1_TC                       _SCI2S1.Bits.TC
#define SCI2S1_TDRE                     _SCI2S1.Bits.TDRE

#define SCI2S1_PF_MASK                  1U
#define SCI2S1_FE_MASK                  2U
#define SCI2S1_NF_MASK                  4U
#define SCI2S1_OR_MASK                  8U
#define SCI2S1_IDLE_MASK                16U
#define SCI2S1_RDRF_MASK                32U
#define SCI2S1_TC_MASK                  64U
#define SCI2S1_TDRE_MASK                128U


/*** SCI2S2 - SCI2 Status Register 2; 0x00000025 ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
  } Bits;
} SCI2S2STR;
extern volatile SCI2S2STR _SCI2S2 @0x00000025;
#define SCI2S2                          _SCI2S2.Byte
#define SCI2S2_RAF                      _SCI2S2.Bits.RAF

#define SCI2S2_RAF_MASK                 1U


/*** SCI2C3 - SCI2 Control Register 3; 0x00000026 ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte             :1;
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI2C3STR;
extern volatile SCI2C3STR _SCI2C3 @0x00000026;
#define SCI2C3                          _SCI2C3.Byte
#define SCI2C3_PEIE                     _SCI2C3.Bits.PEIE
#define SCI2C3_FEIE                     _SCI2C3.Bits.FEIE
#define SCI2C3_NEIE                     _SCI2C3.Bits.NEIE
#define SCI2C3_ORIE                     _SCI2C3.Bits.ORIE
#define SCI2C3_TXDIR                    _SCI2C3.Bits.TXDIR
#define SCI2C3_T8                       _SCI2C3.Bits.T8
#define SCI2C3_R8                       _SCI2C3.Bits.R8

#define SCI2C3_PEIE_MASK                1U
#define SCI2C3_FEIE_MASK                2U
#define SCI2C3_NEIE_MASK                4U
#define SCI2C3_ORIE_MASK                8U
#define SCI2C3_TXDIR_MASK               32U
#define SCI2C3_T8_MASK                  64U
#define SCI2C3_R8_MASK                  128U


/*** SCI2D - SCI2 Data Register; 0x00000027 ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI2DSTR;
extern volatile SCI2DSTR _SCI2D @0x00000027;
#define SCI2D                           _SCI2D.Byte
#define SCI2D_R0_T0                     _SCI2D.Bits.R0_T0
#define SCI2D_R1_T1                     _SCI2D.Bits.R1_T1
#define SCI2D_R2_T2                     _SCI2D.Bits.R2_T2
#define SCI2D_R3_T3                     _SCI2D.Bits.R3_T3
#define SCI2D_R4_T4                     _SCI2D.Bits.R4_T4
#define SCI2D_R5_T5                     _SCI2D.Bits.R5_T5
#define SCI2D_R6_T6                     _SCI2D.Bits.R6_T6
#define SCI2D_R7_T7                     _SCI2D.Bits.R7_T7

#define SCI2D_R0_T0_MASK                1U
#define SCI2D_R1_T1_MASK                2U
#define SCI2D_R2_T2_MASK                4U
#define SCI2D_R3_T3_MASK                8U
#define SCI2D_R4_T4_MASK                16U
#define SCI2D_R5_T5_MASK                32U
#define SCI2D_R6_T6_MASK                64U
#define SCI2D_R7_T7_MASK                128U


/*** SPI1C1 - SPI1 Control Register 1; 0x00000028 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (shifter direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI1 Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI1 System Enable */
    byte SPIE        :1;                                       /* SPI1 Interrupt Enable */
  } Bits;
} SPI1C1STR;
extern volatile SPI1C1STR _SPI1C1 @0x00000028;
#define SPI1C1                          _SPI1C1.Byte
#define SPI1C1_LSBFE                    _SPI1C1.Bits.LSBFE
#define SPI1C1_SSOE                     _SPI1C1.Bits.SSOE
#define SPI1C1_CPHA                     _SPI1C1.Bits.CPHA
#define SPI1C1_CPOL                     _SPI1C1.Bits.CPOL
#define SPI1C1_MSTR                     _SPI1C1.Bits.MSTR
#define SPI1C1_SPTIE                    _SPI1C1.Bits.SPTIE
#define SPI1C1_SPE                      _SPI1C1.Bits.SPE
#define SPI1C1_SPIE                     _SPI1C1.Bits.SPIE

#define SPI1C1_LSBFE_MASK               1U
#define SPI1C1_SSOE_MASK                2U
#define SPI1C1_CPHA_MASK                4U
#define SPI1C1_CPOL_MASK                8U
#define SPI1C1_MSTR_MASK                16U
#define SPI1C1_SPTIE_MASK               32U
#define SPI1C1_SPE_MASK                 64U
#define SPI1C1_SPIE_MASK                128U


/*** SPI1C2 - SPI1 Control Register 2; 0x00000029 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI1 Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI1 Stop in Wait Mode */
    byte             :1;
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1;
    byte             :1;
    byte             :1;
  } Bits;
} SPI1C2STR;
extern volatile SPI1C2STR _SPI1C2 @0x00000029;
#define SPI1C2                          _SPI1C2.Byte
#define SPI1C2_SPC0                     _SPI1C2.Bits.SPC0
#define SPI1C2_SPISWAI                  _SPI1C2.Bits.SPISWAI
#define SPI1C2_BIDIROE                  _SPI1C2.Bits.BIDIROE
#define SPI1C2_MODFEN                   _SPI1C2.Bits.MODFEN

#define SPI1C2_SPC0_MASK                1U
#define SPI1C2_SPISWAI_MASK             2U
#define SPI1C2_BIDIROE_MASK             8U
#define SPI1C2_MODFEN_MASK              16U


/*** SPI1BR - SPI1 Baud Rate Register; 0x0000002A ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI1 Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI1 Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI1 Baud Rate Divisor Bit 2 */
    byte             :1;
    byte SPPR0       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 2 */
    byte             :1;
  } Bits;
  struct {
    byte grpSPR  :3;
    byte         :1;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI1BRSTR;
extern volatile SPI1BRSTR _SPI1BR @0x0000002A;
#define SPI1BR                          _SPI1BR.Byte
#define SPI1BR_SPR0                     _SPI1BR.Bits.SPR0
#define SPI1BR_SPR1                     _SPI1BR.Bits.SPR1
#define SPI1BR_SPR2                     _SPI1BR.Bits.SPR2
#define SPI1BR_SPPR0                    _SPI1BR.Bits.SPPR0
#define SPI1BR_SPPR1                    _SPI1BR.Bits.SPPR1
#define SPI1BR_SPPR2                    _SPI1BR.Bits.SPPR2
#define SPI1BR_SPR                      _SPI1BR.MergedBits.grpSPR
#define SPI1BR_SPPR                     _SPI1BR.MergedBits.grpSPPR

#define SPI1BR_SPR0_MASK                1U
#define SPI1BR_SPR1_MASK                2U
#define SPI1BR_SPR2_MASK                4U
#define SPI1BR_SPPR0_MASK               16U
#define SPI1BR_SPPR1_MASK               32U
#define SPI1BR_SPPR2_MASK               64U
#define SPI1BR_SPR_MASK                 7U
#define SPI1BR_SPR_BITNUM               0U
#define SPI1BR_SPPR_MASK                112U
#define SPI1BR_SPPR_BITNUM              4U


/*** SPI1S - SPI1 Status Register; 0x0000002B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI1 Transmit Buffer Empty Flag */
    byte             :1;
    byte SPRF        :1;                                       /* SPI1 Read Buffer Full Flag */
  } Bits;
} SPI1SSTR;
extern volatile SPI1SSTR _SPI1S @0x0000002B;
#define SPI1S                           _SPI1S.Byte
#define SPI1S_MODF                      _SPI1S.Bits.MODF
#define SPI1S_SPTEF                     _SPI1S.Bits.SPTEF
#define SPI1S_SPRF                      _SPI1S.Bits.SPRF

#define SPI1S_MODF_MASK                 16U
#define SPI1S_SPTEF_MASK                32U
#define SPI1S_SPRF_MASK                 128U


/*** SPI1D - SPI1 Data Register; 0x0000002D ***/
typedef union {
  byte Byte;
} SPI1DSTR;
extern volatile SPI1DSTR _SPI1D @0x0000002D;
#define SPI1D                           _SPI1D.Byte


/*** TPM1SC - TPM 1 Status and Control Register; 0x00000030 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1SCSTR;
extern volatile TPM1SCSTR _TPM1SC @0x00000030;
#define TPM1SC                          _TPM1SC.Byte
#define TPM1SC_PS0                      _TPM1SC.Bits.PS0
#define TPM1SC_PS1                      _TPM1SC.Bits.PS1
#define TPM1SC_PS2                      _TPM1SC.Bits.PS2
#define TPM1SC_CLKSA                    _TPM1SC.Bits.CLKSA
#define TPM1SC_CLKSB                    _TPM1SC.Bits.CLKSB
#define TPM1SC_CPWMS                    _TPM1SC.Bits.CPWMS
#define TPM1SC_TOIE                     _TPM1SC.Bits.TOIE
#define TPM1SC_TOF                      _TPM1SC.Bits.TOF
#define TPM1SC_PS                       _TPM1SC.MergedBits.grpPS
#define TPM1SC_CLKSx                    _TPM1SC.MergedBits.grpCLKSx

#define TPM1SC_PS0_MASK                 1U
#define TPM1SC_PS1_MASK                 2U
#define TPM1SC_PS2_MASK                 4U
#define TPM1SC_CLKSA_MASK               8U
#define TPM1SC_CLKSB_MASK               16U
#define TPM1SC_CPWMS_MASK               32U
#define TPM1SC_TOIE_MASK                64U
#define TPM1SC_TOF_MASK                 128U
#define TPM1SC_PS_MASK                  7U
#define TPM1SC_PS_BITNUM                0U
#define TPM1SC_CLKSx_MASK               24U
#define TPM1SC_CLKSx_BITNUM             3U


/*** TPM1CNT - TPM 1 Counter Register; 0x00000031 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1CNTH - TPM 1 Counter Register High; 0x00000031 ***/
    union {
      byte Byte;
    } TPM1CNTHSTR;
    #define TPM1CNTH                    _TPM1CNT.Overlap_STR.TPM1CNTHSTR.Byte


    /*** TPM1CNTL - TPM 1 Counter Register Low; 0x00000032 ***/
    union {
      byte Byte;
    } TPM1CNTLSTR;
    #define TPM1CNTL                    _TPM1CNT.Overlap_STR.TPM1CNTLSTR.Byte

  } Overlap_STR;

} TPM1CNTSTR;
extern volatile TPM1CNTSTR _TPM1CNT @0x00000031;
#define TPM1CNT                         _TPM1CNT.Word


/*** TPM1MOD - TPM 1 Timer Counter Modulo Register; 0x00000033 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1MODH - TPM 1 Timer Counter Modulo Register High; 0x00000033 ***/
    union {
      byte Byte;
    } TPM1MODHSTR;
    #define TPM1MODH                    _TPM1MOD.Overlap_STR.TPM1MODHSTR.Byte


    /*** TPM1MODL - TPM 1 Timer Counter Modulo Register Low; 0x00000034 ***/
    union {
      byte Byte;
    } TPM1MODLSTR;
    #define TPM1MODL                    _TPM1MOD.Overlap_STR.TPM1MODLSTR.Byte

  } Overlap_STR;

} TPM1MODSTR;
extern volatile TPM1MODSTR _TPM1MOD @0x00000033;
#define TPM1MOD                         _TPM1MOD.Word


/*** TPM1C0SC - TPM 1 Timer Channel 0 Status and Control Register; 0x00000035 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C0SCSTR;
extern volatile TPM1C0SCSTR _TPM1C0SC @0x00000035;
#define TPM1C0SC                        _TPM1C0SC.Byte
#define TPM1C0SC_ELS0A                  _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELS0B                  _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MS0A                   _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MS0B                   _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CH0IE                  _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CH0F                   _TPM1C0SC.Bits.CH0F
#define TPM1C0SC_ELS0x                  _TPM1C0SC.MergedBits.grpELS0x
#define TPM1C0SC_MS0x                   _TPM1C0SC.MergedBits.grpMS0x

#define TPM1C0SC_ELS0A_MASK             4U
#define TPM1C0SC_ELS0B_MASK             8U
#define TPM1C0SC_MS0A_MASK              16U
#define TPM1C0SC_MS0B_MASK              32U
#define TPM1C0SC_CH0IE_MASK             64U
#define TPM1C0SC_CH0F_MASK              128U
#define TPM1C0SC_ELS0x_MASK             12U
#define TPM1C0SC_ELS0x_BITNUM           2U
#define TPM1C0SC_MS0x_MASK              48U
#define TPM1C0SC_MS0x_BITNUM            4U


/*** TPM1C0V - TPM 1 Timer Channel 0 Value Register; 0x00000036 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C0VH - TPM 1 Timer Channel 0 Value Register High; 0x00000036 ***/
    union {
      byte Byte;
    } TPM1C0VHSTR;
    #define TPM1C0VH                    _TPM1C0V.Overlap_STR.TPM1C0VHSTR.Byte


    /*** TPM1C0VL - TPM 1 Timer Channel 0 Value Register Low; 0x00000037 ***/
    union {
      byte Byte;
    } TPM1C0VLSTR;
    #define TPM1C0VL                    _TPM1C0V.Overlap_STR.TPM1C0VLSTR.Byte

  } Overlap_STR;

} TPM1C0VSTR;
extern volatile TPM1C0VSTR _TPM1C0V @0x00000036;
#define TPM1C0V                         _TPM1C0V.Word


/*** TPM1C1SC - TPM 1 Timer Channel 1 Status and Control Register; 0x00000038 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C1SCSTR;
extern volatile TPM1C1SCSTR _TPM1C1SC @0x00000038;
#define TPM1C1SC                        _TPM1C1SC.Byte
#define TPM1C1SC_ELS1A                  _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELS1B                  _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MS1A                   _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MS1B                   _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CH1IE                  _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CH1F                   _TPM1C1SC.Bits.CH1F
#define TPM1C1SC_ELS1x                  _TPM1C1SC.MergedBits.grpELS1x
#define TPM1C1SC_MS1x                   _TPM1C1SC.MergedBits.grpMS1x

#define TPM1C1SC_ELS1A_MASK             4U
#define TPM1C1SC_ELS1B_MASK             8U
#define TPM1C1SC_MS1A_MASK              16U
#define TPM1C1SC_MS1B_MASK              32U
#define TPM1C1SC_CH1IE_MASK             64U
#define TPM1C1SC_CH1F_MASK              128U
#define TPM1C1SC_ELS1x_MASK             12U
#define TPM1C1SC_ELS1x_BITNUM           2U
#define TPM1C1SC_MS1x_MASK              48U
#define TPM1C1SC_MS1x_BITNUM            4U


/*** TPM1C1V - TPM 1 Timer Channel 1 Value Register; 0x00000039 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C1VH - TPM 1 Timer Channel 1 Value Register High; 0x00000039 ***/
    union {
      byte Byte;
    } TPM1C1VHSTR;
    #define TPM1C1VH                    _TPM1C1V.Overlap_STR.TPM1C1VHSTR.Byte


    /*** TPM1C1VL - TPM 1 Timer Channel 1 Value Register Low; 0x0000003A ***/
    union {
      byte Byte;
    } TPM1C1VLSTR;
    #define TPM1C1VL                    _TPM1C1V.Overlap_STR.TPM1C1VLSTR.Byte

  } Overlap_STR;

} TPM1C1VSTR;
extern volatile TPM1C1VSTR _TPM1C1V @0x00000039;
#define TPM1C1V                         _TPM1C1V.Word


/*** TPM1C2SC - TPM 1 Timer Channel 2 Status and Control Register; 0x0000003B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C2SCSTR;
extern volatile TPM1C2SCSTR _TPM1C2SC @0x0000003B;
#define TPM1C2SC                        _TPM1C2SC.Byte
#define TPM1C2SC_ELS2A                  _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELS2B                  _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MS2A                   _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MS2B                   _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CH2IE                  _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CH2F                   _TPM1C2SC.Bits.CH2F
#define TPM1C2SC_ELS2x                  _TPM1C2SC.MergedBits.grpELS2x
#define TPM1C2SC_MS2x                   _TPM1C2SC.MergedBits.grpMS2x

#define TPM1C2SC_ELS2A_MASK             4U
#define TPM1C2SC_ELS2B_MASK             8U
#define TPM1C2SC_MS2A_MASK              16U
#define TPM1C2SC_MS2B_MASK              32U
#define TPM1C2SC_CH2IE_MASK             64U
#define TPM1C2SC_CH2F_MASK              128U
#define TPM1C2SC_ELS2x_MASK             12U
#define TPM1C2SC_ELS2x_BITNUM           2U
#define TPM1C2SC_MS2x_MASK              48U
#define TPM1C2SC_MS2x_BITNUM            4U


/*** TPM1C2V - TPM 1 Timer Channel 2 Value Register; 0x0000003C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C2VH - TPM 1 Timer Channel 2 Value Register High; 0x0000003C ***/
    union {
      byte Byte;
    } TPM1C2VHSTR;
    #define TPM1C2VH                    _TPM1C2V.Overlap_STR.TPM1C2VHSTR.Byte


    /*** TPM1C2VL - TPM 1 Timer Channel 2 Value Register Low; 0x0000003D ***/
    union {
      byte Byte;
    } TPM1C2VLSTR;
    #define TPM1C2VL                    _TPM1C2V.Overlap_STR.TPM1C2VLSTR.Byte

  } Overlap_STR;

} TPM1C2VSTR;
extern volatile TPM1C2VSTR _TPM1C2V @0x0000003C;
#define TPM1C2V                         _TPM1C2V.Word


/*** PTFD - Port F Data Register; 0x00000040 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFD0       :1;                                       /* Port F Data Register Bit 0 */
    byte PTFD1       :1;                                       /* Port F Data Register Bit 1 */
    byte PTFD2       :1;                                       /* Port F Data Register Bit 2 */
    byte PTFD3       :1;                                       /* Port F Data Register Bit 3 */
    byte PTFD4       :1;                                       /* Port F Data Register Bit 4 */
    byte PTFD5       :1;                                       /* Port F Data Register Bit 5 */
    byte PTFD6       :1;                                       /* Port F Data Register Bit 6 */
    byte PTFD7       :1;                                       /* Port F Data Register Bit 7 */
  } Bits;
} PTFDSTR;
extern volatile PTFDSTR _PTFD @0x00000040;
#define PTFD                            _PTFD.Byte
#define PTFD_PTFD0                      _PTFD.Bits.PTFD0
#define PTFD_PTFD1                      _PTFD.Bits.PTFD1
#define PTFD_PTFD2                      _PTFD.Bits.PTFD2
#define PTFD_PTFD3                      _PTFD.Bits.PTFD3
#define PTFD_PTFD4                      _PTFD.Bits.PTFD4
#define PTFD_PTFD5                      _PTFD.Bits.PTFD5
#define PTFD_PTFD6                      _PTFD.Bits.PTFD6
#define PTFD_PTFD7                      _PTFD.Bits.PTFD7

#define PTFD_PTFD0_MASK                 1U
#define PTFD_PTFD1_MASK                 2U
#define PTFD_PTFD2_MASK                 4U
#define PTFD_PTFD3_MASK                 8U
#define PTFD_PTFD4_MASK                 16U
#define PTFD_PTFD5_MASK                 32U
#define PTFD_PTFD6_MASK                 64U
#define PTFD_PTFD7_MASK                 128U


/*** PTFDD - Data Direction Register F; 0x00000043 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDD0      :1;                                       /* Data Direction for Port F Bit 0 */
    byte PTFDD1      :1;                                       /* Data Direction for Port F Bit 1 */
    byte PTFDD2      :1;                                       /* Data Direction for Port F Bit 2 */
    byte PTFDD3      :1;                                       /* Data Direction for Port F Bit 3 */
    byte PTFDD4      :1;                                       /* Data Direction for Port F Bit 4 */
    byte PTFDD5      :1;                                       /* Data Direction for Port F Bit 5 */
    byte PTFDD6      :1;                                       /* Data Direction for Port F Bit 6 */
    byte PTFDD7      :1;                                       /* Data Direction for Port F Bit 7 */
  } Bits;
} PTFDDSTR;
extern volatile PTFDDSTR _PTFDD @0x00000043;
#define PTFDD                           _PTFDD.Byte
#define PTFDD_PTFDD0                    _PTFDD.Bits.PTFDD0
#define PTFDD_PTFDD1                    _PTFDD.Bits.PTFDD1
#define PTFDD_PTFDD2                    _PTFDD.Bits.PTFDD2
#define PTFDD_PTFDD3                    _PTFDD.Bits.PTFDD3
#define PTFDD_PTFDD4                    _PTFDD.Bits.PTFDD4
#define PTFDD_PTFDD5                    _PTFDD.Bits.PTFDD5
#define PTFDD_PTFDD6                    _PTFDD.Bits.PTFDD6
#define PTFDD_PTFDD7                    _PTFDD.Bits.PTFDD7

#define PTFDD_PTFDD0_MASK               1U
#define PTFDD_PTFDD1_MASK               2U
#define PTFDD_PTFDD2_MASK               4U
#define PTFDD_PTFDD3_MASK               8U
#define PTFDD_PTFDD4_MASK               16U
#define PTFDD_PTFDD5_MASK               32U
#define PTFDD_PTFDD6_MASK               64U
#define PTFDD_PTFDD7_MASK               128U


/*** PTGD - Port G Data Register; 0x00000044 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGD0       :1;                                       /* Port G Data Register Bit 0 */
    byte PTGD1       :1;                                       /* Port G Data Register Bit 1 */
    byte PTGD2       :1;                                       /* Port G Data Register Bit 2 */
    byte PTGD3       :1;                                       /* Port G Data Register Bit 3 */
    byte PTGD4       :1;                                       /* Port G Data Register Bit 4 */
    byte PTGD5       :1;                                       /* Port G Data Register Bit 5 */
    byte PTGD6       :1;                                       /* Port G Data Register Bit 6 */
    byte PTGD7       :1;                                       /* Port G Data Register Bit 7 */
  } Bits;
} PTGDSTR;
extern volatile PTGDSTR _PTGD @0x00000044;
#define PTGD                            _PTGD.Byte
#define PTGD_PTGD0                      _PTGD.Bits.PTGD0
#define PTGD_PTGD1                      _PTGD.Bits.PTGD1
#define PTGD_PTGD2                      _PTGD.Bits.PTGD2
#define PTGD_PTGD3                      _PTGD.Bits.PTGD3
#define PTGD_PTGD4                      _PTGD.Bits.PTGD4
#define PTGD_PTGD5                      _PTGD.Bits.PTGD5
#define PTGD_PTGD6                      _PTGD.Bits.PTGD6
#define PTGD_PTGD7                      _PTGD.Bits.PTGD7

#define PTGD_PTGD0_MASK                 1U
#define PTGD_PTGD1_MASK                 2U
#define PTGD_PTGD2_MASK                 4U
#define PTGD_PTGD3_MASK                 8U
#define PTGD_PTGD4_MASK                 16U
#define PTGD_PTGD5_MASK                 32U
#define PTGD_PTGD6_MASK                 64U
#define PTGD_PTGD7_MASK                 128U


/*** PTGDD - Data Direction Register G; 0x00000047 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDD0      :1;                                       /* Data Direction for Port G Bit 0 */
    byte PTGDD1      :1;                                       /* Data Direction for Port G Bit 1 */
    byte PTGDD2      :1;                                       /* Data Direction for Port G Bit 2 */
    byte PTGDD3      :1;                                       /* Data Direction for Port G Bit 3 */
    byte PTGDD4      :1;                                       /* Data Direction for Port G Bit 4 */
    byte PTGDD5      :1;                                       /* Data Direction for Port G Bit 5 */
    byte PTGDD6      :1;                                       /* Data Direction for Port G Bit 6 */
    byte PTGDD7      :1;                                       /* Data Direction for Port G Bit 7 */
  } Bits;
} PTGDDSTR;
extern volatile PTGDDSTR _PTGDD @0x00000047;
#define PTGDD                           _PTGDD.Byte
#define PTGDD_PTGDD0                    _PTGDD.Bits.PTGDD0
#define PTGDD_PTGDD1                    _PTGDD.Bits.PTGDD1
#define PTGDD_PTGDD2                    _PTGDD.Bits.PTGDD2
#define PTGDD_PTGDD3                    _PTGDD.Bits.PTGDD3
#define PTGDD_PTGDD4                    _PTGDD.Bits.PTGDD4
#define PTGDD_PTGDD5                    _PTGDD.Bits.PTGDD5
#define PTGDD_PTGDD6                    _PTGDD.Bits.PTGDD6
#define PTGDD_PTGDD7                    _PTGDD.Bits.PTGDD7

#define PTGDD_PTGDD0_MASK               1U
#define PTGDD_PTGDD1_MASK               2U
#define PTGDD_PTGDD2_MASK               4U
#define PTGDD_PTGDD3_MASK               8U
#define PTGDD_PTGDD4_MASK               16U
#define PTGDD_PTGDD5_MASK               32U
#define PTGDD_PTGDD6_MASK               64U
#define PTGDD_PTGDD7_MASK               128U


/*** ICGC1 - ICG Control Register 1; 0x00000048 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte OSCSTEN     :1;                                       /* Enable Oscillator in Off Mode */
    byte CLKS0       :1;                                       /* Clock Mode Select Bit 0 */
    byte CLKS1       :1;                                       /* Clock Mode Select Bit 1 */
    byte REFS        :1;                                       /* External Reference Select */
    byte RANGE       :1;                                       /* Frequency Range Select */
    byte             :1;
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCLKS :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ICGC1STR;
extern volatile ICGC1STR _ICGC1 @0x00000048;
#define ICGC1                           _ICGC1.Byte
#define ICGC1_OSCSTEN                   _ICGC1.Bits.OSCSTEN
#define ICGC1_CLKS0                     _ICGC1.Bits.CLKS0
#define ICGC1_CLKS1                     _ICGC1.Bits.CLKS1
#define ICGC1_REFS                      _ICGC1.Bits.REFS
#define ICGC1_RANGE                     _ICGC1.Bits.RANGE
#define ICGC1_CLKS                      _ICGC1.MergedBits.grpCLKS

#define ICGC1_OSCSTEN_MASK              4U
#define ICGC1_CLKS0_MASK                8U
#define ICGC1_CLKS1_MASK                16U
#define ICGC1_REFS_MASK                 32U
#define ICGC1_RANGE_MASK                64U
#define ICGC1_CLKS_MASK                 24U
#define ICGC1_CLKS_BITNUM               3U


/*** ICGC2 - ICG Control Register 2; 0x00000049 ***/
typedef union {
  byte Byte;
  struct {
    byte RFD0        :1;                                       /* Reduced Frequency Divider Bit 0 */
    byte RFD1        :1;                                       /* Reduced Frequency Divider Bit 1 */
    byte RFD2        :1;                                       /* Reduced Frequency Divider Bit 2 */
    byte LOCRE       :1;                                       /* Loss of Clock Reset Enable */
    byte MFD0        :1;                                       /* Multiplication Factor Bit 0 */
    byte MFD1        :1;                                       /* Multiplication Factor Bit 1 */
    byte MFD2        :1;                                       /* Multiplication Factor Bit 2 */
    byte LOLRE       :1;                                       /* Loss of Lock Reset Enable */
  } Bits;
  struct {
    byte grpRFD  :3;
    byte         :1;
    byte grpMFD  :3;
    byte         :1;
  } MergedBits;
} ICGC2STR;
extern volatile ICGC2STR _ICGC2 @0x00000049;
#define ICGC2                           _ICGC2.Byte
#define ICGC2_RFD0                      _ICGC2.Bits.RFD0
#define ICGC2_RFD1                      _ICGC2.Bits.RFD1
#define ICGC2_RFD2                      _ICGC2.Bits.RFD2
#define ICGC2_LOCRE                     _ICGC2.Bits.LOCRE
#define ICGC2_MFD0                      _ICGC2.Bits.MFD0
#define ICGC2_MFD1                      _ICGC2.Bits.MFD1
#define ICGC2_MFD2                      _ICGC2.Bits.MFD2
#define ICGC2_LOLRE                     _ICGC2.Bits.LOLRE
#define ICGC2_RFD                       _ICGC2.MergedBits.grpRFD
#define ICGC2_MFD                       _ICGC2.MergedBits.grpMFD

#define ICGC2_RFD0_MASK                 1U
#define ICGC2_RFD1_MASK                 2U
#define ICGC2_RFD2_MASK                 4U
#define ICGC2_LOCRE_MASK                8U
#define ICGC2_MFD0_MASK                 16U
#define ICGC2_MFD1_MASK                 32U
#define ICGC2_MFD2_MASK                 64U
#define ICGC2_LOLRE_MASK                128U
#define ICGC2_RFD_MASK                  7U
#define ICGC2_RFD_BITNUM                0U
#define ICGC2_MFD_MASK                  112U
#define ICGC2_MFD_BITNUM                4U


/*** ICGS1 - ICG Status Register 1; 0x0000004A ***/
typedef union {
  byte Byte;
  struct {
    byte ICGIF       :1;                                       /* ICG Interrupt Flag */
    byte ERCS        :1;                                       /* External Reference Clock Status */
    byte LOCS        :1;                                       /* Loss Of Clock Status */
    byte LOCK        :1;                                       /* FLL Lock Status */
    byte LOLS        :1;                                       /* FLL Loss of Lock Status */
    byte REFST       :1;                                       /* Reference Clock Status */
    byte CLKST0      :1;                                       /* Clock Mode Status Bit 0 */
    byte CLKST1      :1;                                       /* Clock Mode Status Bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCLKST :2;
  } MergedBits;
} ICGS1STR;
extern volatile ICGS1STR _ICGS1 @0x0000004A;
#define ICGS1                           _ICGS1.Byte
#define ICGS1_ICGIF                     _ICGS1.Bits.ICGIF
#define ICGS1_ERCS                      _ICGS1.Bits.ERCS
#define ICGS1_LOCS                      _ICGS1.Bits.LOCS
#define ICGS1_LOCK                      _ICGS1.Bits.LOCK
#define ICGS1_LOLS                      _ICGS1.Bits.LOLS
#define ICGS1_REFST                     _ICGS1.Bits.REFST
#define ICGS1_CLKST0                    _ICGS1.Bits.CLKST0
#define ICGS1_CLKST1                    _ICGS1.Bits.CLKST1
#define ICGS1_CLKST                     _ICGS1.MergedBits.grpCLKST

#define ICGS1_ICGIF_MASK                1U
#define ICGS1_ERCS_MASK                 2U
#define ICGS1_LOCS_MASK                 4U
#define ICGS1_LOCK_MASK                 8U
#define ICGS1_LOLS_MASK                 16U
#define ICGS1_REFST_MASK                32U
#define ICGS1_CLKST0_MASK               64U
#define ICGS1_CLKST1_MASK               128U
#define ICGS1_CLKST_MASK                192U
#define ICGS1_CLKST_BITNUM              6U


/*** ICGS2 - ICG Status Register 2; 0x0000004B ***/
typedef union {
  byte Byte;
  struct {
    byte DCOS        :1;                                       /* DCO Clock Stable */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
  } Bits;
} ICGS2STR;
extern volatile ICGS2STR _ICGS2 @0x0000004B;
#define ICGS2                           _ICGS2.Byte
#define ICGS2_DCOS                      _ICGS2.Bits.DCOS

#define ICGS2_DCOS_MASK                 1U


/*** ICGFLT - ICG Filter Register; 0x0000004C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ICGFLTU - ICG Upper Filter Register; 0x0000004C ***/
    union {
      byte Byte;
      struct {
        byte FILT8       :1;                                       /* ICG Filter Bit 8 */
        byte FILT9       :1;                                       /* ICG Filter Bit 9 */
        byte FILT10      :1;                                       /* ICG Filter Bit 10 */
        byte FILT11      :1;                                       /* ICG Filter Bit 11 */
        byte             :1;
        byte             :1;
        byte             :1;
        byte             :1;
      } Bits;
      struct {
        byte grpFILT_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ICGFLTUSTR;
    #define ICGFLTU                     _ICGFLT.Overlap_STR.ICGFLTUSTR.Byte
    #define ICGFLTU_FILT8               _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT8
    #define ICGFLTU_FILT9               _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT9
    #define ICGFLTU_FILT10              _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT10
    #define ICGFLTU_FILT11              _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT11
    #define ICGFLTU_FILT_8              _ICGFLT.Overlap_STR.ICGFLTUSTR.MergedBits.grpFILT_8
    #define ICGFLTU_FILT                ICGFLTU_FILT_8

    #define ICGFLTU_FILT8_MASK          1U
    #define ICGFLTU_FILT9_MASK          2U
    #define ICGFLTU_FILT10_MASK         4U
    #define ICGFLTU_FILT11_MASK         8U
    #define ICGFLTU_FILT_8_MASK         15U
    #define ICGFLTU_FILT_8_BITNUM       0U


    /*** ICGFLTL - ICG Lower Filter Register; 0x0000004D ***/
    union {
      byte Byte;
      struct {
        byte FILT0       :1;                                       /* ICG Filter Bit 0 */
        byte FILT1       :1;                                       /* ICG Filter Bit 1 */
        byte FILT2       :1;                                       /* ICG Filter Bit 2 */
        byte FILT3       :1;                                       /* ICG Filter Bit 3 */
        byte FILT4       :1;                                       /* ICG Filter Bit 4 */
        byte FILT5       :1;                                       /* ICG Filter Bit 5 */
        byte FILT6       :1;                                       /* ICG Filter Bit 6 */
        byte FILT7       :1;                                       /* ICG Filter Bit 7 */
      } Bits;
    } ICGFLTLSTR;
    #define ICGFLTL                     _ICGFLT.Overlap_STR.ICGFLTLSTR.Byte
    #define ICGFLTL_FILT0               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT0
    #define ICGFLTL_FILT1               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT1
    #define ICGFLTL_FILT2               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT2
    #define ICGFLTL_FILT3               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT3
    #define ICGFLTL_FILT4               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT4
    #define ICGFLTL_FILT5               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT5
    #define ICGFLTL_FILT6               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT6
    #define ICGFLTL_FILT7               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT7

    #define ICGFLTL_FILT0_MASK          1U
    #define ICGFLTL_FILT1_MASK          2U
    #define ICGFLTL_FILT2_MASK          4U
    #define ICGFLTL_FILT3_MASK          8U
    #define ICGFLTL_FILT4_MASK          16U
    #define ICGFLTL_FILT5_MASK          32U
    #define ICGFLTL_FILT6_MASK          64U
    #define ICGFLTL_FILT7_MASK          128U

  } Overlap_STR;

} ICGFLTSTR;
extern volatile ICGFLTSTR _ICGFLT @0x0000004C;
#define ICGFLT                          _ICGFLT.Word


/*** ICGTRM - ICG Trim Register; 0x0000004E ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICG Trim Bit 0 */
    byte TRIM1       :1;                                       /* ICG Trim Bit 1 */
    byte TRIM2       :1;                                       /* ICG Trim Bit 2 */
    byte TRIM3       :1;                                       /* ICG Trim Bit 3 */
    byte TRIM4       :1;                                       /* ICG Trim Bit 4 */
    byte TRIM5       :1;                                       /* ICG Trim Bit 5 */
    byte TRIM6       :1;                                       /* ICG Trim Bit 6 */
    byte TRIM7       :1;                                       /* ICG Trim Bit 7 */
  } Bits;
} ICGTRMSTR;
extern volatile ICGTRMSTR _ICGTRM @0x0000004E;
#define ICGTRM                          _ICGTRM.Byte
#define ICGTRM_TRIM0                    _ICGTRM.Bits.TRIM0
#define ICGTRM_TRIM1                    _ICGTRM.Bits.TRIM1
#define ICGTRM_TRIM2                    _ICGTRM.Bits.TRIM2
#define ICGTRM_TRIM3                    _ICGTRM.Bits.TRIM3
#define ICGTRM_TRIM4                    _ICGTRM.Bits.TRIM4
#define ICGTRM_TRIM5                    _ICGTRM.Bits.TRIM5
#define ICGTRM_TRIM6                    _ICGTRM.Bits.TRIM6
#define ICGTRM_TRIM7                    _ICGTRM.Bits.TRIM7

#define ICGTRM_TRIM0_MASK               1U
#define ICGTRM_TRIM1_MASK               2U
#define ICGTRM_TRIM2_MASK               4U
#define ICGTRM_TRIM3_MASK               8U
#define ICGTRM_TRIM4_MASK               16U
#define ICGTRM_TRIM5_MASK               32U
#define ICGTRM_TRIM6_MASK               64U
#define ICGTRM_TRIM7_MASK               128U


/*** IIC1A - IIC1 Address Register; 0x00000058 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte ADDR1       :1;                                       /* IIC Address Bit 1 */
    byte ADDR2       :1;                                       /* IIC Address Bit 2 */
    byte ADDR3       :1;                                       /* IIC Address Bit 3 */
    byte ADDR4       :1;                                       /* IIC Address Bit 4 */
    byte ADDR5       :1;                                       /* IIC Address Bit 5 */
    byte ADDR6       :1;                                       /* IIC Address Bit 6 */
    byte ADDR7       :1;                                       /* IIC Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpADDR_1 :7;
  } MergedBits;
} IIC1ASTR;
extern volatile IIC1ASTR _IIC1A @0x00000058;
#define IIC1A                           _IIC1A.Byte
#define IIC1A_ADDR1                     _IIC1A.Bits.ADDR1
#define IIC1A_ADDR2                     _IIC1A.Bits.ADDR2
#define IIC1A_ADDR3                     _IIC1A.Bits.ADDR3
#define IIC1A_ADDR4                     _IIC1A.Bits.ADDR4
#define IIC1A_ADDR5                     _IIC1A.Bits.ADDR5
#define IIC1A_ADDR6                     _IIC1A.Bits.ADDR6
#define IIC1A_ADDR7                     _IIC1A.Bits.ADDR7
#define IIC1A_ADDR_1                    _IIC1A.MergedBits.grpADDR_1
#define IIC1A_ADDR                      IIC1A_ADDR_1

#define IIC1A_ADDR1_MASK                2U
#define IIC1A_ADDR2_MASK                4U
#define IIC1A_ADDR3_MASK                8U
#define IIC1A_ADDR4_MASK                16U
#define IIC1A_ADDR5_MASK                32U
#define IIC1A_ADDR6_MASK                64U
#define IIC1A_ADDR7_MASK                128U
#define IIC1A_ADDR_1_MASK               254U
#define IIC1A_ADDR_1_BITNUM             1U


/*** IIC1F - IIC1 Frequency Divider Register; 0x00000059 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IIC1FSTR;
extern volatile IIC1FSTR _IIC1F @0x00000059;
#define IIC1F                           _IIC1F.Byte
#define IIC1F_ICR0                      _IIC1F.Bits.ICR0
#define IIC1F_ICR1                      _IIC1F.Bits.ICR1
#define IIC1F_ICR2                      _IIC1F.Bits.ICR2
#define IIC1F_ICR3                      _IIC1F.Bits.ICR3
#define IIC1F_ICR4                      _IIC1F.Bits.ICR4
#define IIC1F_ICR5                      _IIC1F.Bits.ICR5
#define IIC1F_MULT0                     _IIC1F.Bits.MULT0
#define IIC1F_MULT1                     _IIC1F.Bits.MULT1
#define IIC1F_ICR                       _IIC1F.MergedBits.grpICR
#define IIC1F_MULT                      _IIC1F.MergedBits.grpMULT

#define IIC1F_ICR0_MASK                 1U
#define IIC1F_ICR1_MASK                 2U
#define IIC1F_ICR2_MASK                 4U
#define IIC1F_ICR3_MASK                 8U
#define IIC1F_ICR4_MASK                 16U
#define IIC1F_ICR5_MASK                 32U
#define IIC1F_MULT0_MASK                64U
#define IIC1F_MULT1_MASK                128U
#define IIC1F_ICR_MASK                  63U
#define IIC1F_ICR_BITNUM                0U
#define IIC1F_MULT_MASK                 192U
#define IIC1F_MULT_BITNUM               6U


/*** IIC1C - IIC1 Control Register; 0x0000005A ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte RSTA        :1;                                       /* Repeat START Bit */
    byte TXAK        :1;                                       /* Transmit Acknowledge Enable Bit */
    byte TX          :1;                                       /* Transmit Mode Select Bit */
    byte MST         :1;                                       /* Master Mode Select Bit */
    byte IICIE       :1;                                       /* IIC Interrupt Enable Bit */
    byte IICEN       :1;                                       /* IIC Enable Bit */
  } Bits;
} IIC1CSTR;
extern volatile IIC1CSTR _IIC1C @0x0000005A;
#define IIC1C                           _IIC1C.Byte
#define IIC1C_RSTA                      _IIC1C.Bits.RSTA
#define IIC1C_TXAK                      _IIC1C.Bits.TXAK
#define IIC1C_TX                        _IIC1C.Bits.TX
#define IIC1C_MST                       _IIC1C.Bits.MST
#define IIC1C_IICIE                     _IIC1C.Bits.IICIE
#define IIC1C_IICEN                     _IIC1C.Bits.IICEN

#define IIC1C_RSTA_MASK                 4U
#define IIC1C_TXAK_MASK                 8U
#define IIC1C_TX_MASK                   16U
#define IIC1C_MST_MASK                  32U
#define IIC1C_IICIE_MASK                64U
#define IIC1C_IICEN_MASK                128U


/*** IIC1S - IIC1 Status Register; 0x0000005B ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1;
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy bit */
    byte IAAS        :1;                                       /* Addressed as a Slave Bit */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IIC1SSTR;
extern volatile IIC1SSTR _IIC1S @0x0000005B;
#define IIC1S                           _IIC1S.Byte
#define IIC1S_RXAK                      _IIC1S.Bits.RXAK
#define IIC1S_IICIF                     _IIC1S.Bits.IICIF
#define IIC1S_SRW                       _IIC1S.Bits.SRW
#define IIC1S_ARBL                      _IIC1S.Bits.ARBL
#define IIC1S_BUSY                      _IIC1S.Bits.BUSY
#define IIC1S_IAAS                      _IIC1S.Bits.IAAS
#define IIC1S_TCF                       _IIC1S.Bits.TCF

#define IIC1S_RXAK_MASK                 1U
#define IIC1S_IICIF_MASK                2U
#define IIC1S_SRW_MASK                  4U
#define IIC1S_ARBL_MASK                 16U
#define IIC1S_BUSY_MASK                 32U
#define IIC1S_IAAS_MASK                 64U
#define IIC1S_TCF_MASK                  128U


/*** IIC1D - IIC1 Data I/O Register; 0x0000005C ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IIC1DSTR;
extern volatile IIC1DSTR _IIC1D @0x0000005C;
#define IIC1D                           _IIC1D.Byte
#define IIC1D_DATA0                     _IIC1D.Bits.DATA0
#define IIC1D_DATA1                     _IIC1D.Bits.DATA1
#define IIC1D_DATA2                     _IIC1D.Bits.DATA2
#define IIC1D_DATA3                     _IIC1D.Bits.DATA3
#define IIC1D_DATA4                     _IIC1D.Bits.DATA4
#define IIC1D_DATA5                     _IIC1D.Bits.DATA5
#define IIC1D_DATA6                     _IIC1D.Bits.DATA6
#define IIC1D_DATA7                     _IIC1D.Bits.DATA7

#define IIC1D_DATA0_MASK                1U
#define IIC1D_DATA1_MASK                2U
#define IIC1D_DATA2_MASK                4U
#define IIC1D_DATA3_MASK                8U
#define IIC1D_DATA4_MASK                16U
#define IIC1D_DATA5_MASK                32U
#define IIC1D_DATA6_MASK                64U
#define IIC1D_DATA7_MASK                128U


/*** TPM2SC - TPM 2 Status and Control Register; 0x00000060 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2SCSTR;
extern volatile TPM2SCSTR _TPM2SC @0x00000060;
#define TPM2SC                          _TPM2SC.Byte
#define TPM2SC_PS0                      _TPM2SC.Bits.PS0
#define TPM2SC_PS1                      _TPM2SC.Bits.PS1
#define TPM2SC_PS2                      _TPM2SC.Bits.PS2
#define TPM2SC_CLKSA                    _TPM2SC.Bits.CLKSA
#define TPM2SC_CLKSB                    _TPM2SC.Bits.CLKSB
#define TPM2SC_CPWMS                    _TPM2SC.Bits.CPWMS
#define TPM2SC_TOIE                     _TPM2SC.Bits.TOIE
#define TPM2SC_TOF                      _TPM2SC.Bits.TOF
#define TPM2SC_PS                       _TPM2SC.MergedBits.grpPS
#define TPM2SC_CLKSx                    _TPM2SC.MergedBits.grpCLKSx

#define TPM2SC_PS0_MASK                 1U
#define TPM2SC_PS1_MASK                 2U
#define TPM2SC_PS2_MASK                 4U
#define TPM2SC_CLKSA_MASK               8U
#define TPM2SC_CLKSB_MASK               16U
#define TPM2SC_CPWMS_MASK               32U
#define TPM2SC_TOIE_MASK                64U
#define TPM2SC_TOF_MASK                 128U
#define TPM2SC_PS_MASK                  7U
#define TPM2SC_PS_BITNUM                0U
#define TPM2SC_CLKSx_MASK               24U
#define TPM2SC_CLKSx_BITNUM             3U


/*** TPM2CNT - TPM 2 Counter Register; 0x00000061 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2CNTH - TPM 2 Counter Register High; 0x00000061 ***/
    union {
      byte Byte;
    } TPM2CNTHSTR;
    #define TPM2CNTH                    _TPM2CNT.Overlap_STR.TPM2CNTHSTR.Byte


    /*** TPM2CNTL - TPM 2 Counter Register Low; 0x00000062 ***/
    union {
      byte Byte;
    } TPM2CNTLSTR;
    #define TPM2CNTL                    _TPM2CNT.Overlap_STR.TPM2CNTLSTR.Byte

  } Overlap_STR;

} TPM2CNTSTR;
extern volatile TPM2CNTSTR _TPM2CNT @0x00000061;
#define TPM2CNT                         _TPM2CNT.Word


/*** TPM2MOD - TPM 2 Timer Counter Modulo Register; 0x00000063 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2MODH - TPM 2 Timer Counter Modulo Register High; 0x00000063 ***/
    union {
      byte Byte;
    } TPM2MODHSTR;
    #define TPM2MODH                    _TPM2MOD.Overlap_STR.TPM2MODHSTR.Byte


    /*** TPM2MODL - TPM 2 Timer Counter Modulo Register Low; 0x00000064 ***/
    union {
      byte Byte;
    } TPM2MODLSTR;
    #define TPM2MODL                    _TPM2MOD.Overlap_STR.TPM2MODLSTR.Byte

  } Overlap_STR;

} TPM2MODSTR;
extern volatile TPM2MODSTR _TPM2MOD @0x00000063;
#define TPM2MOD                         _TPM2MOD.Word


/*** TPM2C0SC - TPM 2 Timer Channel 0 Status and Control Register; 0x00000065 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C0SCSTR;
extern volatile TPM2C0SCSTR _TPM2C0SC @0x00000065;
#define TPM2C0SC                        _TPM2C0SC.Byte
#define TPM2C0SC_ELS0A                  _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELS0B                  _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MS0A                   _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MS0B                   _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CH0IE                  _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CH0F                   _TPM2C0SC.Bits.CH0F
#define TPM2C0SC_ELS0x                  _TPM2C0SC.MergedBits.grpELS0x
#define TPM2C0SC_MS0x                   _TPM2C0SC.MergedBits.grpMS0x

#define TPM2C0SC_ELS0A_MASK             4U
#define TPM2C0SC_ELS0B_MASK             8U
#define TPM2C0SC_MS0A_MASK              16U
#define TPM2C0SC_MS0B_MASK              32U
#define TPM2C0SC_CH0IE_MASK             64U
#define TPM2C0SC_CH0F_MASK              128U
#define TPM2C0SC_ELS0x_MASK             12U
#define TPM2C0SC_ELS0x_BITNUM           2U
#define TPM2C0SC_MS0x_MASK              48U
#define TPM2C0SC_MS0x_BITNUM            4U


/*** TPM2C0V - TPM 2 Timer Channel 0 Value Register; 0x00000066 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C0VH - TPM 2 Timer Channel 0 Value Register High; 0x00000066 ***/
    union {
      byte Byte;
    } TPM2C0VHSTR;
    #define TPM2C0VH                    _TPM2C0V.Overlap_STR.TPM2C0VHSTR.Byte


    /*** TPM2C0VL - TPM 2 Timer Channel 0 Value Register Low; 0x00000067 ***/
    union {
      byte Byte;
    } TPM2C0VLSTR;
    #define TPM2C0VL                    _TPM2C0V.Overlap_STR.TPM2C0VLSTR.Byte

  } Overlap_STR;

} TPM2C0VSTR;
extern volatile TPM2C0VSTR _TPM2C0V @0x00000066;
#define TPM2C0V                         _TPM2C0V.Word


/*** TPM2C1SC - TPM 2 Timer Channel 1 Status and Control Register; 0x00000068 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C1SCSTR;
extern volatile TPM2C1SCSTR _TPM2C1SC @0x00000068;
#define TPM2C1SC                        _TPM2C1SC.Byte
#define TPM2C1SC_ELS1A                  _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELS1B                  _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MS1A                   _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MS1B                   _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CH1IE                  _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CH1F                   _TPM2C1SC.Bits.CH1F
#define TPM2C1SC_ELS1x                  _TPM2C1SC.MergedBits.grpELS1x
#define TPM2C1SC_MS1x                   _TPM2C1SC.MergedBits.grpMS1x

#define TPM2C1SC_ELS1A_MASK             4U
#define TPM2C1SC_ELS1B_MASK             8U
#define TPM2C1SC_MS1A_MASK              16U
#define TPM2C1SC_MS1B_MASK              32U
#define TPM2C1SC_CH1IE_MASK             64U
#define TPM2C1SC_CH1F_MASK              128U
#define TPM2C1SC_ELS1x_MASK             12U
#define TPM2C1SC_ELS1x_BITNUM           2U
#define TPM2C1SC_MS1x_MASK              48U
#define TPM2C1SC_MS1x_BITNUM            4U


/*** TPM2C1V - TPM 2 Timer Channel 1 Value Register; 0x00000069 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C1VH - TPM 2 Timer Channel 1 Value Register High; 0x00000069 ***/
    union {
      byte Byte;
    } TPM2C1VHSTR;
    #define TPM2C1VH                    _TPM2C1V.Overlap_STR.TPM2C1VHSTR.Byte


    /*** TPM2C1VL - TPM 2 Timer Channel 1 Value Register Low; 0x0000006A ***/
    union {
      byte Byte;
    } TPM2C1VLSTR;
    #define TPM2C1VL                    _TPM2C1V.Overlap_STR.TPM2C1VLSTR.Byte

  } Overlap_STR;

} TPM2C1VSTR;
extern volatile TPM2C1VSTR _TPM2C1V @0x00000069;
#define TPM2C1V                         _TPM2C1V.Word


/*** TPM2C2SC - TPM 2 Timer Channel 2 Status and Control Register; 0x0000006B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C2SCSTR;
extern volatile TPM2C2SCSTR _TPM2C2SC @0x0000006B;
#define TPM2C2SC                        _TPM2C2SC.Byte
#define TPM2C2SC_ELS2A                  _TPM2C2SC.Bits.ELS2A
#define TPM2C2SC_ELS2B                  _TPM2C2SC.Bits.ELS2B
#define TPM2C2SC_MS2A                   _TPM2C2SC.Bits.MS2A
#define TPM2C2SC_MS2B                   _TPM2C2SC.Bits.MS2B
#define TPM2C2SC_CH2IE                  _TPM2C2SC.Bits.CH2IE
#define TPM2C2SC_CH2F                   _TPM2C2SC.Bits.CH2F
#define TPM2C2SC_ELS2x                  _TPM2C2SC.MergedBits.grpELS2x
#define TPM2C2SC_MS2x                   _TPM2C2SC.MergedBits.grpMS2x

#define TPM2C2SC_ELS2A_MASK             4U
#define TPM2C2SC_ELS2B_MASK             8U
#define TPM2C2SC_MS2A_MASK              16U
#define TPM2C2SC_MS2B_MASK              32U
#define TPM2C2SC_CH2IE_MASK             64U
#define TPM2C2SC_CH2F_MASK              128U
#define TPM2C2SC_ELS2x_MASK             12U
#define TPM2C2SC_ELS2x_BITNUM           2U
#define TPM2C2SC_MS2x_MASK              48U
#define TPM2C2SC_MS2x_BITNUM            4U


/*** TPM2C2V - TPM 2 Timer Channel 2 Value Register; 0x0000006C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C2VH - TPM 2 Timer Channel 2 Value Register High; 0x0000006C ***/
    union {
      byte Byte;
    } TPM2C2VHSTR;
    #define TPM2C2VH                    _TPM2C2V.Overlap_STR.TPM2C2VHSTR.Byte


    /*** TPM2C2VL - TPM 2 Timer Channel 2 Value Register Low; 0x0000006D ***/
    union {
      byte Byte;
    } TPM2C2VLSTR;
    #define TPM2C2VL                    _TPM2C2V.Overlap_STR.TPM2C2VLSTR.Byte

  } Overlap_STR;

} TPM2C2VSTR;
extern volatile TPM2C2VSTR _TPM2C2V @0x0000006C;
#define TPM2C2V                         _TPM2C2V.Word


/*** TPM2C3SC - TPM 2 Timer Channel 3 Status and Control Register; 0x0000006E ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS3A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS3B       :1;                                       /* Edge/Level Select Bit B */
    byte MS3A        :1;                                       /* Mode Select A for TPM Channel 3 */
    byte MS3B        :1;                                       /* Mode Select B for TPM Channel 3 */
    byte CH3IE       :1;                                       /* Channel 3 Interrupt Enable */
    byte CH3F        :1;                                       /* Channel 3 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS3x :2;
    byte grpMS3x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C3SCSTR;
extern volatile TPM2C3SCSTR _TPM2C3SC @0x0000006E;
#define TPM2C3SC                        _TPM2C3SC.Byte
#define TPM2C3SC_ELS3A                  _TPM2C3SC.Bits.ELS3A
#define TPM2C3SC_ELS3B                  _TPM2C3SC.Bits.ELS3B
#define TPM2C3SC_MS3A                   _TPM2C3SC.Bits.MS3A
#define TPM2C3SC_MS3B                   _TPM2C3SC.Bits.MS3B
#define TPM2C3SC_CH3IE                  _TPM2C3SC.Bits.CH3IE
#define TPM2C3SC_CH3F                   _TPM2C3SC.Bits.CH3F
#define TPM2C3SC_ELS3x                  _TPM2C3SC.MergedBits.grpELS3x
#define TPM2C3SC_MS3x                   _TPM2C3SC.MergedBits.grpMS3x

#define TPM2C3SC_ELS3A_MASK             4U
#define TPM2C3SC_ELS3B_MASK             8U
#define TPM2C3SC_MS3A_MASK              16U
#define TPM2C3SC_MS3B_MASK              32U
#define TPM2C3SC_CH3IE_MASK             64U
#define TPM2C3SC_CH3F_MASK              128U
#define TPM2C3SC_ELS3x_MASK             12U
#define TPM2C3SC_ELS3x_BITNUM           2U
#define TPM2C3SC_MS3x_MASK              48U
#define TPM2C3SC_MS3x_BITNUM            4U


/*** TPM2C3V - TPM 2 Timer Channel 3 Value Register; 0x0000006F ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C3VH - TPM 2 Timer Channel 3 Value Register High; 0x0000006F ***/
    union {
      byte Byte;
    } TPM2C3VHSTR;
    #define TPM2C3VH                    _TPM2C3V.Overlap_STR.TPM2C3VHSTR.Byte


    /*** TPM2C3VL - TPM 2 Timer Channel 3 Value Register Low; 0x00000070 ***/
    union {
      byte Byte;
    } TPM2C3VLSTR;
    #define TPM2C3VL                    _TPM2C3V.Overlap_STR.TPM2C3VLSTR.Byte

  } Overlap_STR;

} TPM2C3VSTR;
extern volatile TPM2C3VSTR _TPM2C3V @0x0000006F;
#define TPM2C3V                         _TPM2C3V.Word


/*** TPM2C4SC - TPM 2 Timer Channel 4 Status and Control Register; 0x00000071 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte ELS4A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS4B       :1;                                       /* Edge/Level Select Bit B */
    byte MS4A        :1;                                       /* Mode Select A for TPM Channel 4 */
    byte MS4B        :1;                                       /* Mode Select B for TPM Channel 4 */
    byte CH4IE       :1;                                       /* Channel 4 Interrupt Enable */
    byte CH4F        :1;                                       /* Channel 4 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS4x :2;
    byte grpMS4x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C4SCSTR;
extern volatile TPM2C4SCSTR _TPM2C4SC @0x00000071;
#define TPM2C4SC                        _TPM2C4SC.Byte
#define TPM2C4SC_ELS4A                  _TPM2C4SC.Bits.ELS4A
#define TPM2C4SC_ELS4B                  _TPM2C4SC.Bits.ELS4B
#define TPM2C4SC_MS4A                   _TPM2C4SC.Bits.MS4A
#define TPM2C4SC_MS4B                   _TPM2C4SC.Bits.MS4B
#define TPM2C4SC_CH4IE                  _TPM2C4SC.Bits.CH4IE
#define TPM2C4SC_CH4F                   _TPM2C4SC.Bits.CH4F
#define TPM2C4SC_ELS4x                  _TPM2C4SC.MergedBits.grpELS4x
#define TPM2C4SC_MS4x                   _TPM2C4SC.MergedBits.grpMS4x

#define TPM2C4SC_ELS4A_MASK             4U
#define TPM2C4SC_ELS4B_MASK             8U
#define TPM2C4SC_MS4A_MASK              16U
#define TPM2C4SC_MS4B_MASK              32U
#define TPM2C4SC_CH4IE_MASK             64U
#define TPM2C4SC_CH4F_MASK              128U
#define TPM2C4SC_ELS4x_MASK             12U
#define TPM2C4SC_ELS4x_BITNUM           2U
#define TPM2C4SC_MS4x_MASK              48U
#define TPM2C4SC_MS4x_BITNUM            4U


/*** TPM2C4V - TPM 2 Timer Channel 4 Value Register; 0x00000072 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C4VH - TPM 2 Timer Channel 4 Value Register High; 0x00000072 ***/
    union {
      byte Byte;
    } TPM2C4VHSTR;
    #define TPM2C4VH                    _TPM2C4V.Overlap_STR.TPM2C4VHSTR.Byte


    /*** TPM2C4VL - TPM 2 Timer Channel 4 Value Register Low; 0x00000073 ***/
    union {
      byte Byte;
    } TPM2C4VLSTR;
    #define TPM2C4VL                    _TPM2C4V.Overlap_STR.TPM2C4VLSTR.Byte

  } Overlap_STR;

} TPM2C4VSTR;
extern volatile TPM2C4VSTR _TPM2C4V @0x00000072;
#define TPM2C4V                         _TPM2C4V.Word


/*** SRS - System Reset Status; 0x00001800 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte LVD         :1;                                       /* Low Voltage Detect */
    byte ICG         :1;                                       /* Internal Clock Generation Module Reset */
    byte             :1;
    byte ILOP        :1;                                       /* Illegal Opcode */
    byte COP         :1;                                       /* Computer Operating Properly (COP) Watchdog */
    byte PIN         :1;                                       /* External Reset Pin */
    byte POR         :1;                                       /* Power-On Reset */
  } Bits;
} SRSSTR;
extern volatile SRSSTR _SRS @0x00001800;
#define SRS                             _SRS.Byte
#define SRS_LVD                         _SRS.Bits.LVD
#define SRS_ICG                         _SRS.Bits.ICG
#define SRS_ILOP                        _SRS.Bits.ILOP
#define SRS_COP                         _SRS.Bits.COP
#define SRS_PIN                         _SRS.Bits.PIN
#define SRS_POR                         _SRS.Bits.POR

#define SRS_LVD_MASK                    2U
#define SRS_ICG_MASK                    4U
#define SRS_ILOP_MASK                   16U
#define SRS_COP_MASK                    32U
#define SRS_PIN_MASK                    64U
#define SRS_POR_MASK                    128U


/*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***/
typedef union {
  byte Byte;
  struct {
    byte BDFR        :1;                                       /* Background Debug Force Reset */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
  } Bits;
} SBDFRSTR;
extern volatile SBDFRSTR _SBDFR @0x00001801;
#define SBDFR                           _SBDFR.Byte
#define SBDFR_BDFR                      _SBDFR.Bits.BDFR

#define SBDFR_BDFR_MASK                 1U


/*** SOPT - System Options Register; 0x00001802 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte BKGDPE      :1;                                       /* Background Debug Mode Pin Enable */
    byte             :1;
    byte             :1;
    byte             :1;
    byte STOPE       :1;                                       /* Stop Mode Enable */
    byte COPT        :1;                                       /* COP Watchdog Timeout */
    byte COPE        :1;                                       /* COP Watchdog Enable */
  } Bits;
} SOPTSTR;
extern volatile SOPTSTR _SOPT @0x00001802;
#define SOPT                            _SOPT.Byte
#define SOPT_BKGDPE                     _SOPT.Bits.BKGDPE
#define SOPT_STOPE                      _SOPT.Bits.STOPE
#define SOPT_COPT                       _SOPT.Bits.COPT
#define SOPT_COPE                       _SOPT.Bits.COPE

#define SOPT_BKGDPE_MASK                2U
#define SOPT_STOPE_MASK                 32U
#define SOPT_COPT_MASK                  64U
#define SOPT_COPE_MASK                  128U


/*** SDID - System Integration Module Part ID Register; 0x00001806 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SDIDH - System Integration Module Part ID Register High; 0x00001806 ***/
    union {
      byte Byte;
      struct {
        byte ID8         :1;                                       /* Part Identification Number 8 */
        byte ID9         :1;                                       /* Part Identification Number 9 */
        byte ID10        :1;                                       /* Part Identification Number 10 */
        byte ID11        :1;                                       /* Part Identification Number 11 */
        byte REV0        :1;                                       /* Revision Number 0 */
        byte REV1        :1;                                       /* Revision Number 1 */
        byte REV2        :1;                                       /* Revision Number 2 */
        byte REV3        :1;                                       /* Revision Number 3 */
      } Bits;
      struct {
        byte grpID_8 :4;
        byte grpREV :4;
      } MergedBits;
    } SDIDHSTR;
    #define SDIDH                       _SDID.Overlap_STR.SDIDHSTR.Byte
    #define SDIDH_ID8                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID8
    #define SDIDH_ID9                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID9
    #define SDIDH_ID10                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID10
    #define SDIDH_ID11                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID11
    #define SDIDH_REV0                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV0
    #define SDIDH_REV1                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV1
    #define SDIDH_REV2                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV2
    #define SDIDH_REV3                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV3
    #define SDIDH_ID_8                  _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpID_8
    #define SDIDH_REV                   _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpREV
    #define SDIDH_ID                    SDIDH_ID_8

    #define SDIDH_ID8_MASK              1U
    #define SDIDH_ID9_MASK              2U
    #define SDIDH_ID10_MASK             4U
    #define SDIDH_ID11_MASK             8U
    #define SDIDH_REV0_MASK             16U
    #define SDIDH_REV1_MASK             32U
    #define SDIDH_REV2_MASK             64U
    #define SDIDH_REV3_MASK             128U
    #define SDIDH_ID_8_MASK             15U
    #define SDIDH_ID_8_BITNUM           0U
    #define SDIDH_REV_MASK              240U
    #define SDIDH_REV_BITNUM            4U


    /*** SDIDL - System Integration Module Part ID Register Low; 0x00001807 ***/
    union {
      byte Byte;
      struct {
        byte ID0         :1;                                       /* Part Identification Number 0 */
        byte ID1         :1;                                       /* Part Identification Number 1 */
        byte ID2         :1;                                       /* Part Identification Number 2 */
        byte ID3         :1;                                       /* Part Identification Number 3 */
        byte ID4         :1;                                       /* Part Identification Number 4 */
        byte ID5         :1;                                       /* Part Identification Number 5 */
        byte ID6         :1;                                       /* Part Identification Number 6 */
        byte ID7         :1;                                       /* Part Identification Number 7 */
      } Bits;
    } SDIDLSTR;
    #define SDIDL                       _SDID.Overlap_STR.SDIDLSTR.Byte
    #define SDIDL_ID0                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID0
    #define SDIDL_ID1                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID1
    #define SDIDL_ID2                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID2
    #define SDIDL_ID3                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID3
    #define SDIDL_ID4                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID4
    #define SDIDL_ID5                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID5
    #define SDIDL_ID6                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID6
    #define SDIDL_ID7                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID7

    #define SDIDL_ID0_MASK              1U
    #define SDIDL_ID1_MASK              2U
    #define SDIDL_ID2_MASK              4U
    #define SDIDL_ID3_MASK              8U
    #define SDIDL_ID4_MASK              16U
    #define SDIDL_ID5_MASK              32U
    #define SDIDL_ID6_MASK              64U
    #define SDIDL_ID7_MASK              128U

  } Overlap_STR;

} SDIDSTR;
extern volatile SDIDSTR _SDID @0x00001806;
#define SDID                            _SDID.Word


/*** SRTISC - System RTI Status and Control Register; 0x00001808 ***/
typedef union {
  byte Byte;
  struct {
    byte RTIS0       :1;                                       /* Real-Time Interrupt Delay Select Bit 0 */
    byte RTIS1       :1;                                       /* Real-Time Interrupt Delay Select Bit 1 */
    byte RTIS2       :1;                                       /* Real-Time Interrupt Delay Select Bit 2 */
    byte             :1;
    byte RTIE        :1;                                       /* Real-Time Interrupt Enable */
    byte RTICLKS     :1;                                       /* Real-Time Interrupt Clock Select */
    byte RTIACK      :1;                                       /* Real-Time Interrupt Acknowledge */
    byte RTIF        :1;                                       /* Real-Time Interrupt Flag */
  } Bits;
  struct {
    byte grpRTIS :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SRTISCSTR;
extern volatile SRTISCSTR _SRTISC @0x00001808;
#define SRTISC                          _SRTISC.Byte
#define SRTISC_RTIS0                    _SRTISC.Bits.RTIS0
#define SRTISC_RTIS1                    _SRTISC.Bits.RTIS1
#define SRTISC_RTIS2                    _SRTISC.Bits.RTIS2
#define SRTISC_RTIE                     _SRTISC.Bits.RTIE
#define SRTISC_RTICLKS                  _SRTISC.Bits.RTICLKS
#define SRTISC_RTIACK                   _SRTISC.Bits.RTIACK
#define SRTISC_RTIF                     _SRTISC.Bits.RTIF
#define SRTISC_RTIS                     _SRTISC.MergedBits.grpRTIS

#define SRTISC_RTIS0_MASK               1U
#define SRTISC_RTIS1_MASK               2U
#define SRTISC_RTIS2_MASK               4U
#define SRTISC_RTIE_MASK                16U
#define SRTISC_RTICLKS_MASK             32U
#define SRTISC_RTIACK_MASK              64U
#define SRTISC_RTIF_MASK                128U
#define SRTISC_RTIS_MASK                7U
#define SRTISC_RTIS_BITNUM              0U


/*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit8        :1;                                       /* Debug Comparator A Bit 8 */
    byte Bit9        :1;                                       /* Debug Comparator A Bit 9 */
    byte Bit10       :1;                                       /* Debug Comparator A Bit 10 */
    byte Bit11       :1;                                       /* Debug Comparator A Bit 11 */
    byte Bit12       :1;                                       /* Debug Comparator A Bit 12 */
    byte Bit13       :1;                                       /* Debug Comparator A Bit 13 */
    byte Bit14       :1;                                       /* Debug Comparator A Bit 14 */
    byte Bit15       :1;                                       /* Debug Comparator A Bit 15 */
  } Bits;
} DBGCAHSTR;
extern volatile DBGCAHSTR _DBGCAH @0x00001810;
#define DBGCAH                          _DBGCAH.Byte
#define DBGCAH_Bit8                     _DBGCAH.Bits.Bit8
#define DBGCAH_Bit9                     _DBGCAH.Bits.Bit9
#define DBGCAH_Bit10                    _DBGCAH.Bits.Bit10
#define DBGCAH_Bit11                    _DBGCAH.Bits.Bit11
#define DBGCAH_Bit12                    _DBGCAH.Bits.Bit12
#define DBGCAH_Bit13                    _DBGCAH.Bits.Bit13
#define DBGCAH_Bit14                    _DBGCAH.Bits.Bit14
#define DBGCAH_Bit15                    _DBGCAH.Bits.Bit15

#define DBGCAH_Bit8_MASK                1U
#define DBGCAH_Bit9_MASK                2U
#define DBGCAH_Bit10_MASK               4U
#define DBGCAH_Bit11_MASK               8U
#define DBGCAH_Bit12_MASK               16U
#define DBGCAH_Bit13_MASK               32U
#define DBGCAH_Bit14_MASK               64U
#define DBGCAH_Bit15_MASK               128U


/*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit0        :1;                                       /* Debug Comparator A Bit 0 */
    byte Bit1        :1;                                       /* Debug Comparator A Bit 1 */
    byte Bit2        :1;                                       /* Debug Comparator A Bit 2 */
    byte Bit3        :1;                                       /* Debug Comparator A Bit 3 */
    byte Bit4        :1;                                       /* Debug Comparator A Bit 4 */
    byte Bit5        :1;                                       /* Debug Comparator A Bit 5 */
    byte Bit6        :1;                                       /* Debug Comparator A Bit 6 */
    byte Bit7        :1;                                       /* Debug Comparator A Bit 7 */
  } Bits;
} DBGCALSTR;
extern volatile DBGCALSTR _DBGCAL @0x00001811;
#define DBGCAL                          _DBGCAL.Byte
#define DBGCAL_Bit0                     _DBGCAL.Bits.Bit0
#define DBGCAL_Bit1                     _DBGCAL.Bits.Bit1
#define DBGCAL_Bit2                     _DBGCAL.Bits.Bit2
#define DBGCAL_Bit3                     _DBGCAL.Bits.Bit3
#define DBGCAL_Bit4                     _DBGCAL.Bits.Bit4
#define DBGCAL_Bit5                     _DBGCAL.Bits.Bit5
#define DBGCAL_Bit6                     _DBGCAL.Bits.Bit6
#define DBGCAL_Bit7                     _DBGCAL.Bits.Bit7

#define DBGCAL_Bit0_MASK                1U
#define DBGCAL_Bit1_MASK                2U
#define DBGCAL_Bit2_MASK                4U
#define DBGCAL_Bit3_MASK                8U
#define DBGCAL_Bit4_MASK                16U
#define DBGCAL_Bit5_MASK                32U
#define DBGCAL_Bit6_MASK                64U
#define DBGCAL_Bit7_MASK                128U


/*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit8        :1;                                       /* Debug Comparator B Bit 8 */
    byte Bit9        :1;                                       /* Debug Comparator B Bit 9 */
    byte Bit10       :1;                                       /* Debug Comparator B Bit 10 */
    byte Bit11       :1;                                       /* Debug Comparator B Bit 11 */
    byte Bit12       :1;                                       /* Debug Comparator B Bit 12 */
    byte Bit13       :1;                                       /* Debug Comparator B Bit 13 */
    byte Bit14       :1;                                       /* Debug Comparator B Bit 14 */
    byte Bit15       :1;                                       /* Debug Comparator B Bit 15 */
  } Bits;
} DBGCBHSTR;
extern volatile DBGCBHSTR _DBGCBH @0x00001812;
#define DBGCBH                          _DBGCBH.Byte
#define DBGCBH_Bit8                     _DBGCBH.Bits.Bit8
#define DBGCBH_Bit9                     _DBGCBH.Bits.Bit9
#define DBGCBH_Bit10                    _DBGCBH.Bits.Bit10
#define DBGCBH_Bit11                    _DBGCBH.Bits.Bit11
#define DBGCBH_Bit12                    _DBGCBH.Bits.Bit12
#define DBGCBH_Bit13                    _DBGCBH.Bits.Bit13
#define DBGCBH_Bit14                    _DBGCBH.Bits.Bit14
#define DBGCBH_Bit15                    _DBGCBH.Bits.Bit15

#define DBGCBH_Bit8_MASK                1U
#define DBGCBH_Bit9_MASK                2U
#define DBGCBH_Bit10_MASK               4U
#define DBGCBH_Bit11_MASK               8U
#define DBGCBH_Bit12_MASK               16U
#define DBGCBH_Bit13_MASK               32U
#define DBGCBH_Bit14_MASK               64U
#define DBGCBH_Bit15_MASK               128U


/*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit0        :1;                                       /* Debug Comparator B Bit 0 */
    byte Bit1        :1;                                       /* Debug Comparator B Bit 1 */
    byte Bit2        :1;                                       /* Debug Comparator B Bit 2 */
    byte Bit3        :1;                                       /* Debug Comparator B Bit 3 */
    byte Bit4        :1;                                       /* Debug Comparator B Bit 4 */
    byte Bit5        :1;                                       /* Debug Comparator B Bit 5 */
    byte Bit6        :1;                                       /* Debug Comparator B Bit 6 */
    byte Bit7        :1;                                       /* Debug Comparator B Bit 7 */
  } Bits;
} DBGCBLSTR;
extern volatile DBGCBLSTR _DBGCBL @0x00001813;
#define DBGCBL                          _DBGCBL.Byte
#define DBGCBL_Bit0                     _DBGCBL.Bits.Bit0
#define DBGCBL_Bit1                     _DBGCBL.Bits.Bit1
#define DBGCBL_Bit2                     _DBGCBL.Bits.Bit2
#define DBGCBL_Bit3                     _DBGCBL.Bits.Bit3
#define DBGCBL_Bit4                     _DBGCBL.Bits.Bit4
#define DBGCBL_Bit5                     _DBGCBL.Bits.Bit5
#define DBGCBL_Bit6                     _DBGCBL.Bits.Bit6
#define DBGCBL_Bit7                     _DBGCBL.Bits.Bit7

#define DBGCBL_Bit0_MASK                1U
#define DBGCBL_Bit1_MASK                2U
#define DBGCBL_Bit2_MASK                4U
#define DBGCBL_Bit3_MASK                8U
#define DBGCBL_Bit4_MASK                16U
#define DBGCBL_Bit5_MASK                32U
#define DBGCBL_Bit6_MASK                64U
#define DBGCBL_Bit7_MASK                128U


/*** DBGF - Debug FIFO Register; 0x00001814 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGFH - Debug FIFO High Register; 0x00001814 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Debug FIFO Bit 8 */
        byte Bit9        :1;                                       /* Debug FIFO Bit 9 */
        byte Bit10       :1;                                       /* Debug FIFO Bit 10 */
        byte Bit11       :1;                                       /* Debug FIFO Bit 11 */
        byte Bit12       :1;                                       /* Debug FIFO Bit 12 */
        byte Bit13       :1;                                       /* Debug FIFO Bit 13 */
        byte Bit14       :1;                                       /* Debug FIFO Bit 14 */
        byte Bit15       :1;                                       /* Debug FIFO Bit 15 */
      } Bits;
    } DBGFHSTR;
    #define DBGFH                       _DBGF.Overlap_STR.DBGFHSTR.Byte
    #define DBGFH_Bit8                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit8
    #define DBGFH_Bit9                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit9
    #define DBGFH_Bit10                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit10
    #define DBGFH_Bit11                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit11
    #define DBGFH_Bit12                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit12
    #define DBGFH_Bit13                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit13
    #define DBGFH_Bit14                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit14
    #define DBGFH_Bit15                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit15

    #define DBGFH_Bit8_MASK             1U
    #define DBGFH_Bit9_MASK             2U
    #define DBGFH_Bit10_MASK            4U
    #define DBGFH_Bit11_MASK            8U
    #define DBGFH_Bit12_MASK            16U
    #define DBGFH_Bit13_MASK            32U
    #define DBGFH_Bit14_MASK            64U
    #define DBGFH_Bit15_MASK            128U


    /*** DBGFL - Debug FIFO Low Register; 0x00001815 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Debug FIFO Bit 0 */
        byte Bit1        :1;                                       /* Debug FIFO Bit 1 */
        byte Bit2        :1;                                       /* Debug FIFO Bit 2 */
        byte Bit3        :1;                                       /* Debug FIFO Bit 3 */
        byte Bit4        :1;                                       /* Debug FIFO Bit 4 */
        byte Bit5        :1;                                       /* Debug FIFO Bit 5 */
        byte Bit6        :1;                                       /* Debug FIFO Bit 6 */
        byte Bit7        :1;                                       /* Debug FIFO Bit 7 */
      } Bits;
    } DBGFLSTR;
    #define DBGFL                       _DBGF.Overlap_STR.DBGFLSTR.Byte
    #define DBGFL_Bit0                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit0
    #define DBGFL_Bit1                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit1
    #define DBGFL_Bit2                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit2
    #define DBGFL_Bit3                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit3
    #define DBGFL_Bit4                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit4
    #define DBGFL_Bit5                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit5
    #define DBGFL_Bit6                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit6
    #define DBGFL_Bit7                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit7

    #define DBGFL_Bit0_MASK             1U
    #define DBGFL_Bit1_MASK             2U
    #define DBGFL_Bit2_MASK             4U
    #define DBGFL_Bit3_MASK             8U
    #define DBGFL_Bit4_MASK             16U
    #define DBGFL_Bit5_MASK             32U
    #define DBGFL_Bit6_MASK             64U
    #define DBGFL_Bit7_MASK             128U

  } Overlap_STR;

} DBGFSTR;
extern volatile DBGFSTR _DBGF @0x00001814;
#define DBGF                            _DBGF.Word


/*** DBGC - Debug Control Register; 0x00001816 ***/
typedef union {
  byte Byte;
  struct {
    byte RWBEN       :1;                                       /* Enable R/W for Comparator B */
    byte RWB         :1;                                       /* R/W Comparison Value for Comparator B */
    byte RWAEN       :1;                                       /* Enable R/W for Comparator A */
    byte RWA         :1;                                       /* R/W Comparison Value for Comparator A */
    byte BRKEN       :1;                                       /*  Break Enable */
    byte TAG         :1;                                       /* Tag/Force Select */
    byte ARM         :1;                                       /* Arm Control */
    byte DBGEN       :1;                                       /* Debug Module Enable */
  } Bits;
} DBGCSTR;
extern volatile DBGCSTR _DBGC @0x00001816;
#define DBGC                            _DBGC.Byte
#define DBGC_RWBEN                      _DBGC.Bits.RWBEN
#define DBGC_RWB                        _DBGC.Bits.RWB
#define DBGC_RWAEN                      _DBGC.Bits.RWAEN
#define DBGC_RWA                        _DBGC.Bits.RWA
#define DBGC_BRKEN                      _DBGC.Bits.BRKEN
#define DBGC_TAG                        _DBGC.Bits.TAG
#define DBGC_ARM                        _DBGC.Bits.ARM
#define DBGC_DBGEN                      _DBGC.Bits.DBGEN

#define DBGC_RWBEN_MASK                 1U
#define DBGC_RWB_MASK                   2U
#define DBGC_RWAEN_MASK                 4U
#define DBGC_RWA_MASK                   8U
#define DBGC_BRKEN_MASK                 16U
#define DBGC_TAG_MASK                   32U
#define DBGC_ARM_MASK                   64U
#define DBGC_DBGEN_MASK                 128U


/*** DBGT - Debug Trigger Register; 0x00001817 ***/
typedef union {
  byte Byte;
  struct {
    byte TRG0        :1;                                       /* Select Trigger Mode Bit 0 */
    byte TRG1        :1;                                       /* Select Trigger Mode Bit 1 */
    byte TRG2        :1;                                       /* Select Trigger Mode Bit 2 */
    byte TRG3        :1;                                       /* Select Trigger Mode Bit 3 */
    byte             :1;
    byte             :1;
    byte BEGIN       :1;                                       /* Begin/End Trigger Select */
    byte TRGSEL      :1;                                       /* Trigger Type */
  } Bits;
  struct {
    byte grpTRG  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGTSTR;
extern volatile DBGTSTR _DBGT @0x00001817;
#define DBGT                            _DBGT.Byte
#define DBGT_TRG0                       _DBGT.Bits.TRG0
#define DBGT_TRG1                       _DBGT.Bits.TRG1
#define DBGT_TRG2                       _DBGT.Bits.TRG2
#define DBGT_TRG3                       _DBGT.Bits.TRG3
#define DBGT_BEGIN                      _DBGT.Bits.BEGIN
#define DBGT_TRGSEL                     _DBGT.Bits.TRGSEL
#define DBGT_TRG                        _DBGT.MergedBits.grpTRG

#define DBGT_TRG0_MASK                  1U
#define DBGT_TRG1_MASK                  2U
#define DBGT_TRG2_MASK                  4U
#define DBGT_TRG3_MASK                  8U
#define DBGT_BEGIN_MASK                 64U
#define DBGT_TRGSEL_MASK                128U
#define DBGT_TRG_MASK                   15U
#define DBGT_TRG_BITNUM                 0U


/*** DBGS - Debug Status Register; 0x00001818 ***/
typedef union {
  byte Byte;
  struct {
    byte CNT0        :1;                                       /* FIFO Valid Count Bit 0 */
    byte CNT1        :1;                                       /* FIFO Valid Count Bit 1 */
    byte CNT2        :1;                                       /* FIFO Valid Count Bit 2 */
    byte CNT3        :1;                                       /* FIFO Valid Count Bit 3 */
    byte             :1;
    byte ARMF        :1;                                       /* Arm Flag */
    byte BF          :1;                                       /* Trigger Match B Flag */
    byte AF          :1;                                       /* Trigger Match A Flag */
  } Bits;
  struct {
    byte grpCNT  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGSSTR;
extern volatile DBGSSTR _DBGS @0x00001818;
#define DBGS                            _DBGS.Byte
#define DBGS_CNT0                       _DBGS.Bits.CNT0
#define DBGS_CNT1                       _DBGS.Bits.CNT1
#define DBGS_CNT2                       _DBGS.Bits.CNT2
#define DBGS_CNT3                       _DBGS.Bits.CNT3
#define DBGS_ARMF                       _DBGS.Bits.ARMF
#define DBGS_BF                         _DBGS.Bits.BF
#define DBGS_AF                         _DBGS.Bits.AF
#define DBGS_CNT                        _DBGS.MergedBits.grpCNT

#define DBGS_CNT0_MASK                  1U
#define DBGS_CNT1_MASK                  2U
#define DBGS_CNT2_MASK                  4U
#define DBGS_CNT3_MASK                  8U
#define DBGS_ARMF_MASK                  32U
#define DBGS_BF_MASK                    64U
#define DBGS_AF_MASK                    128U
#define DBGS_CNT_MASK                   15U
#define DBGS_CNT_BITNUM                 0U


/*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***/
typedef union {
  byte Byte;
  struct {
    byte DIV0        :1;                                       /* Divisor for FLASH Clock Divider Bit 0 */
    byte DIV1        :1;                                       /* Divisor for FLASH Clock Divider Bit 1 */
    byte DIV2        :1;                                       /* Divisor for FLASH Clock Divider Bit 2 */
    byte DIV3        :1;                                       /* Divisor for FLASH Clock Divider Bit 3 */
    byte DIV4        :1;                                       /* Divisor for FLASH Clock Divider Bit 4 */
    byte DIV5        :1;                                       /* Divisor for FLASH Clock Divider Bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte DIVLD       :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpDIV  :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} FCDIVSTR;
extern volatile FCDIVSTR _FCDIV @0x00001820;
#define FCDIV                           _FCDIV.Byte
#define FCDIV_DIV0                      _FCDIV.Bits.DIV0
#define FCDIV_DIV1                      _FCDIV.Bits.DIV1
#define FCDIV_DIV2                      _FCDIV.Bits.DIV2
#define FCDIV_DIV3                      _FCDIV.Bits.DIV3
#define FCDIV_DIV4                      _FCDIV.Bits.DIV4
#define FCDIV_DIV5                      _FCDIV.Bits.DIV5
#define FCDIV_PRDIV8                    _FCDIV.Bits.PRDIV8
#define FCDIV_DIVLD                     _FCDIV.Bits.DIVLD
#define FCDIV_DIV                       _FCDIV.MergedBits.grpDIV

#define FCDIV_DIV0_MASK                 1U
#define FCDIV_DIV1_MASK                 2U
#define FCDIV_DIV2_MASK                 4U
#define FCDIV_DIV3_MASK                 8U
#define FCDIV_DIV4_MASK                 16U
#define FCDIV_DIV5_MASK                 32U
#define FCDIV_PRDIV8_MASK               64U
#define FCDIV_DIVLD_MASK                128U
#define FCDIV_DIV_MASK                  63U
#define FCDIV_DIV_BITNUM                0U


/*** FOPT - FLASH Options Register; 0x00001821 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code Bit 0 */
    byte SEC01       :1;                                       /* Security State Code Bit 1 */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} FOPTSTR;
extern volatile FOPTSTR _FOPT @0x00001821;
#define FOPT                            _FOPT.Byte
#define FOPT_SEC00                      _FOPT.Bits.SEC00
#define FOPT_SEC01                      _FOPT.Bits.SEC01
#define FOPT_FNORED                     _FOPT.Bits.FNORED
#define FOPT_KEYEN                      _FOPT.Bits.KEYEN
#define FOPT_SEC0                       _FOPT.MergedBits.grpSEC0

#define FOPT_SEC00_MASK                 1U
#define FOPT_SEC01_MASK                 2U
#define FOPT_FNORED_MASK                64U
#define FOPT_KEYEN_MASK                 128U
#define FOPT_SEC0_MASK                  3U
#define FOPT_SEC0_BITNUM                0U


/*** FPROT - FLASH Protection Register; 0x00001824 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte             :1;
    byte FPS0        :1;                                       /* FLASH Protect Size Select Bit 0 */
    byte FPS1        :1;                                       /* FLASH Protect Size Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Size Select Bit 2 */
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPOPEN      :1;                                       /* Open Unprotected FLASH for Program/Erase */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpFPS  :3;
    byte         :1;
    byte         :1;
  } MergedBits;
} FPROTSTR;
extern volatile FPROTSTR _FPROT @0x00001824;
#define FPROT                           _FPROT.Byte
#define FPROT_FPS0                      _FPROT.Bits.FPS0
#define FPROT_FPS1                      _FPROT.Bits.FPS1
#define FPROT_FPS2                      _FPROT.Bits.FPS2
#define FPROT_FPDIS                     _FPROT.Bits.FPDIS
#define FPROT_FPOPEN                    _FPROT.Bits.FPOPEN
#define FPROT_FPS                       _FPROT.MergedBits.grpFPS

#define FPROT_FPS0_MASK                 8U
#define FPROT_FPS1_MASK                 16U
#define FPROT_FPS2_MASK                 32U
#define FPROT_FPDIS_MASK                64U
#define FPROT_FPOPEN_MASK               128U
#define FPROT_FPS_MASK                  56U
#define FPROT_FPS_BITNUM                3U


/*** FSTAT - FLASH Status Register; 0x00001825 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte FBLANK      :1;                                       /* FLASH Verified as All Blank (erased) Flag */
    byte             :1;
    byte FACCERR     :1;                                       /* Access Error Flag */
    byte FPVIOL      :1;                                       /* Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} FSTATSTR;
extern volatile FSTATSTR _FSTAT @0x00001825;
#define FSTAT                           _FSTAT.Byte
#define FSTAT_FBLANK                    _FSTAT.Bits.FBLANK
#define FSTAT_FACCERR                   _FSTAT.Bits.FACCERR
#define FSTAT_FPVIOL                    _FSTAT.Bits.FPVIOL
#define FSTAT_FCCF                      _FSTAT.Bits.FCCF
#define FSTAT_FCBEF                     _FSTAT.Bits.FCBEF

#define FSTAT_FBLANK_MASK               4U
#define FSTAT_FACCERR_MASK              16U
#define FSTAT_FPVIOL_MASK               32U
#define FSTAT_FCCF_MASK                 64U
#define FSTAT_FCBEF_MASK                128U


/*** FCMD - FLASH Command Register; 0x00001826 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* FLASH Command Bit 0 */
    byte FCMD1       :1;                                       /* FLASH Command Bit 1 */
    byte FCMD2       :1;                                       /* FLASH Command Bit 2 */
    byte FCMD3       :1;                                       /* FLASH Command Bit 3 */
    byte FCMD4       :1;                                       /* FLASH Command Bit 4 */
    byte FCMD5       :1;                                       /* FLASH Command Bit 5 */
    byte FCMD6       :1;                                       /* FLASH Command Bit 6 */
    byte FCMD7       :1;                                       /* FLASH Command Bit 7 */
  } Bits;
} FCMDSTR;
extern volatile FCMDSTR _FCMD @0x00001826;
#define FCMD                            _FCMD.Byte
#define FCMD_FCMD0                      _FCMD.Bits.FCMD0
#define FCMD_FCMD1                      _FCMD.Bits.FCMD1
#define FCMD_FCMD2                      _FCMD.Bits.FCMD2
#define FCMD_FCMD3                      _FCMD.Bits.FCMD3
#define FCMD_FCMD4                      _FCMD.Bits.FCMD4
#define FCMD_FCMD5                      _FCMD.Bits.FCMD5
#define FCMD_FCMD6                      _FCMD.Bits.FCMD6
#define FCMD_FCMD7                      _FCMD.Bits.FCMD7

#define FCMD_FCMD0_MASK                 1U
#define FCMD_FCMD1_MASK                 2U
#define FCMD_FCMD2_MASK                 4U
#define FCMD_FCMD3_MASK                 8U
#define FCMD_FCMD4_MASK                 16U
#define FCMD_FCMD5_MASK                 32U
#define FCMD_FCMD6_MASK                 64U
#define FCMD_FCMD7_MASK                 128U


/*** NVPROT - Nonvolatile FLASH Protection Register; 0x0000FFBD ***/
typedef union {
  byte Byte;
  struct {
    byte             :1;
    byte             :1;
    byte             :1;
    byte FPS0        :1;                                       /* FLASH Protect Size Select Bit 0 */
    byte FPS1        :1;                                       /* FLASH Protect Size Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Size Select Bit 2 */
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPOPEN      :1;                                       /* Open Unprotected FLASH for Program/Erase */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpFPS  :3;
    byte         :1;
    byte         :1;
  } MergedBits;
} NVPROTSTR;
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
#define _NVPROT (*(const NVPROTSTR * __far)0x0000FFBD)
#define NVPROT                          _NVPROT.Byte
#define NVPROT_FPS0                     _NVPROT.Bits.FPS0
#define NVPROT_FPS1                     _NVPROT.Bits.FPS1
#define NVPROT_FPS2                     _NVPROT.Bits.FPS2
#define NVPROT_FPDIS                    _NVPROT.Bits.FPDIS
#define NVPROT_FPOPEN                   _NVPROT.Bits.FPOPEN
#define NVPROT_FPS                      _NVPROT.MergedBits.grpFPS

#define NVPROT_FPS0_MASK                8U
#define NVPROT_FPS1_MASK                16U
#define NVPROT_FPS2_MASK                32U
#define NVPROT_FPDIS_MASK               64U
#define NVPROT_FPOPEN_MASK              128U
#define NVPROT_FPS_MASK                 56U
#define NVPROT_FPS_BITNUM               3U


/*** NVOPT - Nonvolatile FLASH Options Register; 0x0000FFBF ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code Bit 0 */
    byte SEC01       :1;                                       /* Security State Code Bit 1 */
    byte             :1;
    byte             :1;
    byte             :1;
    byte             :1;
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} NVOPTSTR;
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */
#define _NVOPT (*(const NVOPTSTR * __far)0x0000FFBF)
#define NVOPT                           _NVOPT.Byte
#define NVOPT_SEC00                     _NVOPT.Bits.SEC00
#define NVOPT_SEC01                     _NVOPT.Bits.SEC01
#define NVOPT_FNORED                    _NVOPT.Bits.FNORED
#define NVOPT_KEYEN                     _NVOPT.Bits.KEYEN
#define NVOPT_SEC0                      _NVOPT.MergedBits.grpSEC0

#define NVOPT_SEC00_MASK                1U
#define NVOPT_SEC01_MASK                2U
#define NVOPT_FNORED_MASK               64U
#define NVOPT_KEYEN_MASK                128U
#define NVOPT_SEC0_MASK                 3U
#define NVOPT_SEC0_BITNUM               0U



/* Flash commands */
#define mBlank                          0x05
#define mByteProg                       0x20
#define mBurstProg                      0x25
#define mMassErase                      0x41
#define mPageErase                      0x40

// 7 segment displays
extern volatile byte HEX3 @0x00000001;
extern volatile byte HEX2 @0x00000002;
extern volatile byte HEX1 @0x00000005;
extern volatile byte HEX0 @0x00000006;

// LEDs
typedef union {
	byte	Byte;
	struct {
		byte LED0	: 1;
		byte LED1	: 1;
		byte LED2	: 1;
		byte LED3	: 1;
		byte LED4	: 1;
		byte LED5	: 1;
		byte LED6	: 1;
		byte LED7	: 1;
	} Bits;
}LEDLSTR;
extern volatile LEDLSTR _LEDRL @0x0000000A;
extern volatile LEDLSTR _LEDG  @0x0000000D;


typedef union {
	byte	Byte;
	struct {
		byte LED8	: 1;
		byte LED9	: 1;
		byte rsvd	: 6;
	} Bits;
}LEDHSTR;
extern volatile LEDHSTR _LEDRH @0x00000009;

#define LEDRH     	_LEDRH.Byte
#define LEDRL     	_LEDRL.Byte
#define LEDG    	_LEDG.Byte

#define LEDR_LED0	_LEDRL.Bits.LED0
#define LEDR_LED1	_LEDRL.Bits.LED1
#define LEDR_LED2	_LEDRL.Bits.LED2
#define LEDR_LED3	_LEDRL.Bits.LED3
#define LEDR_LED4	_LEDRL.Bits.LED4
#define LEDR_LED5	_LEDRL.Bits.LED5
#define LEDR_LED6	_LEDRL.Bits.LED6
#define LEDR_LED7	_LEDRL.Bits.LED7
#define LEDR_LED8	_LEDRH.Bits.LED8
#define LEDR_LED9	_LEDRH.Bits.LED9
#define LEDG_LED0	_LEDG.Bits.LED0
#define LEDG_LED1	_LEDG.Bits.LED1
#define LEDG_LED2	_LEDG.Bits.LED2
#define LEDG_LED3	_LEDG.Bits.LED3
#define LEDG_LED4	_LEDG.Bits.LED4
#define LEDG_LED5	_LEDG.Bits.LED5
#define LEDG_LED6	_LEDG.Bits.LED6
#define LEDG_LED7	_LEDG.Bits.LED7

#define LEDR_LED0_MASK             1U
#define LEDR_LED1_MASK             2U
#define LEDR_LED2_MASK             4U
#define LEDR_LED3_MASK             8U
#define LEDR_LED4_MASK             16U
#define LEDR_LED5_MASK             32U
#define LEDR_LED6_MASK             64U
#define LEDR_LED7_MASK             128U
#define LEDR_LED8_MASK             1U
#define LEDR_LED9_MASK             2U
#define LEDG_LED0_MASK             1U
#define LEDG_LED1_MASK             2U
#define LEDG_LED2_MASK             4U
#define LEDG_LED3_MASK             8U
#define LEDG_LED4_MASK             16U
#define LEDG_LED5_MASK             32U
#define LEDG_LED6_MASK             64U
#define LEDG_LED7_MASK             128U

// switches
typedef union {
	byte	Byte;
	struct {
		byte SWL0	: 1;
		byte SWL1	: 1;
		byte SWL2	: 1;
		byte SWL3	: 1;
		byte SWL4	: 1;
		byte SWL5	: 1;
		byte SWL6	: 1;
		byte SWL7	: 1;
	} Bits;
}SWLSTR;
extern volatile SWLSTR _SWL @0x00000012;

typedef union {
	byte	Byte;
	struct {
		byte SWH8	: 1;
		byte SWH9	: 1;
		byte rsvd	: 3;
		byte KEY1	: 1;
		byte KEY2	: 1;
		byte KEY3	: 1;
	} Bits;
}SWHSTR;
extern volatile SWHSTR _SWH @0x00000011;

#define SWH     _SWH.Byte
#define SWL     _SWL.Byte

#define SW_SW0	_SWL.Bits.SWL0
#define SW_SW1	_SWL.Bits.SWL1
#define SW_SW2	_SWL.Bits.SWL2
#define SW_SW3	_SWL.Bits.SWL3
#define SW_SW4	_SWL.Bits.SWL4
#define SW_SW5	_SWL.Bits.SWL5
#define SW_SW6	_SWL.Bits.SWL6
#define SW_SW7	_SWL.Bits.SWL7
#define SW_SW8	_SWH.Bits.SWH8
#define SW_SW9	_SWH.Bits.SWH9
#define SW_KEY1	_SWH.Bits.KEY1
#define SW_KEY2	_SWH.Bits.KEY2
#define SW_KEY3	_SWH.Bits.KEY3

#define SW_SW0_MASK             1U
#define SW_SW1_MASK             2U
#define SW_SW2_MASK             4U
#define SW_SW3_MASK             8U
#define SW_SW4_MASK             16U
#define SW_SW5_MASK             32U
#define SW_SW6_MASK             64U
#define SW_SW7_MASK             128U
#define SW_SW8_MASK             1U
#define SW_SW9_MASK             2U
#define SW_KEY1_MASK            32U
#define SW_KEY2_MASK            64U
#define SW_KEY3_MASK            128U

// FIR
typedef union {
	byte	ByteRd;
	byte	ByteWr;
	struct {
		byte OVR	: 1;		// Right channel Overflow
		byte OVL	: 1;		// Left channel Overflow
		byte 		: 1;
		byte 		: 1;
		byte 		: 1;
		byte Full	: 1;		// New result available
		byte FIE	: 1;		// Interrupt enable
		byte Busy	: 1;		// Executing command
	} BitsRd;
	struct {
		byte Cmd	: 4;
		byte rsvd	: 4;
	} BitsWr;
}FIRSTR;
extern volatile FIRSTR _FIRSC @0x00000041;

#define FIRCMD  	_FIRSC.ByteWr
#define FIRSTAT		_FIRSC.ByteRd

#define FIRSTAT_OVR		_FIRSC.BitsRd.OVR
#define FIRSTAT_OVL		_FIRSC.BitsRd.OVL
#define FIRSTAT_FULL	_FIRSC.BitsRd.Full
#define FIRSTAT_FIE		_FIRSC.BitsRd.FIE
#define FIRSTAT_BUSY	_FIRSC.BitsRd.Busy
#define FIR_CMD			_FIRSC.BitsWr.Cmd

#define FIRSTAT_OVR_MASK             1U
#define FIRSTAT_OVL_MASK             2U
#define FIRSTAT_FULL_MASK            32U
#define FIRSTAT_FIE_MASK             64U
#define FIRSTAT_BUSY_MASK            128U

// FIR commands
#define	mNOP			 0U		// NOP
#define	mSetTaps		 1U		// set number of taps
#define	mSetCoefAddr	 2U		// set coefficient address
#define	mSetTapAddr		 3U		// set signal tap address
#define	mWrtCoefData	 4U		// write coefficient data to both channels (MSbyte of left channel first)
#define	mWrtTapData		 5U		// write signal tap data to both channels (MSbyte of left channel first)
#define	mWrtDataBoth	 6U		// write input signal data to both channels (MSbyte of left channel first)
#define	mWrtDataRight	 7U		// write input signal data to right channel only (MSbyte first)
#define	mReadDataBoth	 8U		// read output sample from both channels (MSbyte of left channel first)
#define	mReadDataRight	 9U		// read output sample from right channel only (MSbyte first)
#define	mReadTaps		 10U	// read number of taps
#define	mReadCoefData	 12U	// read coefficient data from both channels (MSbyte of left channel first)
#define	mReadSigData	 13U	// read signal tap data from both channels (MSbyte of left channel first)
#define	mFIR_DisableInt	 14U	// disable FIR interrupts
#define	mFIR_EnableInt	 15U	// enable FIR interrupts

extern volatile byte _FIRDAT @0x00000042;

// Audio Codec
typedef union {
	byte	ByteRd;
	byte	ByteWr;
	struct {
		byte 		: 1;
		byte 		: 1;
		byte 		: 1;
		byte 		: 1;
		byte 		: 1;
		byte Full	: 1;		// New result available
		byte ACIE	: 1;		// Interrupt enable
		byte Busy	: 1;		// Executing command
	} BitsRd;
	struct {
		byte Cmd	: 3;
		byte rsvd	: 5;
	} BitsWr;
}ACSTR;
extern volatile ACSTR _ACSC @0x00000045;

#define ACCMD  		_ACSC.ByteWr
#define ACSTAT		_ACSC.ByteRd

#define ACSTAT_FULL		_ACSC.BitsRd.Full
#define ACSTAT_FIE		_ACSC.BitsRd.FIE
#define ACSTAT_BUSY		_ACSC.BitsRd.Busy
#define AC_CMD			_ACSC.BitsWr.Cmd

#define ACSTAT_FULL_MASK            32U
#define ACSTAT_FIE_MASK             64U
#define ACSTAT_BUSY_MASK            128U

// Audio Codec commands
// #define	mNOP			 0U		// NOP
#define	mCtrlWr			 1U		// Write control word to Codec
#define	mLeftWr			 2U		// Write Left channel output
#define	mRightWr		 3U		// Write Right channel output
#define	mLeftRd			 4U		// Read Left channel input
#define	mRightRd		 5U		// Read Right channel input
#define	mAC_DisableInt	 6U		// disable AC interrupts
#define	mAC_EnableInt	 7U		// enable AC interrupts

extern volatile byte _ACDAT @0x00000046;



/***********************************************/
/**   D E P R E C I A T E D   S Y M B O L S   **/
/***********************************************/
/* -----------------------------------------------------------
Exceptions in bit names of timer status and control registers
due to backward compatibility with previous releases */
#define TPM1C0SC_ELSxA    _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELSxB    _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MSxA     _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MSxB     _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CHxIE    _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CHxF     _TPM1C0SC.Bits.CH0F

#define TPM1C1SC_ELSxA    _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELSxB    _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MSxA     _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MSxB     _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CHxIE    _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CHxF     _TPM1C1SC.Bits.CH1F

#define TPM1C2SC_ELSxA    _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELSxB    _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MSxA     _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MSxB     _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CHxIE    _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CHxF     _TPM1C2SC.Bits.CH2F

#define TPM2C0SC_ELSxA    _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELSxB    _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MSxA     _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MSxB     _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CHxIE    _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CHxF     _TPM2C0SC.Bits.CH0F

#define TPM2C1SC_ELSxA    _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELSxB    _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MSxA     _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MSxB     _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CHxIE    _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CHxF     _TPM2C1SC.Bits.CH1F
#define TPM2C2SC_ELSxA    _TPM2C2SC.Bits.ELS2A
#define TPM2C2SC_ELSxB    _TPM2C2SC.Bits.ELS2B
#define TPM2C2SC_MSxA     _TPM2C2SC.Bits.MS2A
#define TPM2C2SC_MSxB     _TPM2C2SC.Bits.MS2B
#define TPM2C2SC_CHxIE    _TPM2C2SC.Bits.CH2IE
#define TPM2C2SC_CHxF     _TPM2C2SC.Bits.CH2F

#define TPM2C3SC_ELSxA    _TPM2C3SC.Bits.ELS3A
#define TPM2C3SC_ELSxB    _TPM2C3SC.Bits.ELS3B
#define TPM2C3SC_MSxA     _TPM2C3SC.Bits.MS3A
#define TPM2C3SC_MSxB     _TPM2C3SC.Bits.MS3B
#define TPM2C3SC_CHxIE    _TPM2C3SC.Bits.CH3IE
#define TPM2C3SC_CHxF     _TPM2C3SC.Bits.CH3F

#define TPM2C4SC_ELSxA    _TPM2C4SC.Bits.ELS4A
#define TPM2C4SC_ELSxB    _TPM2C4SC.Bits.ELS4B
#define TPM2C4SC_MSxA     _TPM2C4SC.Bits.MS4A
#define TPM2C4SC_MSxB     _TPM2C4SC.Bits.MS4B
#define TPM2C4SC_CHxIE    _TPM2C4SC.Bits.CH4IE
#define TPM2C4SC_CHxF     _TPM2C4SC.Bits.CH4F
/* --------------------------------------------------------------------------- */
/* The following symbols were removed, because they were invalid or irrelevant */
/* --------------------------------------------------------------------------- */
/*
 * Follows changes from the database 2.87.167 version */
#define IIC1A_ADDR_BITNUM                IIC1A_ADDR_1_BITNUM
#define IIC1A_ADDR_MASK                  IIC1A_ADDR_1_MASK
#define IIC1A_ADDR0                      This_symb_has_been_depreciated
#define IIC1A_ADDR0_MASK                 This_symb_has_been_depreciated
#endif
/*lint -restore  +esym(961,18.4) +esym(961,19.7) Enable MISRA rule (1.1,18.4,6.4,19.7) checking. */
