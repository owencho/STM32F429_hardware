/*
 * Gpio.c
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */


#include "Gpio.h"
#include "Common.h"
#include <stddef.h>
#include "Exception.h"
#include "STM32Error.h"

void gpioSetPinSpeed(GpioRegs *gpio , int pin , PinSpeed speed){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(pin > 15 || pin < 0 ){
				throwException(GPIO_INVALID_PIN,"Input pin number is invalid");
		}
		else if(speed > VERY_HI_SPEED || speed < LOW_SPEED ){
				throwException(GPIO_INVALID_SPEED_MODE,"Input speed mode is invalid");
		}
		gpio->ospeedr &= ~(3 << (pin*2 ));
		gpio->ospeedr |= speed << (pin *2);
}

void gpioSetPullUpDownReg(GpioRegs *gpio , int pin , PinPullUpDown type){
		gpio->pupdr &= ~(3 << (pin*2 ));
		gpio->pupdr |= type << (pin *2);
}

void gpioSetMode(GpioRegs *gpio , int pin , PinMode mode){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(pin > 15 || pin < 0 ){
				throwException(GPIO_INVALID_PIN,"Input pin number is invalid");
		}
		else if(mode > GPIO_ANALOG || mode < GPIO_IN ){
				throwException(GPIO_INVALID_PIN_MODE,"Input pin mode is invalid");
		}
		gpio->moder &= ~(3 << (pin*2 ));
		gpio->moder |= mode << (pin *2);
}

void gpioSetOutputType(GpioRegs *gpio , int pin ,PinOutputType type){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(pin > 15 || pin < 0 ){
				throwException(GPIO_INVALID_PIN,"Input pin number is invalid");
		}
		else if(type > PUSH_PULL || type < OPEN_DRAIN ){
				throwException(GPIO_INVALID_PIN_MODE,"Input pin mode is invalid");
		}
		gpio->otyper &= ~(1 << pin);
		gpio->otyper |= type << pin;
}

void gpioWrite(GpioRegs *gpio , int value){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		gpio->bsrr = value;
}

void gpioWriteBit(GpioRegs *gpio , int bitNumber , int value){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(bitNumber > 15 || bitNumber < 0 ){
				throwException(GPIO_INVALID_BIT_NUM,"Input bit number is invalid");
		}
		else if(value > 1 || value < 0 ){
				throwException(GPIO_INVALID_BIT_VALUE,"Input bit number is invalid");
		}
		gpio->bsrr = 1<< (bitNumber + ((~value & 1) <<4 ));
}


int gpioReadBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(bitNumber > 15 || bitNumber < 0 ){
				throwException(GPIO_INVALID_BIT_NUM,"Input bit number is invalid");
		}
		return (gpio->idr >> bitNumber )& 0x1;
}

void gpioToggleBit(GpioRegs *gpio , int bitNumber ){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		else if(bitNumber > 15 || bitNumber < 0 ){
				throwException(GPIO_INVALID_BIT_NUM,"Input bit number is invalid");
		}
		gpio->odr ^= (1 << bitNumber);
}

void gpioSetAlternateFunction(GpioRegs *gpio ,PinNumber pin ,
															AlternateFunction altFunction){
		if(gpio == NULL){
				throwException(GPIO_REG_INPUT_NULL,"Gpio register input is NULL");
		}
		if(pin > 15 || pin < 0 ){
				throwException(GPIO_INVALID_PIN,"Input pin number is invalid");
		}
		if(altFunction > AF15 || altFunction < AF0 ){
				throwException(GPIO_INVALID_ALT_FUNCTION,"Input alternative function is invalid");
		}

		if(pin > 7){
				gpio->afrh &= ~(15 << ((pin-8)*4));
				gpio->afrh |= altFunction << ((pin-8)*4);
		}
		else{
				gpio->afrl &= ~(15 << (pin*4));
				gpio->afrl |= altFunction << (pin*4);
		}
}
