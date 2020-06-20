/*
 * Gpio.c
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */


#include "Gpio.h"
#include "Common.h"
#include <stddef.h>

void gpioSetPinSpeed(GpioRegs *gpio , int pin , PinSpeed speed){
		if(gpio == NULL)
				return;
		gpio->OSPEEDR &= ~(3 << (pin*2 ));
		gpio->OSPEEDR |= speed << (pin *2);
}

void gpioSetMode(GpioRegs *gpio , int pin , PinMode mode){
		if(gpio == NULL)
				return;
		gpio->MODER &= ~(3 << (pin*2 ));
		gpio->MODER |= mode << (pin *2);
}

void gpioSetOutputType(GpioRegs *gpio , int pin ,PinOutputType type){
		if(gpio == NULL)
				return;
		gpio->OTYPER &= ~(1 << pin);
		gpio->OTYPER |= type << pin;
}

void gpioWrite(GpioRegs *gpio , int value){
		if(gpio == NULL)
				return;
		gpio->BSRR = value;
}

void gpioWriteBit(GpioRegs *gpio , int bitNumber , int value){
		if(gpio == NULL)
				return;
		gpio->BSRR = 1<< (bitNumber + ((~value & 1) <<4 ));
}


int gpioReadBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL)
				return 0;
		return (gpio->IDR >> bitNumber )& 0x1;
}

void gpioToggleBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL)
				return;
		gpio->ODR ^= (1 << bitNumber);
}
