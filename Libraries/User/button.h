/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H__
#define __BUTTON_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "SysTick.h"

/* Exported defines ------------------------------------------------------------*/
//#define SYSTEMCALLBACK void (*fnCallback)(*void)
/* Exported types ------------------------------------------------------------*/
typedef void (*fnCallback)(gpio_handle_t p_gpio);

typedef enum state
{
	IDLE = 0,
	WAIT_BUTTON_UP,
	WAIT_PRESS_TIMEOUT,
	WAIT_CLICK_TIMEOUT,
	WAIT_DOUBLECLICK_TIMEOUT
} state_t;

typedef struct button
{
	uint32_t nTick;
	gpio_handle_t *p_gpio;
	uint8_t enable;
	uint8_t state;
	fnCallback 	fnCallBackIdle;
	fnCallback 	fnCallBackClick;
	fnCallback 	fnCallBackDoubleClick;
	fnCallback 	fnCallBackPress;
} button_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported variables ------------------------------------------------------- */ 
/* Exported functions ------------------------------------------------------- */ 
void ButtonAllReset(void);

void ButtonInit(button_t* pButton, 
								gpio_handle_t *gpio, 
								fnCallback onIdle,
								fnCallback onClick,
								fnCallback onDoubleClick,
								fnCallback onPress);
                
uint8_t ButtonStart(button_t *pButton);

void ButtonCancel(button_t Button);

void ButtonProcessEvent(gpio_handle_t p_gpioLed);

void Click(gpio_handle_t p_gpioLed);
void DoubleClick(gpio_handle_t p_gpioLed);
void Press(gpio_handle_t p_gpioLed);               
#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE****/
