/*
 * BaseAddress.h
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */

#ifndef INC_BASEADDRESS_H_
#define INC_BASEADDRESS_H_
//System control block
#define SCB_BASEADDRESS 0xE000ED00
//GPIO
#define GPIO_A 0x40020000
#define GPIO_B 0x40020400
#define GPIO_C 0x40020800
#define GPIO_D 0x40020C00
#define GPIO_E 0x40021000
#define GPIO_F 0x40021400
#define GPIO_G 0x40021800
#define GPIO_H 0x40021C00
#define GPIO_I 0x40022000
#define GPIO_J 0x40022400
#define GPIO_K 0x40022800

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
//ADC
#define ADC1_BASEADDRESS 0x40012000
#define ADC2_BASEADDRESS 0x40012100
#define ADC3_BASEADDRESS 0x40012200
#define ADC_COMMON_BASEADDRESS 0x40012300

#endif /* INC_BASEADDRESS_H_ */
