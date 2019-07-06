#ifndef _LED_H_
#define _LED_H_
#define LED(i)\
					if(i){GPIO_ResetBits(GPIOB,GPIO_Pin_1);}\
					else{GPIO_SetBits(GPIOB,GPIO_Pin_1);}
void init_led(void);
#endif
