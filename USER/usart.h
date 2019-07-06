#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
void init_usart(void);
void Usart_Send(USART_TypeDef* USARTx,unsigned char data);
void Usart_Send_string(USART_TypeDef* USARTx,unsigned char* str);
#endif
