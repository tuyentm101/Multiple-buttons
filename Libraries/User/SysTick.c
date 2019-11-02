/** 
	* @brief Setup SysTick Timer for 1 Usec interrupts
	* 			 Reload Value is the parameter to be passed for SysTick_Config() function
	*	       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)  
	*        Initialise value of timer interval and start System Tick Timer 
	*        Interruption occurs between two microseconds
	*        Note: Formula using clock frequency is AHB, not AHB / 8
  */
/* Includes ------------------------------------------------------------------*/
#include "SysTick.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t micros, millis;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
	* @brief: SystemCoreClock = 48 Mhz 
  * @param  
  * @retval 
  */
void SysTick_Init(void)
{
	// SystemCoreClock / 1000 = 48000 is numer of pulses at frequency of 48 MHz to create interval of 1 ms
	if (SysTick_Config(48000))
	{
		while (1);
	}	
	
	NVIC_SetPriority(SysTick_IRQn, 0); // set highest priority interupt to SysTick
	
	millis = 0;
}
/**
  * @brief  
  * @param  
  * @retval 
  */
void SysTick_Delay_Us(uint32_t nTime_Us)
{
	uint32_t now = micros;
	
	while((nTime_Us-(micros-now)) > 0);
}
/**
  * @brief  
  * @param  
  * @retval 
  */
void SysTick_Delay_ms(uint32_t nTime_ms)
{
	uint32_t now = millis;
	
	while((nTime_ms-(millis-now)) > 0);
}
/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t get_millis(void)
{
		return millis;
}
/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t get_micros(void)
{
//	micros =  millis*1000+(SystemCoreClock/1000-SysTick->VAL)/48;
	micros =  millis*1000+1000-SysTick->VAL/48;
	
	return micros;
}
/*****END OF FILE****/
