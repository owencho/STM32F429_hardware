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
	IoRegister cr;
	IoRegister pllcfgr;
	IoRegister cfgr;
	IoRegister cir;
	IoRegister ahb1rstr;
	IoRegister ahb2rstr;
	IoRegister ahb3rstr;
	IoRegister reserve0;
	IoRegister apb1rstr;
	IoRegister apb2rstr;
	IoRegister reserve1;
	IoRegister reserve2;
	IoRegister ahb1enr;
	IoRegister ahb2enr;
	IoRegister ahb3enr;
	IoRegister reserve3;
	IoRegister apb1enr;
	IoRegister apb2enr;
	IoRegister reserve4;
	IoRegister reserve5;
	IoRegister ahb1lpenr;
	IoRegister ahb2lpenr;
	IoRegister ahb3lpenr;
	IoRegister reserve6;
	IoRegister apb1lpenr;
	IoRegister apb2lpenr;
	IoRegister reserve7;
	IoRegister reserve8;
	IoRegister bdcr;
	IoRegister csr;
	IoRegister reserve9;
	IoRegister reserve10;
	IoRegister sscgr;
	IoRegister plli2scfgr;
	IoRegister pllsaicfgr;
	IoRegister dckcfgr;

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
void enableGpio(PortName portName);
void disableGpio(PortName portName);
void enableUSART1();
void disableUSART1();
void enableUSART6();
void disableUSART6();
void enableUART5();
void disableUART5();
void enableTimer4();
void disableTimer4();

void enableSpi1();
void disableSpi1();
void enableSpi2();
void disableSpi2();
void enableSpi3();
void disableSpi3();
void enableSpi4_5();
void disableSpi4_5();
#endif /* INC_RCC_H_ */
