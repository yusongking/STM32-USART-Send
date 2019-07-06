#include <stdio.h>
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
void delay(unsigned int t){
	while(t--);
}
unsigned char word[] = "Â·Î÷Æ¤¹·Ôô  \n";
int main(void){
	init_usart();
	init_led();
	
	while(1){
		LED(1);
		Usart_Send_string(USART1,word);
		delay(0XFFFFF);
		printf("¹·Êº\n");
	}
}
