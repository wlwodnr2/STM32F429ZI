
/*******************************************************************************
  
  * File name :  EXTI_1 / stm32f4xx_it.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// --  <1> ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õ ÆÄÀÏ 
#include "main.h"
#include "stm32f4xx_it.h"					// ÀÎÅÍ·´Æ® »ç¿ë¿¡ ÇÊ¿äÇÑ Çì´õ ÆÄÀÏ

// -------------------------------------------------------------------------------- //
// --  <2> SysTick ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void SysTick_Handler(void)
{	
		// -- <2-1> HAL_IncTick() ÇÔ¼ö¸¦ È£Ãâ 
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //
// -- <3>  EXTI0 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI0_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_0¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_0) ¸¦ È£Ãâ
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI1 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI1_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_1¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_1) ¸¦ È£Ãâ	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI2 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI2_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_2¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_2) ¸¦ È£Ãâ		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //
// -- <6>  EXTI3 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI3_IRQHandler(void)
{
		// -- <6-1> GPIO_PIN_3¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_3) ¸¦ È£Ãâ		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //
// -- <7>  EXTI13 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI15_10_IRQHandler(void)
{	
		// -- <7-1> GPIO_PIN_13¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_13) ¸¦ È£Ãâ		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //
