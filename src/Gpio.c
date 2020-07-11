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
		if(gpio == NULL){
				return;
		}
		gpio->ospeedr &= ~(3 << (pin*2 ));
		gpio->ospeedr |= speed << (pin *2);
}

void gpioSetMode(GpioRegs *gpio , int pin , PinMode mode){
		if(gpio == NULL){
				return;
		}
		gpio->moder &= ~(3 << (pin*2 ));
		gpio->moder |= mode << (pin *2);
}

void gpioSetOutputType(GpioRegs *gpio , int pin ,PinOutputType type){
		if(gpio == NULL){
				return;
		}
		gpio->otyper &= ~(1 << pin);
		gpio->otyper |= type << pin;
}

void gpioWrite(GpioRegs *gpio , int value){
		if(gpio == NULL){
				return;
		}
		gpio->bsrr = value;
}

void gpioWriteBit(GpioRegs *gpio , int bitNumber , int value){
		if(gpio == NULL){
				return;
		}
		gpio->bsrr = 1<< (bitNumber + ((~value & 1) <<4 ));
}


int gpioReadBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL){
				return 0 ;
		}
		return (gpio->idr >> bitNumber )& 0x1;
}

void gpioToggleBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL){
				return;
		}
		gpio->odr ^= (1 << bitNumber);
}

void gpioSetAlternateFunction(GpioRegs *gpio ,PinNumber pin ,
															AlternateFunction altFunction){
		if(gpio == NULL){
				return;
		}
		if(pin > 15 || pin < 0 ){
				return;
		}
		if(pin > 7){
				gpio->afrh &= ~(15 << (pin*4));
				gpio->afrh |= altFunction << (pin*4);
		}
		else{
				gpio->afrl &= ~(15 << (pin*4));
				gpio->afrl |= altFunction << (pin*4);
		}
}
