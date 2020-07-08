/*
 * Rcc.h
 *
 *  Created on: Jun 11, 2020
 *      Author: Owen
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"


typedef struct RccRegs RccRegs;
struct RccRegs {
	IoRegister CR;
	IoRegister PLLCFGR;
	IoRegister CFGR;
	IoRegister CIR;
	IoRegister AHB1RSTR;
	IoRegister AHB2RSTR;
	IoRegister AHB3RSTR;
	IoRegister RESERVE0;
	IoRegister APB1RSTR;
	IoRegister APB2RSTR;
	IoRegister RESERVE1;
	IoRegister RESERVE2;
	IoRegister AHB1ENR;
	IoRegister AHB2ENR;
	IoRegister AHB3ENR;
	IoRegister RESERVE3;
	IoRegister APB1ENR;
	IoRegister APB2ENR;
	IoRegister RESERVE4;
	IoRegister RESERVE5;
	IoRegister AHB1LPENR;
	IoRegister AHB2LPENR;
	IoRegister AHB3LPENR;
	IoRegister RESERVE6;
	IoRegister APB1LPENR;
	IoRegister APB2LPENR;
	IoRegister RESERVE7;
	IoRegister RESERVE8;
	IoRegister BDCR;
	IoRegister CSR;
	IoRegister RESERVE9;
	IoRegister RESERVE10;
	IoRegister SSCGR;
	IoRegister PLLI2SCFGR;
	IoRegister PLLSAICFGR;
	IoRegister DCKCFGR;

};

#define rcc ((RccRegs*)(RCC_BASEADDRESS))
void enableGpioG();
void disableGpioG();
void enableGpioA();
void disableGpioA();
void enableUART4();
void enableUART8();
void disableUART4();
void disableUART8();
#endif /* INC_RCC_H_ */
