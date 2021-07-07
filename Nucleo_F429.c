
/*******************************************************************************
  
  * File name :  Nucleo_F429.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <4> Nucleo_F429 º¸µåÀÇ »ç¿ë¿¡ ÇÊ¿äÇÑ ÇÔ¼ö¸¦ ±¸ÇöÇÑ ÆÄÀÏ

// -- <4-1> ÇÁ·Î±×·¥ÀÇ ½ÇÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏÀ» ÀÎÅ¬·çµå
#include "main.h"
#include "Nucleo_F429.h"

// -- <4-2> ÁÖº¯ÀåÄ¡ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼
GPIO_InitTypeDef		    						GPIO_Init_Struct; 					    // GPIOÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö 
TIM_HandleTypeDef								TimHandle;											// Å¸ÀÌ¸ÓÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö
TIM_OC_InitTypeDef								TIM_OCInit;												// Å¸ÀÌ¸Ó Channel(OC)ÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö
UART_HandleTypeDef						UartHandle;											// UARTÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö 		
ADC_HandleTypeDef							AdcHandler;											// ADCÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö
ADC_ChannelConfTypeDef   	Adc_sConfig; 									// ADC ChannelÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö
DAC_HandleTypeDef							DacHandler;										// DACÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö
DAC_ChannelConfTypeDef			Dac_sConfig;										// DAC ChannelÀÇ ÃÊ±âÈ­¿ë ±¸Á¶Ã¼ º¯¼ö

// -------------------------------------------------------------------------------- //
// -- <5> Nucleo_F429 º¸µåÀÇ  LED¿ë GPIO (PD0~7)ÀÇ ÃÊ±â¼³Á¤À» ÇÔ 

void LED_Config(void)
{
		// -- Nucleo Board LED GPIO (PB0, PB7)¼³Á¤
		// -- <5-1> GPIOBÀÇ Å¬·°À» enable	
		__HAL_RCC_GPIOB_CLK_ENABLE();

		// -- <5-2> LEDÀÇ µ¿ÀÛ Á¶°ÇÀ» ¼³Á¤
		GPIO_Init_Struct.Pin = GPIO_PIN_0 | GPIO_PIN_7;		// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP; 		// Output Push-Pull ¸ðµå
		GPIO_Init_Struct.Pull     = GPIO_PULLUP; 						// Pull Up ¸ðµå
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î 	
		
		// -- <5-3> GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ
		HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);
		
		// -- È®Àå IO Board LED GPIO (PD0 ~ PD7)¼³Á¤
		// -- <5-4> GPIODÀÇ Å¬·°À» enable	
		__HAL_RCC_GPIOD_CLK_ENABLE();

		// -- <5-5> LED1~8ÀÇ µ¿ÀÛ Á¶°ÇÀ» ¼³Á¤
		GPIO_Init_Struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
								 GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;	
																	// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP; 		// Output Push-Pull ¸ðµå
		GPIO_Init_Struct.Pull     = GPIO_PULLUP; 						// Pull Up ¸ðµå
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î 	
		
		// -- <5-6> GPIOLed¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ
		HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct); 
}


// -------------------------------------------------------------------------------- //
// -- <6> Nucleo_F429 º¸µåÀÇ  SwitchÀÇ GPIO (PG0, PG1, PG2, PG3)ÀÇ ÃÊ±â¼³Á¤À» ÇÔ 
//				* ÀÌ ÇÔ¼ö´Â SW¸¦ GPIO ÀÔ·ÂÀ¸·Î ¹Þ´Â ÇÔ¼öÀÌ´Ù.

void Sw_Config(void)
{
		// -- Nucleo Board Switch (PC13)¼³Á¤
		// -- <6-1> GPIOCÀÇ Å¬·°À» enable		
		__HAL_RCC_GPIOC_CLK_ENABLE();	

		// -- <6-2> SW1ÀÇ µ¿ÀÛ Á¶°ÇÀ» GPIO ÀÔ·ÂÀ¸·Î ¼³Á¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ¸ðµå
		GPIO_Init_Struct.Pull 		= GPIO_PULLDOWN; 						// Pull Down ¸ðµå
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î 

		// -- <6-3> GPIOC¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ	
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);    

		// -- È®Àå IO Board Switch (PG0, PG1, PG2, PG3)ÀÇ ÃÊ±â¼³Á¤
		// -- <6-4> GPIOGÀÇ Å¬·°À» enable		
		__HAL_RCC_GPIOG_CLK_ENABLE();	

		// -- <6-5>  SW1 ~ SW4¿ë µ¿ÀÛ Á¶°ÇÀ» GPIO ÀÔ·ÂÀ¸·Î ¼³Á¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;	// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ¸ðµå
		GPIO_Init_Struct.Pull 		= GPIO_PULLUP; 						// Pull Up ¸ðµå
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î 

		// -- <6-6> GPIOG¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ	
		HAL_GPIO_Init(GPIOG, &GPIO_Init_Struct);      		
}

// -------------------------------------------------------------------------------- //
// -- <7> Nucleo_F429 º¸µåÀÇ  SwitchÀÇ GPIO (PG0, PG1, PG2, PG3)ÀÇ ÃÊ±â¼³Á¤À» ÇÔ 
//				* ÀÌ ÇÔ¼ö´Â SW¸¦ ´©¸£¸é EXTI°¡ ¹ß»ýÇÏµµ·Ï ¼³Á¤ÇÑ´Ù.

void SwEXTI_Config(void)
{
		// -- Nucleo Board Switch (PC13)¼³Á¤
		// -- <7-1> GPIOCÀÇ Å¬·°À» enable		
		__HAL_RCC_GPIOC_CLK_ENABLE();	

		// -- <7-2> SW1ÀÇ µ¿ÀÛ Á¶°ÇÀ» GPIO ÀÔ·ÂÀ¸·Î ¼³Á¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING; 				// Input Floating ¸ðµå
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ºñÈ°¼ºÈ­
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î 

		// -- <7-3> GPIOC¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ	
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);

		// -- È®Àå IO Board Switch (PG0, PG1, PG2, PG3)ÀÇ ÃÊ±â¼³Á¤
		// -- <7-4> GPIOGÀÇ Å¬·°À» enable			
		__HAL_RCC_GPIOG_CLK_ENABLE();	

		// -- <7-5>  SW1 ~ SW4¿ë µ¿ÀÛ Á¶°ÇÀ» GPIO ÀÔ·ÂÀ¸·Î ¼³Á¤
		GPIO_Init_Struct.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;	// GPIO¿¡¼­ »ç¿ëÇÒ PIN ¼³Á¤
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING;				// Falling edge¿¡¼­ Interrupt ¹ß»ý
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ºñÈ°¼ºÈ­
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// µ¿ÀÛ¼Óµµ¸¦ HIGH·Î  	

		// -- <7-6>  Nucleo SW, SW1 ~ SW4¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ	
		HAL_GPIO_Init(GPIOG, &GPIO_Init_Struct);    

		// -- <7-7> SW1 ~ SW4ÀÇ EXTI¿¡ ´ëÇÑ ÀÎÅÍ·´Æ®ÀÇ ¿ì¼±¼øÀ§¸¦ ¼³Á¤ÇÏ°í, ÀÎÅÍ·´Æ®¸¦ enableÇÔ
		HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);					//  EXTI ÀÇ priority¸¦ ¼³Á¤	
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);								//  EXTI ÀÎÅÍ·´Æ®¸¦ enable
	
	  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);					//  EXTI ÀÇ priority¸¦ ¼³Á¤	
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);								//  EXTI ÀÎÅÍ·´Æ®¸¦ enable
	
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);					//  EXTI ÀÇ priority¸¦ ¼³Á¤	
		HAL_NVIC_EnableIRQ(EXTI2_IRQn);								//  EXTI ÀÎÅÍ·´Æ®¸¦ enable
		
		HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);					//  EXTI ÀÇ priority¸¦ ¼³Á¤	
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);								//  EXTI ÀÎÅÍ·´Æ®¸¦ enable
		
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);					//  EXTI ÀÇ priority¸¦ ¼³Á¤	
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);								//  EXTI ÀÎÅÍ·´Æ®¸¦ enable
}

// -------------------------------------------------------------------------------- //
// -- <8> TimerÀÇ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö
//			  * TIM2¸¦ Up couting ¸ðµå·Î µ¿ÀÛ½ÃÄÑ 1ÃÊ¿¡ 1¹ø¾¿ ¹ß»ýÇÏµµ·Ï ÁÖÆÄ¼ö¸¦ 1 Hz·Î ¼³Á¤ÇÑ´Ù.

void TIM2_Config(int prescaler_value, int period_value)
{

		// -- <8-1> TIM2ÀÇ clockÀ» enable
		__HAL_RCC_TIM2_CLK_ENABLE();
		
		// -- <8-2> TIMÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤ (ÀÎÅÍ·´Æ®°¡ 1ÃÊ¿¡ 1¹ø¾¿ ¹ß»ýÇÏµµ·Ï ÁÖÆÄ¼ö¸¦ 1 Hz·Î ¼³Á¤)
		TimHandle.Instance = TIM2;											// TIM2 »ç¿ë
		TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;	//	Up Counter ¸ðµå ¼³Á¤
		TimHandle.Init.Prescaler = prescaler_value;								// Prescaler =8999·Î ¼³Á¤
		TimHandle.Init.Period = period_value;						// ¾÷µ¥ÀÌÆ® ÀÌº¥Æ® ¹ß»ý½Ã Auto-Reload ·¹Áö½ºÅÍ = 9999·Î ¼³Á¤
		TimHandle.Init.ClockDivision = 0;								// Clock Division ¼³Á¤
		//TimHandle.Init.RepetitionCounter = 0;	// Repetition Counter °ªÀ»  ¼³Á¤ (TIM1¸¸ ÇØ´ç)

		// -- <8-3> TIM2¸¦ TimHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ÇÏ°í TIM¸¦ µ¿ÀÛÇÔ
		HAL_TIM_Base_Init(&TimHandle);	
		HAL_TIM_Base_Start_IT(&TimHandle);	
		
		// -- <8-4> Å¸ÀÌ¸Ó ÀÎÅÍ·´Æ® ¿ì¼±¼øÀ§ ¼³Á¤ ¹× ENABLE
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);		// º°µµ·Î ¼³Á¤ÇÏÁö ¾ÊÀ¸¸é µðÆúÆ®·Î ¼³Á¤µÊ
		HAL_NVIC_EnableIRQ(TIM2_IRQn);	
}

// -------------------------------------------------------------------------------- //
// -- <9> TimerÀÇ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö
//			  * TIM3¸¦ Down couting ¸ðµå·Î µ¿ÀÛ½ÃÄÑ 1ÃÊ¿¡ 1¹ø¾¿ ¹ß»ýÇÏµµ·Ï ÁÖÆÄ¼ö¸¦ 1 Hz·Î ¼³Á¤ÇÑ´Ù.

void TIM3_Config(int prescaler_value, int period_value)
{

		// -- <9-1> TIM2ÀÇ clockÀ» enable
		__HAL_RCC_TIM3_CLK_ENABLE();
		
		// -- <9-2> TIMÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤ (ÀÎÅÍ·´Æ®°¡ 1ÃÊ¿¡ 1¹ø¾¿ ¹ß»ýÇÏµµ·Ï ÁÖÆÄ¼ö¸¦ 1 Hz·Î ¼³Á¤)
		TimHandle.Instance = TIM3;								// TIM3 »ç¿ë
		TimHandle.Init.CounterMode = TIM_COUNTERMODE_DOWN;	//	Down Counter ¸ðµå ¼³Á¤
		TimHandle.Init.Prescaler = prescaler_value;					// Prescaler =6399·Î ¼³Á¤
		TimHandle.Init.Period = period_value;							// ¾÷µ¥ÀÌÆ® ÀÌº¥Æ® ¹ß»ý½Ã Auto-Reload ·¹Áö½ºÅÍ = 9999·Î ¼³Á¤
		TimHandle.Init.ClockDivision = 0;					// Clock Division ¼³Á¤
		//TimHandle.Init.RepetitionCounter = 0;		// Repetition Counter °ªÀ»  ¼³Á¤ (TIM1¸¸ ÇØ´ç)

		// -- <9-3> TIM3¸¦ TimHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ÇÏ°í TIM¸¦ µ¿ÀÛ
		HAL_TIM_Base_Init(&TimHandle);	
		HAL_TIM_Base_Start_IT(&TimHandle);	
		
		// -- <9-4> Å¸ÀÌ¸Ó ÀÎÅÍ·´Æ® ¿ì¼±¼øÀ§ ¼³Á¤ ¹× ENABLE
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);		// º°µµ·Î ¼³Á¤ÇÏÁö ¾ÊÀ¸¸é µðÆúÆ®·Î ¼³Á¤µÊ
		HAL_NVIC_EnableIRQ(TIM3_IRQn);		
}

// -------------------------------------------------------------------------------- //
// -- <10> TimerÀÇ Output Compare µ¿ÀÛ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö

void TIM_OC_Config(int pulse_value)
{

		// -- <10-1> TIMÀÇ OC µ¿ÀÛÁ¶°Ç ¼³Á¤
		TIM_OCInit.OCMode = TIM_OCMODE_TIMING;					// Output Compare µ¿ÀÛ¸ðµå ¼³Á¤
		TIM_OCInit.Pulse = pulse_value;											// Capture/Compare Register(CCR)ÀÇ ¼³Á¤°ª
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;			// OC Ãâ·ÂÀ» High·Î ¼³Á¤
		TIM_OCInit.OCFastMode = TIM_OCFAST_DISABLE; 		// TIM Output Compare Fast¸¦ Disable

		// -- <10-2> TIM OC¸¦ TimHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ÇÔ  	
		HAL_TIM_OC_Init(&TimHandle);
		// -- <10-3> TIM OCÀÇ ChannelÀ» TIM_OCInit¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ÇÔ 
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		// -- <10-4> TIM OC¸¦ µ¿ÀÛÇÔ
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_1);
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_2);
}

// -------------------------------------------------------------------------------- //
// -- <11> TimerÀÇ PWM µ¿ÀÛ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö

void TIM_PWM_IT_Config(int pwm_value)
{

		// -- <11-1> TIMÀÇ OC µ¿ÀÛÁ¶°Ç¼³Á¤
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;					
		TIM_OCInit.Pulse = pwm_value;											
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;						

		// -- <11-2> TIM PWM¸¦ TimHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 	
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <11-3> TIM PWMÀÇ ChannelÀ» TIM_OCInit¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <11-4> TIM PWM¸¦ µ¿ÀÛÇÔ
		HAL_TIM_PWM_Start_IT(&TimHandle,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
// -- <12> TimerÀÇ PWM µ¿ÀÛ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö

void TIM_PWM_Poll_Config(int pwm_value)
{

		// -- <12-1> TIMÀÇ OC µ¿ÀÛÁ¶°Ç¼³Á¤
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;					
		TIM_OCInit.Pulse = pwm_value;											
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;						

		// -- <12-2> TIM PWM¸¦ TimHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 	
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <12-3> TIM PWMÀÇ ChannelÀ» TIM_OCInit¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <12-4> TIM PWM¸¦ µ¿ÀÛÇÔ
		HAL_TIM_PWM_Start(&TimHandle,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
// -- <13> UARTÀÇ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö 
void UART3_Config(void)
{
	// -- <13-1> UARTÀÇ Å¬·°À» È°¼ºÈ­ 
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_USART3_CLK_ENABLE();

	// -- <13-2> GPIO DÆ÷Æ® 8¹ø ÇÉÀ» UART Tx·Î ¼³Á¤
	GPIO_Init_Struct.Pin	= GPIO_PIN_8;
	GPIO_Init_Struct.Mode	= GPIO_MODE_AF_PP;
	GPIO_Init_Struct.Pull	= GPIO_PULLUP;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	GPIO_Init_Struct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct);

	// -- <13-3> GPIO DÆ÷Æ® 3¹ø ÇÉÀ» UART Rx·Î ¼³Á¤
	GPIO_Init_Struct.Pin	= GPIO_PIN_9;
	GPIO_Init_Struct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_Init_Struct);	

	// -- <13-4> UARTÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤ 
	UartHandle.Instance	= USART3;  
	UartHandle.Init.BaudRate	= 9600;
	UartHandle.Init.WordLength	= UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits	= UART_STOPBITS_1;
	UartHandle.Init.Parity	= UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UartHandle.Init.Mode	= UART_MODE_TX_RX;
	
	// -- <13-5> UART ±¸¼ºÁ¤º¸¸¦ UartHandle¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 
	HAL_UART_Init(&UartHandle);
	
	// -- <13-6> UART ÀÎÅÍ·´Æ® ¿ì¼±¼øÀ§ ¼³Á¤ ¹× È°¼ºÈ­
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);	
	HAL_NVIC_EnableIRQ(USART3_IRQn); 
}

// -------------------------------------------------------------------------------- //
// -- <14> ADCÀÇ Polling¿ë ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö 
void ADC1_Polling_Config(void)
{	  
    // -- <14-1> ADCÀÇ clockÀ» È°¼ºÈ­ 
    __HAL_RCC_GPIOC_CLK_ENABLE();	
    __HAL_RCC_ADC1_CLK_ENABLE();
	
    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_0;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;	
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);	

    // -- <14-2> ADCÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;
	
    // -- <14-3> ADC¸¦ AdcHandler¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 	
    HAL_ADC_Init(&AdcHandler);

    // -- <14-4> ADC Channelµ¿ÀÛÁ¶°Ç ¼³Á¤	
    Adc_sConfig.Channel	= ADC_CHANNEL_10;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_3CYCLES;

		// -- <14-5> ¼³Á¤µÈ sConfig¿Í AdcHandler¸¦ ¿¬°üÁö¾î ÃÊ±âÈ­ ÇÔ
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <14-6> ADC¸¦ µ¿ÀÛ½ÃÅ´
		HAL_ADC_Start(&AdcHandler);
						
		// -- <14-7> º¯È¯ÀÌ ¿Ï·áµÉ ¶§±îÁö ´ë±â
		HAL_ADC_PollForConversion(&AdcHandler, 10);	

}

// -------------------------------------------------------------------------------- //
// -- <15> ADCÀÇ Interrupt¿ë ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö 
void ADC1_Interrupt_Config(void)
{	  
    // -- <15-1> ADCÀÇ clockÀ» È°¼ºÈ­ 
    __HAL_RCC_GPIOC_CLK_ENABLE();	
    __HAL_RCC_ADC1_CLK_ENABLE();
	
    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_0;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;	
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);	

    // -- <15-2> ADCÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;
	
    // -- <15-3> ADC¸¦ AdcHandler¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 	
    HAL_ADC_Init(&AdcHandler);

    // -- <15-4> ADC Channelµ¿ÀÛÁ¶°Ç ¼³Á¤	
    Adc_sConfig.Channel	= ADC_CHANNEL_10;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_3CYCLES;

		// -- <15-5> ¼³Á¤µÈ sConfig¿Í AdcHandler¸¦ ¿¬°üÁö¾î ÃÊ±âÈ­ ÇÔ
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <15-6> ADC¸¦ µ¿ÀÛ½ÃÅ´
		HAL_ADC_Start_IT(&AdcHandler);
	
    // -- <15-7> ADC ÀÎÅÍ·´Æ® ¿ì¼±¼øÀ§ ¼³Á¤ ¹× È°¼ºÈ­ 
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0); 
    HAL_NVIC_EnableIRQ(ADC_IRQn);

}

// -------------------------------------------------------------------------------- //
// -- <16> DACÀÇ ÃÊ±â¼³Á¤À» À§ÇÑ ÇÔ¼ö 
void DAC_Config(void)
{
    // -- <16-1> DACÀÇ clock ¹× LED ÇÉ clockÀ» È°¼ºÈ­ 
    __HAL_RCC_DAC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
    // -- <16-2> Ãß°¡ LED µ¿ÀÛ Á¶°ÇÀ» ¼³Á¤
    GPIO_Init_Struct.Pin 	= GPIO_PIN_4;
    GPIO_Init_Struct.Mode 	= GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pull 	= GPIO_NOPULL;

    // -- <16-3> GPIOA¸¦ GPIO_Init_Struct¿¡ ¼³Á¤µÈ Á¶°ÇÀ¸·Î ÃÊ±âÈ­ÇÔ
    HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);
	
    // -- <16-4> DACÀÇ µ¿ÀÛ Á¶°Ç ¼³Á¤ 
    DacHandler.Instance 		= DAC;
    Dac_sConfig.DAC_Trigger 		= DAC_TRIGGER_NONE;
    Dac_sConfig.DAC_OutputBuffer 	= DAC_OUTPUTBUFFER_DISABLE;

    // -- <16-5> DacHandler¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ 	
    HAL_DAC_Init(&DacHandler);

    // -- <16-6> DACÀÇ Channel 1À» sConfig¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ ÇÔ
    HAL_DAC_ConfigChannel(&DacHandler, &Dac_sConfig, DAC_CHANNEL_1);

    // -- <16-7> DAC Channel 1¹ø¿¡ ±¸Ã¼ÀûÀÎ µ¥ÀÌÅÍ ·¹Áö½ºÅÍ °ªÀ» ¼³Á¤
    HAL_DAC_SetValue(&DacHandler, DAC_CHANNEL_1, DAC_ALIGN_8B_R, 0xff);

    // -- <16-8> DAC¸¦ È°¼ºÈ­ÇÏ°í º¯È¯À» ½ÃÀÛ
    HAL_DAC_Start(&DacHandler, DAC_CHANNEL_1);

}

// -------------------------------------------------------------------------------- //
// -- <17> ½Ç½Àº¸µåÀÇ  LED¸¦ ON½ÃÅ°°í ÀÏÁ¤ ½Ã°£ÈÄ¿¡ ´Ù½Ã OFF ½ÃÅ°´Â ÇÔ¼ö

void LED_OnOff(int led, int interval) 
{
		// -- <17-1> GPIOLed Æ÷Æ®¿¡ ÀÖ´Â led¸¦ ON ÇÔ
		HAL_GPIO_WritePin(GPIONucleo, led, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOExt, led, GPIO_PIN_SET );		
		// -- <17-2> interval (msec) ½Ã°£¸¸Å­ ½Ã°£ Áö¿¬À» ÇÔ
		HAL_Delay(interval);
		// -- <17-3> GPIOLed Æ÷Æ®¿¡ ÀÖ´Â led¸¦ OFF ÇÔ
		HAL_GPIO_WritePin(GPIONucleo, led, GPIO_PIN_RESET );	
		HAL_GPIO_WritePin(GPIOExt, led, GPIO_PIN_RESET );	
}


// -------------------------------------------------------------------------------- //
//   --  <18>  System Clock À» ¼³Á¤ÇØÁÖ´Â ÇÔ¼ö
/*				- Å¬·°Àº ´ÙÀ½°ú °°ÀÌ ¼³Á¤µÈ´Ù.

  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */
// -------------------------------------------------------------------------------- //

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
  }
	
}

// -------------------------------------------------------------------------------- //
//   --  <19>  Clock ¼³Á¤½Ã ¿¡·¯°¡ ¹ß»ýÇÏ¸é Ã³¸®ÇØÁÖ´Â ÇÔ¼ö

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
	while (1)   {
	}	
}
#endif

// -------------------------------------------------------------------------------- //

