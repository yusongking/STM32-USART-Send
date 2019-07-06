#include <stdio.h>
#include "stm32f10x_usart.h"
//#include "stm32f10x.h"
//TX transport 发送
//RX receive   接收
//但是板子上对应的是RX-A9,TX-A10.板子有问题？？
//接收引脚对应的是发送引脚
//发送引脚对应的是接收引脚  fuck,fuck,找了一下午mmp.
void NVIC_USART(void){
	NVIC_InitTypeDef NVIC_Struct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);
}
void init_usart(void){
	USART_InitTypeDef USART_Struct;
	GPIO_InitTypeDef USART_GPIO_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_GPIO_Struct.GPIO_Pin = GPIO_Pin_9;
	USART_GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;
	USART_GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&USART_GPIO_Struct);
	
	USART_GPIO_Struct.GPIO_Pin = GPIO_Pin_10;
	USART_GPIO_Struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&USART_GPIO_Struct);
	
	USART_Struct.USART_BaudRate = 115200;
	USART_Struct.USART_WordLength = USART_WordLength_8b;
	USART_Struct.USART_StopBits = USART_StopBits_1;
	USART_Struct.USART_Parity = USART_Parity_No;
	USART_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_Struct);
	
	NVIC_USART();
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
}
void Usart_Send(USART_TypeDef* USARTx,unsigned char data){
	USART_SendData(USARTx,data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);
	//对于单个字节发送的时候使用USART_FLAG_TXE。
}
void Usart_Send_string(USART_TypeDef* USARTx,unsigned char* str){
	do{
		Usart_Send(USARTx,*str);
		str += 1;
	}while(*str != '\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
	//对于字符串发送的时候呢，则需要USART_FLAG_TC。
	//USART_FLAG_TXE发送缓冲区空标志：说明可以往数据寄存器写入数据了，但并不代码数据发送完成了。
	//USART_FLAG_TC发送完成标志：这个才是代表USART在缓冲区的数据发送完成了，即从机接收到了数据。
}
/**
	*Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!
	*要使用printf必须在potion里面的target里面必须给USE MICRO LIB打勾！
	*Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!
	*/
int fputc(int ch,FILE* f){
	USART_SendData(USART1,(unsigned char)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return ch;
}
