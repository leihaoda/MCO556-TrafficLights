/// \file       Lights.c
/// \author     William Huang
/// \brief      Interface for LEDG
/// \date       03/11/2016

#include "lights.h"
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

/// \brief  Mapping from the first 8 bits of LEDG to Traffic Lights
static enum LEDtoLightMap
{
    NS_RED,     /* bit 0 */
    NS_YELLOW,
    NS_GREEN,
    NS_LEFT,
    EW_GREEN = 5,   /* bit 5 */
    EW_YELLOW,
    EW_RED          /* bit 7 */
};

/// \brief  Sets or clears North South Lights depending on received parameters.
/// 
/// Set = 1, Clear = 0
///
/// \param  red     : red light
/// \param  yellow  : yellow light
/// \param  green   : green light
/// \param  leftTurn: left turn signal light
static void CtlNS(unsigned char red, unsigned char yellow, unsigned char green, unsigned char leftTurn)
{
    LEDG &= ~( (1U << NS_RED) | (1U << NS_YELLOW) | (1U << NS_GREEN) | (1U << NS_LEFT) );
    LEDG |= (red << NS_RED) | (yellow << NS_YELLOW) | (green << NS_GREEN) | (leftTurn << NS_LEFT);
}

/// \brief  Sets or clears East West Lights depending on received parameters.
/// 
/// Set = 1, Clear = 0
///
/// \param  red     : red light
/// \param  yellow  : yellow light
/// \param  green   : green light
static void CtlEW(unsigned char red, unsigned char yellow, unsigned char green)
{
    LEDG &= ~ ( (1U << EW_RED) | (1U << EW_YELLOW) | (1U << EW_GREEN) );
    LEDG |= (red << EW_RED) | (yellow << EW_YELLOW) | (green << EW_GREEN);
}

/// \brief Interface for Lights
LightsInterface Lights = 
{
        &CtlNS,
        &CtlEW
};

