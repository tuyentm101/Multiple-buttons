#ifndef _TIM_H_
#define _TIM_H_
/*************************************/
#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
/*************************************/
void Timer_Configuration_PWM(void);
void Timer_Enable(void);
void Timer_Output_Enable(void);
void Channel1_Pulsing(void);
void Channel1_Stop_Pulsing(void);
void Channel1_Force_To_Low(void);
void Channel1_Force_To_High(void);
void Channel2_Pulsing(void);
void Channel2_Stop_Pulsing(void);
void Channel2_Force_To_Low(void);
void Channel2_Force_To_High(void);
void Channel3_Pulsing(void);
void Channel3_Stop_Pulsing(void);
void Channel3_Force_To_Low(void);
void Channel3_Force_To_High(void);
void Channel4_Pulsing(void);
void Channel4_Stop_Pulsing(void);
void Channel4_Force_To_Low(void);
void Channel4_Force_To_High(void);
#endif
