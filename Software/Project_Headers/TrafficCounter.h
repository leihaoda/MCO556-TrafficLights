/*
 * TrafficCounter.h
 *
 *  Created on: Nov 18, 2016
 *      Author: whuang73
 */

#ifndef TRAFFICCOUNTER_H_
#define TRAFFICCOUNTER_H_

typedef struct
{
    void (*Init)(void);
    void (*GetCount)(unsigned char dir, unsigned char *buffer);
}TrafficCounterInterface;

extern TrafficCounterInterface TrafficCounter;


#endif /* TRAFFICCOUNTER_H_ */
