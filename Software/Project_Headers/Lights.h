/// \file       Lights.h
/// \author     William Huang
/// \brief      Header file for Interface for LEDG
/// \date       03/11/2016

#ifndef LIGHTS_H_
#define LIGHTS_H_

typedef struct 
{
    void (*CtlNS)(unsigned char red, unsigned char yellow, unsigned char green, unsigned char leftTurn);
    void (*CtlEW)(unsigned char red, unsigned char yellow, unsigned char green);
}LightsInterface;

extern LightsInterface Lights;

#endif /* LIGHTS_H_ */
