/*
    Project : MCO556 Drivers
    File    : analog.h
    Author  : G. VandeBelt
    Date    : 2012/03/19

   This file contains the function prototypes for the analog driver.

   In ADC interrupt mode, ADCgetSample returns 0 if no sample is available.
   In ADC non-interrupt mode, ADCgetSample returns TRUE.

 */
#ifndef ANALOG_H
#define ANALOG_H

void ANALOGopen(unsigned char RxIntEna);
unsigned char ADCgetSample(char chan, unsigned int *sample );
void DACputSample(char chan, int sample);
void ADCstart(char chan);

#endif	// ANALOG_H