/*
 * BaseAddress.h
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */

#ifndef INC_BASEADDRESS_H_
#define INC_BASEADDRESS_H_
#include <stdint.h>
uintptr_t getAdc1BaseAddress();
uintptr_t getAdc2BaseAddress();
uintptr_t getAdc3BaseAddress();
uintptr_t getAdcCommonBaseAddress();
uintptr_t getNvicBaseAddress();
uintptr_t getRCCBaseAddress();
uintptr_t getSyscfgBaseAddress();
uintptr_t getUsartBaseAddress();
uintptr_t getUsart3BaseAddress();
uintptr_t getUsart6BaseAddress();
uintptr_t getExtiBaseAddress();
#define GPIO_A 0x40020000
#define GPIO_B 0x40020400
//..
#define GPIO_G 0x40021800
#define EXTI_BASEADDRESS getExtiBaseAddress()
#define RCC_BASEADDRESS getRCCBaseAddress()
#define NVIC_BASEADDRESS getNvicBaseAddress()
#define SYSCFG_BASEADDRESS getSyscfgBaseAddress()
#define USART1_BASEADDRESS getUsartBaseAddress()
#define USART3_BASEADDRESS getUsart3BaseAddress()
#define USART6_BASEADDRESS getUsart6BaseAddress()

#define ADC1_BASEADDRESS getAdc1BaseAddress()
#define ADC2_BASEADDRESS getAdc2BaseAddress()
#define ADC3_BASEADDRESS getAdc3BaseAddress()
#define ADC_COMMON_BASEADDRESS getAdcCommonBaseAddress()
#endif /* INC_BASEADDRESS_H_ */
