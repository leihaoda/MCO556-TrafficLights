/*
 * StateTimeController.h
 *
 *  Created on: Nov 17, 2016
 *      Author: whuang73
 */

#ifndef STATETIMECONTROLLER_H_
#define STATETIMECONTROLLER_H_

typedef struct
{
    void (*Init)(void);
    void (*UpdateStateTime)(void);
}StateTimeCTLInterface;

extern StateTimeCTLInterface StateTimeCTL;

extern unsigned char TempSensorFlag;

#endif /* STATETIMECONTROLLER_H_ */
