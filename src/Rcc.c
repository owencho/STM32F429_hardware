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
		rcc->AHB1RSTR &= ~(1 << 6);
		rcc->AHB1ENR |= 1 << 6;
}

void disableGpioG(){
		rcc-> AHB1RSTR |= 1 << 6;
		rcc-> AHB1ENR &= ~(1 << 6);
}

void enableGpioA(){
		rcc->AHB1RSTR &= ~(1 << 0);
		rcc->AHB1ENR |= 1 << 0;
}

void disableGpioA(){
		rcc-> AHB1RSTR |= 1 << 0;
		rcc-> AHB1ENR &= ~(1 << 0);
}

void enableUART4(){
		rcc->APB1RSTR &= ~ (1<<19);
		rcc-> APB1ENR |= (1<< 19);
}

void disableUART4(){
		rcc->APB1RSTR |= (1<<19);
		rcc->APB1ENR &= ~ (1<<19);
}

void enableUART8(){
		rcc->APB1RSTR &= ~ (1<<31);
		rcc-> APB1ENR |= (1<< 31);
}

void disableUART8(){
		rcc->APB1RSTR |= (1<<31);
		rcc->APB1ENR &= ~(1<<31);
}
