/* Includes ------------------------------------------------------------------*/
#include "button.h"
#include <stdlib.h>
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_BUTTON_NUMBER		10
#define CLICK_TICK					200U  //ms
#define DOUBLE_CLICK_TICK		200U  //ms
#define PRESS_TICK					2000U  //ms

#define DEBOUNCE_TIMEOUT  10   //ms

#define LOW									0x00
#define HIGH								0x01	

//#define TIMER_TIME_MASK     0x7FFF
//#define TIMER_TYPE_LONG     0x8000	
/* Private macro -------------------------------------------------------------*/
#define CURRENT_TICK 				get_millis() 
/* Private variables ---------------------------------------------------------*/
static button_t *g_pButton[MAX_BUTTON_NUMBER];   // Private array of handling button elements
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief 				
  * @param   
  * @retval
  */
void Click(gpio_handle_t p_gpioLed)
{
	on(p_gpioLed);
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void DoubleClick(gpio_handle_t p_gpioLed)
{
	off(p_gpioLed);
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void Press(gpio_handle_t p_gpioLed)
{
	uint8_t times = 10;
	
	while (times--)
	{
		toggle(p_gpioLed);
	}
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void ButtonAllReset(void)
{
  uint8_t i;
  
  for (i = 0; i < MAX_BUTTON_NUMBER; i++)
  {
    g_pButton[i] = NULL;
  }
}
 /**
  * @brief:  initialize values and addresses    				
	* @param:  pButton: pointer to active button
	* @param:	 gpio: 	pointer to active gpio of button
	* @param:	 onIdle, onClick, onDoubleClick, onPress: pointer to button's process call back function 
	* @retval: none
  */
void ButtonInit(button_t* pButton, 
								gpio_handle_t *gpio, 
								fnCallback onIdle,
								fnCallback onClick,
								fnCallback onDoubleClick,
								fnCallback onPress)
{
	pButton->fnCallBackIdle = onIdle;
	pButton->fnCallBackClick = onClick;
	pButton->fnCallBackDoubleClick = onDoubleClick;
	pButton->fnCallBackPress = onPress;
	
	pButton->p_gpio = gpio;
	
	pButton->nTick = 0;
	pButton->state = IDLE;
	pButton->enable = 0;
}	
/**
	* @brief: enable button 				
	* @param: pButton: pointer to active button   
  * @retval: 0 if success
  * @retval: 1 fail 
  */
uint8_t ButtonStart(button_t *pButton)
{
	uint8_t i;
	
	for (i=0; i<MAX_BUTTON_NUMBER; i++)
	{
		if (g_pButton[i] == NULL)
		{
			g_pButton[i] = pButton;
			
			pButton->nTick = 0;
			pButton->state = IDLE;
			pButton->enable = 1;
			
			return 0;
		}
	}
	return 1;
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void ButtonCancel(button_t Button)
{
	uint8_t i;
	
	for (i=0; i<MAX_BUTTON_NUMBER; i++)
	{
		if (g_pButton[i] != NULL)
		{
			g_pButton[i] = NULL;
		}
	}
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void ButtonProcessEvent(gpio_handle_t p_gpioLed)
{
	uint8_t i, ButtonState;
	
	for (i=0; i<MAX_BUTTON_NUMBER; i++)
	{
		if ((g_pButton[i] != NULL) && (g_pButton[i]->enable))
		{
			switch(g_pButton[i]->state)
			{
				case IDLE: //0
					ButtonState = gpioRead(g_pButton[i]->p_gpio);
					if (ButtonState == LOW)
					{
						SysTick_Delay_ms(DEBOUNCE_TIMEOUT);
						if (ButtonState == LOW)
						{
							g_pButton[i]->state = WAIT_BUTTON_UP; // Sang trang thai cho nha nut (1)
							g_pButton[i]->nTick = CURRENT_TICK + PRESS_TICK;
						}
					}
					break;
					
				case WAIT_BUTTON_UP: //1
					ButtonState = gpioRead(g_pButton[i]->p_gpio);
          if ((ButtonState == HIGH) && (g_pButton[i]->nTick > CURRENT_TICK)) // if not pass timeout and button is released
          {
						SysTick_Delay_ms(DEBOUNCE_TIMEOUT);
						ButtonState = gpioRead(g_pButton[i]->p_gpio);
						if (ButtonState == HIGH)	
						{
							g_pButton[i]->state = WAIT_CLICK_TIMEOUT; // Sang trang thai click timeout (2)
							g_pButton[i]->nTick = CURRENT_TICK + CLICK_TICK;
							break;
						}
          }
					if (g_pButton[i]->nTick <= CURRENT_TICK) // if pass timeout
					{
						g_pButton[i]->state = WAIT_PRESS_TIMEOUT;	// Sang trang thai press timeout (4)
						if (g_pButton[i]->fnCallBackPress != NULL)
						{
							g_pButton[i]->fnCallBackPress(p_gpioLed);
						}
					}
					break;
					
				case WAIT_PRESS_TIMEOUT:  //4 remain in this state until the button is high
					ButtonState = gpioRead(g_pButton[i]->p_gpio);
					if (ButtonState == HIGH)
					{
						SysTick_Delay_ms(DEBOUNCE_TIMEOUT);
						if (ButtonState == HIGH)
						{
							g_pButton[i]->state = IDLE;
							g_pButton[i]->nTick = 0;
						}
					}
					break;
					
				case WAIT_CLICK_TIMEOUT: //2
					ButtonState = gpioRead(g_pButton[i]->p_gpio);
          if ((ButtonState == LOW) && (g_pButton[i]->nTick > CURRENT_TICK)) // if not pass timeout
					{
						SysTick_Delay_ms(DEBOUNCE_TIMEOUT);
						ButtonState = gpioRead(g_pButton[i]->p_gpio);
						if (ButtonState == LOW)
							{
								g_pButton[i]->state = WAIT_DOUBLECLICK_TIMEOUT; // Sang trang thai cho timeout double click (3)
								g_pButton[i]->nTick = CURRENT_TICK + DOUBLE_CLICK_TICK;
								break;
							}
          }
					if (g_pButton[i]->nTick <= CURRENT_TICK)	//if pass timeout
					{
						if (g_pButton[i]->fnCallBackClick != NULL)
						{
							g_pButton[i]->fnCallBackClick(p_gpioLed);
						}
						// after finish click callback function return to state 0
						g_pButton[i]->state = IDLE;
						g_pButton[i]->nTick = 0;
					}
          // detect button is still up and click timeout
          break;
					
				case WAIT_DOUBLECLICK_TIMEOUT: //3
          // detect if button is up 
					ButtonState = gpioRead(g_pButton[i]->p_gpio);
          if ((ButtonState == HIGH) && (g_pButton[i]->nTick > CURRENT_TICK))   // if not pass timeout
					{
						SysTick_Delay_ms(DEBOUNCE_TIMEOUT);
						ButtonState = gpioRead(g_pButton[i]->p_gpio);
						if (ButtonState == HIGH)  // if buttoned is released
						{
							if (g_pButton[i]->fnCallBackDoubleClick != NULL)
							{
								g_pButton[i]->fnCallBackDoubleClick(p_gpioLed);
							}
							// after finish click callback function return to state 0
							g_pButton[i]->state = IDLE;
							g_pButton[i]->nTick = 0;
							break;
						}
          }
					if (g_pButton[i]->nTick <= CURRENT_TICK) //if pass timeout
					{
						g_pButton[i]->state = WAIT_PRESS_TIMEOUT;  // chuyen sang trang thai press timeout (4)
					}
          break;
			}
		}
	}
}
/*****END OF FILE****/
