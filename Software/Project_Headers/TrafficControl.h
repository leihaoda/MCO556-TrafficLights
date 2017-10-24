/*
 * TrafficLights.h
 *
 *  Created on: Nov 3, 2016
 *      Author: whuang73
 */

#ifndef TRAFFICLIGHTS_H_
#define TRAFFICLIGHTS_H_

typedef struct
{
    void (*Init)(void);
    void (*StateMachine)(void);
    void (*ChangeTimeGREEN)(unsigned int timeNS, unsigned int timeEW);
    void (*ChangeTimeFLASH)(unsigned int timeNS, unsigned int timeEW);
    void (*ChangeTimeYELLOW)(unsigned int timeNS, unsigned int timeEW);
}TrafficCTLInterface;

extern TrafficCTLInterface TrafficCTL;
extern volatile unsigned int timeCount;
extern volatile unsigned char lcdFlashFlag;
extern volatile unsigned char lcdFlashState;


#endif /* TRAFFICLIGHTS_H_ */
