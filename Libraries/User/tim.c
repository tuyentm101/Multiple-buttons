#include "tim.h"
void Timer_Configuration_PWM(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  			 TIM_OCInitStructure;
	uint32_t ARR_Val, PreScaler;
	uint32_t CCR1_Val, CCR2_Val, CCR3_Val, CCR4_Val;
	uint32_t duty_ch1, duty_ch2, duty_ch3, duty_ch4;
	uint32_t TIM_counter_clock_freq, TIM_clock_freq;
	/* TIM1 Configuration ---------------------------------------------------
   Generate 4 PWM signals with 4 different duty cycles:
   TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2)    
   - TIM1CLK = PCLK2 = SystemCoreClock = 48 MHz
	 - TIM1 counter clock frequency = TIM1CLK / Prescaler
   - ARR_Val = (TIM1 counter clock frequency/ PWM_frequency) - 1 with ARR_Val + 1 = TIM1_Period
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (ARR_Val + 1) / 100
	---------------------------------------------------------------------------*/
	/* Compute the value to be set in ARR regiter to generate signal frequency at 0.5 Hz */
	TIM_clock_freq = SystemCoreClock;
  TIM_counter_clock_freq = 4800;				
	PreScaler = (uint16_t)((TIM_clock_freq  / TIM_counter_clock_freq) - 1);
  ARR_Val = (TIM_clock_freq * 2) - 1;
	duty_ch1 = 5;
	duty_ch2 = 375;
	duty_ch3 = 25;
	duty_ch4 = 125;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  CCR1_Val = (duty_ch1 * (ARR_Val + 1)) / 10;
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
  CCR2_Val = (duty_ch2 * (ARR_Val + 1)) / 1000;
  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
  CCR3_Val = (duty_ch3 * (ARR_Val + 1)) / 100;
  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  CCR4_Val = (duty_ch4 * (ARR_Val + 1)) / 1000;
	 /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = PreScaler;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = ARR_Val;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);				//fills with default values
	/* Channel 1, 2,3 and 4 Configuration in PWM mode 1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable);
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable);
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
}
void Timer_Enable(void)
{
	TIM_Cmd(TIM1, ENABLE);
}
void Timer_Output_Enable(void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
void Channel1_Pulsing(void)
{
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
}
void Channel1_Stop_Pulsing(void)
{
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable); 
}
void Channel1_Force_To_Low(void)
{
	TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_InActive); 
}	
void Channel1_Force_To_High(void)
{
	TIM_ForcedOC1Config(TIM1, TIM_ForcedAction_Active); 
}	
void Channel2_Pulsing(void)
{
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 
}
void Channel2_Stop_Pulsing(void)
{
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable); 
}
void Channel2_Force_To_Low(void)
{
	TIM_ForcedOC2Config(TIM1, TIM_ForcedAction_InActive); 
}	
void Channel2_Force_To_High(void)
{
	TIM_ForcedOC2Config(TIM1, TIM_ForcedAction_Active); 
}	
void Channel3_Pulsing(void)
{
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
}
void Channel3_Stop_Pulsing(void)
{
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable); 
}
void Channel3_Force_To_Low(void)
{
	TIM_ForcedOC3Config(TIM1, TIM_ForcedAction_InActive); 
}	
void Channel3_Force_To_High(void)
{
	TIM_ForcedOC3Config(TIM1, TIM_ForcedAction_Active); 
}	
void Channel4_Pulsing(void)
{
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
}
void Channel4_Stop_Pulsing(void)
{
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable); 
}
void Channel4_Force_To_Low(void)
{
	TIM_ForcedOC4Config(TIM1, TIM_ForcedAction_InActive); 
}	
void Channel4_Force_To_High(void)
{
	TIM_ForcedOC4Config(TIM1, TIM_ForcedAction_Active); 
}	
