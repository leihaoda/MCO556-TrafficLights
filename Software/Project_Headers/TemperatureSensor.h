/*
 * TemperatureSensor.h
 *
 *  Created on: Nov 22, 2016
 *      Author: whuang73
 */

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

typedef struct
{
    void (*Init)(void);
    unsigned char (*GetTemp)(signed int *temperature);
    void (*DisplayTemp)(signed int temperature);
}TEMPSENSORINTERFACE;

extern TEMPSENSORINTERFACE TempSensor;


#endif /* TEMPERATURESENSOR_H_ */
