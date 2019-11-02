/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define NUMBER_OF_ACTIVE_GPIO     0x02
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{ 
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
      
  /* Add your application code here
     */
  gpio_handle_t g_gpio[NUMBER_OF_ACTIVE_GPIO];
  button_t btn1;
  
	clock_configuration();
  SysTick_Init();
  gpio_configuration(g_gpio);
  
  ButtonAllReset();
  ButtonInit(&btn1, &g_gpio[1], NULL, Click, DoubleClick, Press);
  ButtonStart(&btn1);
  
  /* Infinite loop */
  while (1)
  {
    ButtonProcessEvent(g_gpio[0]);
//		toggle(g_gpio[0]);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*******END OF FILE****/
