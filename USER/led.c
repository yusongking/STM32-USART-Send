#include "stm32f10x_gpio.h"
void init_led(void){
	GPIO_InitTypeDef LED_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	LED_Struct.GPIO_Pin = GPIO_Pin_1;
	LED_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&LED_Struct);
}
