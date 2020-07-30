#include "Exti.h"
#include <stddef.h>
#include "Exception.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"

void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		else if(mode > NOT_MASKED || mode < MASKED ){
				throwException(EXTI_INVALID_MASKED_MODE,"Input masked mode is invalid");
		}
		extiLoc->imr &= ~(1 << pin);
		extiLoc->imr |= mode << pin;
}

void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc,int pin,RisingTriggerStatus mode){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		else if(mode > RISING_ENABLED || mode < RISING_DISABLED ){
				throwException(EXTI_INVALID_RISING_TRIGGER_STATUS," Exti Input Rising trigger status is invalid");
		}
		extiLoc->rtsr &= ~(1 << pin);
		extiLoc->rtsr |= mode << pin;
}

void extiSetFallingTriggerInterrupt(ExtiRegs *extiLoc,int pin,FallingTriggerStatus mode){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		else if(mode > RISING_ENABLED || mode < RISING_DISABLED ){
				throwException(EXTI_INVALID_FALLING_TRIGGER_STATUS,"Input Rising trigger status is invalid");
		}
		extiLoc->ftsr &= ~(1 << pin);
		extiLoc->ftsr |= mode << pin;
}

void extiSetSoftwareInterruptEvent(ExtiRegs *extiLoc,int pin){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		extiLoc->swier &= ~(1 << pin);
		extiLoc->swier |= 1 << pin;
}

void extiSetPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		extiLoc->pr |= 1 << pin;
}

int extiReadPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc == NULL){
				throwException(EXTI_REG_INPUT_NULL,"Exti register input is NULL");
		}
		else if(pin > 22 || pin < 0 ){
				throwException(EXTI_INVALID_PIN,"Exti Input pin number is invalid");
		}
		return (extiLoc->pr >> pin) & 0x1;
}
