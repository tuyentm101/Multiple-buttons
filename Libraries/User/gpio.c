/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

///**
//  * @brief 				
//  * @param   
//  * @retval
//  */
//void gpio_init(struct gpio_handle *gpio)
//{
//  GPIO_Init(gpio->gpioPort, gpio->gpio_init);
//}
/**
  * @brief 				
  * @param   
  * @retval
  */
void gpio_configuration(gpio_handle_t *g_gpio)
{ 
  g_gpio[0].gpioPin = BOARD_LED_PIN;
  g_gpio[0].gpioPort = BOARD_LED_PORT;
  g_gpio[0].gpio_init.GPIO_Pin = BOARD_LED_PIN;
  g_gpio[0].gpio_init.GPIO_Mode = GPIO_MODE_OUTPUT;
  g_gpio[0].gpio_init.GPIO_Speed = GPIO_HIGH_SPEED;
  g_gpio[0].gpio_init.GPIO_OType = GPIO_TYPE_OUTPUT_PUSHPULL;
  GPIO_Init(g_gpio[0].gpioPort, &(g_gpio[0].gpio_init));
	           				 
  g_gpio[1].gpioPin = BOARD_BUTTON_PIN;
  g_gpio[1].gpioPort = BOARD_BUTTON_PORT; 
  g_gpio[1].gpio_init.GPIO_Pin = BOARD_BUTTON_PIN;
  g_gpio[1].gpio_init.GPIO_Mode = GPIO_MODE_INPUT;
  g_gpio[1].gpio_init.GPIO_Speed = GPIO_HIGH_SPEED; 
  g_gpio[1].gpio_init.GPIO_PuPd = GPIO_TYPE_INPUT_PULLUP;
  GPIO_Init(g_gpio[1].gpioPort, &(g_gpio[1].gpio_init));
}
/**
  * @brief 				
  * @param   
  * @retval
  */
uint8_t gpioRead(gpio_handle_t *gpio)
{
  return GPIO_ReadInputDataBit(gpio->gpioPort, gpio->gpioPin);
}
/**
  * @brief 				
  * @param   
  * @retval
  */
void gpioWrite(gpio_handle_t *gpio, BitAction val)
{
  GPIO_WriteBit(gpio->gpioPort, gpio->gpioPin, val);
}
