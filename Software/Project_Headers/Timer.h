/*
 * Timer.h
 *
 *  Created on: Nov 1, 2016
 *      Author: whuang73
 */

#ifndef TIMER_H_
#define TIMER_H_

#define INPUTCATURE_RISING		1
#define INPUTCAPTURE_FALLING	2
#define INPUTCAPTURE_BOTHEDGE	3
#define OUTPUTCOMPARE_SOFTWARE	0		
#define OUTPUTCOMPARE_TOGGLE	1
#define OUTPUTCOMPARE_CLEAR		2
#define OUTPUTCOMPARE_SET		3

typedef enum 
{
    INPUT_CAPTURE = 0x00,
    OUTPUT_COMPARE = 0x01,
    EDGE_PWM = 0x02
}TIMxCHy_MS;

typedef enum
{
	DISABLE,
	BUS_CLK,
	X_CLK,
	EXT_CLK
}TIM_CLK_SRC;

void TIM1_Open(TIM_CLK_SRC clockSource, unsigned char prescaler, unsigned char interruptEn);
void TIM1C0_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal);
void TIM1C1_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal);
void TIM1C2_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal);

void TIM2_Open(TIM_CLK_SRC clockSource, unsigned char prescaler, unsigned char interruptEn);
void TIM2C0_Open(TIMxCHy_MS modeSelect, unsigned char edgeLevelSelect, unsigned char interruptEn, unsigned int chVal);


#endif /* TIMER_H_ */
