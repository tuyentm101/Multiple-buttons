#ifndef _CLOCK_H_
#define _CLOCK_H_
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
/*-----------------------------------------------------------------*/
#define RCC_GPIO_PORT_ACTIVE				RCC_AHBPeriph_GPIOA	| RCC_AHBPeriph_GPIOC
/*-----------------------------------------------------------------*/
void clock_configuration(void);
#endif
