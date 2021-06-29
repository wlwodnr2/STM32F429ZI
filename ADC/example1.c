// ADC 예제 1 : ADC 출력 값에 따른 LED의 On/Off 주기 변경 (폴링 방식)


/*******************************************************************************
  
  * File name :  ADC_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// -- <1> AdcHandler, sConfig º¯¼ö¸¦ ¿ÜºÎÁ¤ÀÇ º¯¼ö·Î ¼±¾ð
extern ADC_HandleTypeDef							AdcHandler;	
extern ADC_ChannelConfTypeDef   	Adc_sConfig; 

int adc_value;
int delay_time = 0;

// -------------------------------------------------------------------------------- //

int main(void)
{
    HAL_Init(); 
    SystemClock_Config();
    LED_Config();

    // -- <2> ADCÀÇ ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ 
    ADC1_Polling_Config();   

    // -- <3> Æú¸µÀ¸·Î ADC°ª ÀÔ·Â¹Þ±â 
    while (1) 
    {
					// -- <4> ¼³Á¤µÈ sConfig¿Í AdcHandler¸¦ ¿¬°üÁö¾î ÃÊ±âÈ­ ÇÔ
					HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

					// -- <5> ADC¸¦ µ¿ÀÛ½ÃÅ´
					HAL_ADC_Start(&AdcHandler);
					
					// -- <6> º¯È¯ÀÌ ¿Ï·áµÉ ¶§±îÁö ´ë±â
					HAL_ADC_PollForConversion(&AdcHandler, 10);
					
					// -- <7> ADC º¯È¯ °á°ú °ªÀ» ÀúÀå 
					adc_value = HAL_ADC_GetValue(&AdcHandler)* 6000;
					
					// -- <8> º¯È¯ °á°ú °ªÀ» Áö¿¬ÇÔ¼ö·Î ±¸ÇöÇÏ¿© LED On/Off Á¦¾î 
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_SET);
					for(delay_time=0; delay_time<adc_value; delay_time++);
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET);

					// -- <9> for¹®À» ÀÌ¿ëÇÏ¿© delay½Ã°£À» 0~1000000±îÁö ±¸Çö  			
					for(delay_time=0; delay_time<1000000; delay_time++);
    }
}

// -------------------------------------------------------------------------------- //
