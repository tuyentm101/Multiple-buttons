/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h" 
#include "stm32f0xx_misc.h"

/* Exported types ------------------------------------------------------------*/

extern volatile uint32_t millis;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */ 

void SysTick_Init(void);
void SysTick_Delay_ms(uint32_t nTime_ms);
void SysTick_Delay_Us(volatile uint32_t nTime_Us);
uint32_t get_millis(void);
uint32_t get_micros(void);

#ifdef __cplusplus
}
#endif

#endif


/*****END OF FILE****/
