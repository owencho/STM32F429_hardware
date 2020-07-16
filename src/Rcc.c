/*
 * Rcc.c
 *
 *  Created on: Jun 11, 2020
 *      Author: owen
 */
#include "Rcc.h"
#include <stdint.h>
#include <stddef.h>

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
		rcc->ahb1rstr &= ~(1 << portName);
		rcc->ahb1enr |= 1 << portName;
}

void disableGpio(PortName portName){
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
		rcc->apb2rstr &= ~ (1<<4);
		rcc-> apb2enr |= (1<< 4);
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
