/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "SysTick.h"
/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void toggle(gpio_handle_t gpioLed);

void on(gpio_handle_t gpioLed);

void off(gpio_handle_t gpioLed);

#ifdef __cplusplus
}
#endif

#endif 
/*****END OF FILE****/
