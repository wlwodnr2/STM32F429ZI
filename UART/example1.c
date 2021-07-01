// UART 예제 1 : UART를 이용하여 PC에 메세지 보내기 


/*******************************************************************************
  
  * File name :  UART_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// -- <1> UartHandler º¯¼ö¸¦ ¿ÜºÎÁ¤ÀÇ º¯¼ö·Î ¼±¾ð
extern UART_HandleTypeDef	UartHandle;			

// -- <2> UART Åë½ÅÀ» À§ÇÑ Á¤ÀÇ 
#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// -- <3> UART Åë½Å¿ë º¯¼ö ¼±¾ð 
uint8_t TxBuffer[] = "\n\rUART Example 1 (Transmission  Success !!)\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

// -------------------------------------------------------------------------------- //

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();

	// -- <4> TimerÀÇ ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ 
	UART3_Config();	
	
	LED_OnOff(GPIO_PIN_LedAll, 500);

	// -- <5> TxBuffer¿¡ ÀúÀåµÇ¾î ÀÖ´Â ³»¿ëÀ» PC·Î º¸³½´Ù. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF); 

	// -- <6> ¹«ÇÑ ·çÇÁ 
	while (1) { }
}

// -------------------------------------------------------------------------------- //

