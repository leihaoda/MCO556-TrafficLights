/*
 * WalkRequest.h
 *
 *  Created on: Nov 14, 2016
 *      Author: whuang73
 */

#ifndef WALKREQUEST_H_
#define WALKREQUEST_H_

typedef struct
{
    void (*Init)(void);
    void (*CheckRequest)(void);
    unsigned char (*GetRequestStatus)(void);
    void (*ClearRequestStatus)(void);
}WalkReqInterface;

extern WalkReqInterface WalkRequest;


#endif /* WALKREQUEST_H_ */
