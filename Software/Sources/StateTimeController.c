/// \file       StateTimeControl.c
/// \author     William Huang
/// \brief      Interface to control state time
/// \date       17/11/2016

#include <stdlib.h>
#include <hidef.h>                  /* for EnableInterrupts macro */
#include "derivative.h"             /* include peripheral declarations */
#include "StateTimeController.h"
#include "TrafficControl.h"
#include "serial.h"                 /* For SCI communication */
#include "TemperatureSensor.h"
#include "main.h"

#define NACK        21U
#define ACK         6U

#define MSG_SIZE    6U                          /// \brief Number of characters that will be sent from uC or received from PC
#define NS_MINTIME  10U                         /// \brief Min. allowable time for North South green lights
#define NS_MAXTIME  20U                         /// \brief Max. allowable time for North South green lights
#define EW_MINTIME  10U                         /// \brief Min. allowable time for East West green lights
#define EW_MAXTIME  20U                         /// \brief Max. allowable time for East-West green lights
static volatile unsigned char Buffer[MSG_SIZE]; /// \brief Buffer to hold characters to be sent to or received from PC
static volatile unsigned char *pBuffer;         /// \brief Pointer to buffer 
static volatile unsigned char RxFlag;           /// \brief Flag to indicate message a has been received from PC
unsigned int timeNS, timeEW;                    /// \brief Variable to hold valid time for NS and EW green time

static void Init(void);
static void UpdateStateTime(void);
static unsigned char ConvertTime(unsigned char firstChar, unsigned char secondChar, unsigned char minTime, unsigned char maxTime, unsigned int *RxTime);
static unsigned char ReadFromTerminal(void);


/// \brief  Initializes necessary applications for StateTimeController interface to work
///
/// Requires SCI for PC communication, ADC for temperature sensing.
/// Assumes SCI has already been initialize in main.
static void Init(void)
{
    // Require temp. sensor to be initialized
    TempSensor.Init();
}

/// \brief Updates State Time for various conditions....
///
/// Need better description
/// For PC, if valid message, update the time. If invalid, return NACK
static void UpdateStateTime(void)
{

    unsigned char returnVal;
    unsigned char i;
    volatile signed int temperature;
    
    // Following for updating time when message received from PC
    if(RxFlag)
    {
        RxFlag = 0;
        
        if(ReadFromTerminal() == 0)
        {
            // Invalid message, return a NACK
            SCI2putch(NACK);
        }
        else
        {
            // Valid message, return ACK and update time
            SCI2putch(ACK);
            TrafficCTL.ChangeTimeGREEN(timeNS, timeEW);
        }
        
        // Clear buffer
        for(i = 0; i < MSG_SIZE; i++)
        {
            Buffer[i] = 0;
        }
    }
    
    
    // For Temperature Sensor
    if(TempSensorFlag)
    {

        returnVal = TempSensor.GetTemp(&temperature);
        
        if(returnVal) 
        { 
            TempSensorFlag = 0; 
            TempSensor.DisplayTemp(temperature);
        }
        
        if(temperature <= 0)
        {
            // Change Flash and Yellow Time to 5 seconds
            TrafficCTL.ChangeTimeFLASH(5, 5);
            TrafficCTL.ChangeTimeYELLOW(5, 5);
        }
        else
        {
            // Change Flash and Yellow Time to 3 seconds
            TrafficCTL.ChangeTimeFLASH(3, 3);
            TrafficCTL.ChangeTimeYELLOW(3, 3);
        }
        
        
    }
}

/// \brief Read message sent from PC Terminal.
/// 
/// Read message sent from PC Terminal. A zero (0) is returned if any part of the message is invalid.
/// A one (1) is returned otherwise.
/// Steps to proceed with message:
/// 1 - Check if valid message received
///   a. STX is first character, ETX is last character
///   b. Second and Third Character is within N/S time range
///   c. Fourth and Fifth Character is within E/W time range
///
/// \return 0 - Invalid message
/// \return 1 - Valid message
static unsigned char ReadFromTerminal(void)
{
    
    unsigned int RxTime;

    // Check for valid STX/ETX
    
    if( (Buffer[0] != 2) || (Buffer[MSG_SIZE - 1] != 3) )
    {
        return 0;
    }
    
    
    // Check for valid NS Time
    if(!ConvertTime(1, 2, NS_MINTIME, NS_MAXTIME, &RxTime))
    {
        return 0;
    }
    else
    {
        timeNS = RxTime;
    }
    
    // Check for valid EW Time
    if(!ConvertTime(3, 4, EW_MINTIME, EW_MAXTIME, &RxTime))
    {
        return 0;
    }
    else
    {
        timeEW = RxTime;
    }

    // Everything is valid up to this point
    return 1;
}

/// \brief Converts the received time from ASCII to integer
///
/// If value is invalid, discard value and return a 0. Otherwise return a 1
/// \return 0 - Invalid time received
/// \return 1 - Valid time received
static unsigned char ConvertTime(unsigned char firstChar, unsigned char secondChar, unsigned char minTime, unsigned char maxTime, unsigned int *RxTime)
{

    unsigned int value;
    unsigned char temp[3];
    
    temp[0] = Buffer[firstChar];
    temp[1] = Buffer[secondChar];
    temp[2] = 0;
    
    value = atoi(temp);
    if( value < minTime  || value > maxTime)    // Invalid range, return 0
    {
        return 0;
    }
    else
    {
        *RxTime = value;
    }
    
    return 1;   // Valid range, return 1
}

/// \brief  Terminal RX interrupt service routine
///
/// For SCI communication with PC. Interrupts when data is received from the PC
interrupt void SCI2RxISR(void)
{
    static unsigned char bufferLoc = 0;
    unsigned char ch;
    ch = SCI2S1;    // Read status register to begin clear flag
    ch = SCI2D;     // Read data and clear flag
    
    if(ch == 2 || bufferLoc == 0) 
    {
        pBuffer = Buffer;
        bufferLoc = 0;
    }
    
    *pBuffer++ = ch;
    bufferLoc++;
    
    if (ch == 3 || bufferLoc == MSG_SIZE)    // Set RxFlag when ETX or when bufferLoc reaches max size of Buffer
    {
        RxFlag = 1;
        bufferLoc = 0;
    }
    
    // Wrap pointer to beginning of buffer if pointer reaches end of buffer
    if(pBuffer >= &Buffer[MSG_SIZE])
    {
        pBuffer = Buffer;
        bufferLoc = 0;
    }
    
    
}

StateTimeCTLInterface StateTimeCTL =
{
        &Init,
        &UpdateStateTime
};
