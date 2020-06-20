/*
 * BaseAddress.h
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */

#ifndef INC_BASEADDRESS_H_
#define INC_BASEADDRESS_H_
#include <stdint.h>

uintptr_t getNvicBaseAddress();
uintptr_t getRCCBaseAddress();
#define GPIO_A 0x40020000
#define GPIO_B 0x40020400
//..
#define GPIO_G 0x40021800
#define RCC_BASEADDRESS 0x40023800
#define NVIC_BASEADDRESS getNvicBaseAddress()

#endif /* INC_BASEADDRESS_H_ */
