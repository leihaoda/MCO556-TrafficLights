/// \file       TrafficCounter.c
/// \author     William Huang
/// \brief      Traffic Counter interface for the Traffic Control system
///
/// Initializes Input capture, capturing on rising edges. Will be used to determine traffic count
/// Timer 1 Channel 0: North South traffic  (TP15)
/// Timer 1 Channel 1: East-West traffic    (TP16)
/// Max count is 99
///
/// \date       21/11/2016

#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative information */
#include "Timer.h"
#include "TrafficCounter.h"

unsigned int TrafficCountNS;
unsigned int TrafficCountEW;

static void Init(void);
static void GetCount(unsigned char dir, unsigned char *buffer);

/// \brief  Initialization for traffic counter
///
/// Assuming Timer 1 has already been initialized at 20MHz / 128, initialize channel 0 and 1 
/// for input capture on rising edge.
/// Assumes SCI2 has been initialized with 2400 baud and RX interrupt enable
static void Init(void)
{
    
    // Setting up Timer 1 Channel 2 to use input capture,
    // and Timer 1 Channel 4 to determine when to send the traffic count
    TIM1C0_Open(INPUT_CAPTURE, INPUTCATURE_RISING, 1, 0); // North - South traffic sensor
    TIM1C1_Open(INPUT_CAPTURE, INPUTCATURE_RISING, 1, 0); // East - West traffic sensor
}

/// \brief Takes current count of north south traffic and stores ASCII value in buffer
///
/// \param dir      1: Count for North-South    0: Count for East-West
/// \param *buffer  Pointer to buffer of where to store the value in ASCII
static void GetCount(unsigned char dir, unsigned char *buffer)
{
    unsigned int tmp;
    unsigned int value;
    signed char idx;
    
    if(dir)
    {
        value = TrafficCountNS;
        TrafficCountNS = 0;
    }
    else
    {
        value = TrafficCountEW;
        TrafficCountEW = 0;
    }
    
    // Keep TrafficCount to 99 max
    if(value > 99)
    {
        value = 99;
    }
    
    // Convert value into ASCII
    for(idx = 1; idx >= 0; idx --)
    {

        *buffer-- = (value % 10) + '0';
        value = value / 10;
    }
}

TrafficCounterInterface TrafficCounter =
{
        &Init,
        &GetCount
};

interrupt void NSTrafficISR(void)
{
    TPM1C0SC_CH0F = 0;
    TrafficCountNS++;
}


interrupt void EWTrafficISR(void)
{
    TPM1C1SC_CH1F = 0;
    TrafficCountEW++;
}

