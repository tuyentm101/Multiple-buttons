#include "clock.h"

/*
	Enable peripherals clock, need to config first!!!!!
*/
void clock_configuration(void)
{
	RCC_AHBPeriphClockCmd(RCC_GPIO_PORT_ACTIVE, ENABLE);
}
