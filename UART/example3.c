// UART 예제 3 : UART를 이용하여 PC와 통신하기 (폴링 방식)


/*******************************************************************************
  
  * File name :  UART_3 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// UartHandler º¯¼ö¸¦ ¿ÜºÎÁ¤ÀÇ º¯¼ö·Î ¼±¾ð
extern UART_HandleTypeDef	UartHandle;		

// UART Åë½ÅÀ» À§ÇÑ Á¤ÀÇ  
#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// UART Åë½Å¿ë º¯¼ö ¼±¾ð
uint8_t TxBuffer[] = "\n\rUART Example 3 (Transmission  Success !!)\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

//------------------------------------------------------------------------------------//

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();

	// UARTÀÇ ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ 
	UART3_Config();	

	LED_OnOff(GPIO_PIN_LedAll, 500);

	// -- <1> TxBuffer¿¡ ÀúÀåµÇ¾î ÀÖ´Â ³»¿ëÀ» PC·Î º¸³½´Ù. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize, 0xFFFF);

	// -- <2> PC¿¡¼­ µ¥ÀÌÅÍ¸¦ ¹Þ¾Æ ±×´ë·Î PC·Î Àü¼Û(echo) ÇÑ´Ù. 
	while (1)  {

		// -- <3> PC·ÎºÎÅÍ ¹ÞÀº µ¥ÀÌÅÍ¸¦ RxBuffer¿¡ ÀúÀåÇÑ´Ù. 
		if(HAL_UART_Receive(&UartHandle, (uint8_t*)RxBuffer,1, 5000)== HAL_OK)
		{
			// --<4> RxBuffer¸¦ PC·Î ´Ù½Ã º¸³½´Ù. 
			HAL_UART_Transmit(&UartHandle, (uint8_t*)RxBuffer, 1, 5000);
		}
	}
	
}

// -------------------------------------------------------------------------------- //

