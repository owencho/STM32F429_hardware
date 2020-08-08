/*
 * Rcc.c
 *
 *  Created on: Jun 11, 2020
 *      Author: owen
 */
#include "Rcc.h"
#include <stdint.h>
#include <stddef.h>
#include "Exception.h"
#include "STM32Error.h"

void enableGpioG(){
		rcc->ahb1rstr &= ~(1 << 6);
		rcc->ahb1enr |= 1 << 6;
}

void disableGpioG(){
		rcc-> ahb1rstr |= 1 << 6;
		rcc-> ahb1enr &= ~(1 << 6);
}

void enableGpioA(){
		rcc->ahb1rstr &= ~(1 << 0);
		rcc->ahb1enr |= 1 << 0;
}

void disableGpioA(){
		rcc-> ahb1rstr |= 1 << 0;
		rcc-> ahb1enr &= ~(1 << 0);
}

void enableGpio(PortName portName){
		if(portName > PORT_K ||portName < PORT_A ){
				throwException(RCC_INVALID_PORTNAME,"invalid GPIO input name");
		}
		rcc->ahb1rstr &= ~(1 << portName);
		rcc->ahb1enr |= 1 << portName;
}

void disableGpio(PortName portName){
		if(portName < PORT_A ||portName > PORT_K){
				throwException(RCC_INVALID_PORTNAME,"invalid GPIO input name");
		}
		rcc-> ahb1rstr |= 1 << portName;
		rcc-> ahb1enr &= ~(1 << portName);
}

void enableUART4(){
		rcc->apb1rstr &= ~ (1<<19);
		rcc-> apb1enr |= (1<< 19);
}

void disableUART4(){
		rcc->apb1rstr |= (1<<19);
		rcc->apb1enr &= ~ (1<<19);
}

void enableUART8(){
		rcc->apb1rstr &= ~ (1<<31);
		rcc-> apb1enr |= (1<< 31);
}

void disableUART8(){
		rcc->apb1rstr |= (1<<31);
		rcc->apb1enr &= ~(1<<31);
}

void enableUSART1(){
		rcc->apb2rstr &= ~ (1<<4);
		rcc-> apb2enr |= (1<< 4);
}

void disableUSART1(){
		rcc->apb2rstr |= (1<<4);
		rcc->apb2enr &= ~ (1<<4);
}

void enableUSART6(){
		rcc->apb2rstr &= ~ (1<<5);
		rcc-> apb2enr |= (1<< 5);
}

void disableUSART6(){
		rcc->apb2rstr |= (1<<5);
		rcc->apb2enr &= ~ (1<<5);
}

void enableUART5(){
		rcc->apb1rstr &= ~ (1<<20);
		rcc-> apb1enr |= (1<< 20);
}

void disableUART5(){
		rcc->apb1rstr |= (1<<20);
		rcc->apb1enr &= ~(1<<20);
}

void enableTimer4(){
		rcc->apb1rstr &= ~ (1<<2);
		rcc-> apb1enr |= (1<< 2);
}

void disableTimer4(){
		rcc->apb1rstr |= (1<<2);
		rcc->apb1enr &= ~ (1<<2);
}

void enableSpi1(){
		rcc->apb2rstr &= ~ (1<<12);
		rcc-> apb2enr |= (1<< 12);
}

void disableSpi1(){
		rcc->apb2rstr |= (1<<12);
		rcc->apb2enr &= ~ (1<<12);
}

void enableSpi2(){
		rcc->apb1rstr &= ~ (1<<14);
		rcc-> apb1enr |= (1<< 14);
}

void disableSpi2(){
		rcc->apb1rstr |= (1<<14);
		rcc->apb1enr &= ~ (1<<14);
}

void enableSpi3(){
		rcc->apb1rstr &= ~ (1<<15);
		rcc-> apb1enr |= (1<< 15);
}

void disableSpi3(){
		rcc->apb1rstr |= (1<<15);
		rcc->apb1enr &= ~ (1<<15);
}

void enableSpi4_5(){
		rcc->apb2rstr &= ~ (1<<13);
		rcc-> apb2enr |= (1<< 13);
}

void disableSpi4_5(){
		rcc->apb2rstr |= (1<<13);
		rcc->apb2enr &= ~ (1<<13);
}
