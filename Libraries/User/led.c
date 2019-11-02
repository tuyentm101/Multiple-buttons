/* Includes ------------------------------------------------------------------*/
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  
  * @param  
  * @retval 
  */
void on(gpio_handle_t gpioLed)
{
	GPIO_SetBits(gpioLed.gpioPort, gpioLed.gpioPin);
}
/**
  * @brief  
  * @param  
  * @retval 
  */
void off(gpio_handle_t gpioLed)
{
	GPIO_ResetBits(gpioLed.gpioPort, gpioLed.gpioPin);
}
/**
  * @brief  
  * @param  
  * @retval 
  */
void toggle(gpio_handle_t gpioLed)
{
  static BitAction val = Bit_SET;
  
  GPIO_WriteBit(gpioLed.gpioPort, gpioLed.gpioPin, val ? Bit_SET : Bit_RESET);
  if (val)
	{
		val = Bit_RESET;
	}
	else
	{
		val = Bit_SET;
	}
  SysTick_Delay_ms(500);
}
/*****END OF FILE****/
