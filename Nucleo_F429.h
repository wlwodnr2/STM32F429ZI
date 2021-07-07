
/*******************************************************************************
  
  * File name :  Nucleo_F429.h  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <3> Nucleo_F429 BoardÀÇ »ç¿ë¿¡ ÇÊ¿äÇÑ ³»¿ëÀ» Á¤ÀÇ, ¼±¾ðÇÑ Çì´õ ÆÄÀÏ

// -- <3-1> Nucleo_F429 BoardÀÇ LEDÀÇ Æ÷Æ®, ÇÉ ¹øÈ£¸¦ Á¤ÀÇ 
#define GPIONucleo					GPIOB 
#define GPIOExt									GPIOD
#define GPIO_PIN_Led1		GPIO_PIN_0
#define GPIO_PIN_Led2		GPIO_PIN_1
#define GPIO_PIN_Led3		GPIO_PIN_2
#define GPIO_PIN_Led4		GPIO_PIN_3
#define GPIO_PIN_Led5		GPIO_PIN_4
#define GPIO_PIN_Led6		GPIO_PIN_5
#define GPIO_PIN_Led7		GPIO_PIN_6
#define GPIO_PIN_Led8		GPIO_PIN_7
#define GPIO_PIN_LedAll		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

// -- <3-2> Nucleo_F429 BoardÀÇ SwitchÀÇ  Æ÷Æ®, ÇÉ ¹øÈ£¸¦ Á¤ÀÇ
#define GPIOSwNucleo							GPIOC
#define GPIOSw1				GPIOG
#define GPIOSw2				GPIOG
#define GPIOSw3				GPIOG
#define GPIOSw4				GPIOG
#define GPIO_PIN_Nucleo_Sw		GPIO_PIN_13
#define GPIO_PIN_Sw1		GPIO_PIN_0
#define GPIO_PIN_Sw2		GPIO_PIN_1
#define GPIO_PIN_Sw3		GPIO_PIN_2
#define GPIO_PIN_Sw4		GPIO_PIN_3


// -- <3-3> Nucleo_F429.c ¿¡¼­ »ç¿ëÇÏ´Â ÇÔ¼öÀÇ ¼±¾ð
void SystemClock_Config(void);
void LED_Config(void);
void Sw_Config(void);
void SwEXTI_Config(void);
void TIM2_Config(int prescaler_value, int period_value);
void TIM3_Config(int prescaler_value, int period_value);
void TIM_OC_Config(int pulse_value);
void TIM_PWM_Poll_Config(int pwm_value);
void TIM_PWM_IT_Config(int pwm_value);
void UART3_Config(void);
void ADC1_Polling_Config(void);
void ADC1_Interrupt_Config(void);
void DAC_Config(void);
void LED_OnOff(int, int); 

// -------------------------------------------------------------------------------- //



