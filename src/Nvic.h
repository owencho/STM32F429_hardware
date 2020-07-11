/*
 * Nvic.h
 *
 *  Created on: Jun 14, 2020
 *      Author: owen
 */

#ifndef INC_NVIC_H_
#define INC_NVIC_H_

#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"


typedef struct NvicRegs NvicRegs;
struct NvicRegs {
	IoRegister iser[8];
	IoRegister reserved0[3];
	IoRegister icer[8];
	IoRegister reserved1[3];
	IoRegister ispr[8];
	IoRegister reserved2[3];
	IoRegister icpr[8];
	IoRegister reserved3[3];
	IoRegister iabr[8];
	IoRegister reserved4[7];
	IoRegister ipr[60];
	IoRegister reserved5[80];
	uint16_t  reserved6;
	IoRegister stir;
};

#define nvic ((NvicRegs*)(NVIC_BASEADDRESS))

void nvicEnableInterrupt(int interruptNum);
void nvicDisableInterrupt(int interruptNum);
void nvicSetPendingInterrupt(int interruptNum);
void nvicClearPendingInterrupt(int interruptNum);
int nvicIsInterruptActive(int interruptNum);
void nvicSetInterruptPriority(int interruptNum, int interruptPriority);
int nvicGetInterruptPriority(int interruptNum);
void nvicSoftwareTriggerInterrupt(int interruptNum);

#endif /* INC_NVIC_H_ */
