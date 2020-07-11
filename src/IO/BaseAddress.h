/*
 * BaseAddress.h
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */

#ifndef INC_BASEADDRESS_H_
#define INC_BASEADDRESS_H_

//GPIO
#define GPIO_A 0x40020000
#define GPIO_B 0x40020400
//..
#define GPIO_G 0x40021800

#define RCC_BASEADDRESS 0x40023800
#define NVIC_BASEADDRESS 0xE000E100
#define SYSCFG_BASEADDRESS 0x40013800
#define EXTI_BASEADDRESS 0x40013C00

//USART
#define USART1_BASEADDRESS 0x40011000
#define USART2_BASEADDRESS 0x40004400
#define USART3_BASEADDRESS 0x40004800
#define UART4_BASEADDRESS 0x40004C00
#define UART5_BASEADDRESS 0x40005000
#define USART6_BASEADDRESS 0x40011400
#define UART7_BASEADDRESS 0x40007800
#define UART8_BASEADDRESS 0x40007C00

#endif /* INC_BASEADDRESS_H_ */
