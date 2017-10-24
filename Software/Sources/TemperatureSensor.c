/// \file       TemperatureSensor.c
/// \author     William Huang
/// \brief      Interface to sense temperature
/// \date       17/11/2016

#include <hidef.h>      /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdlib.h>
#include <string.h>
#include "TemperatureSensor.h"
#include "analog.h"
#include "lcd.h"

static unsigned int sample;

static void Init(void);
static unsigned char GetTemp(signed int *temperature);
static void DisplayTemp(signed int temperature);

/// \brief Initializes necessary modules for temperature sensor
///
/// Requires the analog.c driver and lcd.c driver.
/// Assumes lcd has been initialized elsewhere
static void Init(void)
{
    ANALOGopen(1);
}

/// \brief Gets ADC reading of temperature sensor and converts it to a temperature value
///
/// Reads ADC channel 1 (temperature sensor) and converts the sampled value to a temperature
/// value using the transfer function:
///         Temperature = -30 + ((sample * 75)+2047)  / 4095
///
/// \return temperature - signed integer value of the temperature value
static unsigned char GetTemp(signed int *temperature)
{

    if(ADCgetSample(1, &sample))
    {
        *temperature = (int)((((sample * 75UL)+2047U)/4095) - 30); // Transfer function of sample*75/4095 - 30. Rounding handled by 2047/4095
        return 1;
    }
    
    return 0;
}

/// \brief Displays the temperature on line 1 of the LCD screen
static void DisplayTemp(signed int temperature)
{
    unsigned char i;
    static unsigned char tempUnit[] = {0xDF, 'C', 0}; // 0xDF = degree symbol. Null terminated
    static unsigned char tempValue[6];  // Format: |sign||d||d||degree||C||NULL|
    static unsigned char length;
    // Convert temperature to ASCII
    _itoa(temperature, tempValue, 10);
    strcat(tempValue, tempUnit);
    // Determine how many spaces will ASCII values take up
    length = strlen(tempValue);
    
    // Display Temperature on line 1, upper right corner
    LCDline(1);                         //  Move to line 1
    LCDinstruct(0x80 + 10);             //  Set cursor to position 10 on line 1
    LCDputs("     ");                   //  Clear previous temperature value 
    LCDinstruct(0x80 + (16-length));    // Set cursor at approrpiate position on line 1 to display temp
    LCDputs(tempValue);                 //  Display value
    
}


TEMPSENSORINTERFACE TempSensor =
{
        &Init,
        &GetTemp,
        &DisplayTemp
};
