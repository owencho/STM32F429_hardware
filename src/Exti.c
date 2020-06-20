#include "Exti.h"
#include <stddef.h>

void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode){
		if(extiLoc==NULL || pin > 22)
				return ;
		extiLoc->IMR &= ~(1 << pin);
		extiLoc->IMR |= mode << pin;
}

void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc,int pin,RisingTriggerStatus mode){
		if(extiLoc==NULL || pin > 22)
				return ;
		extiLoc->RTSR &= ~(1 << pin);
		extiLoc->RTSR |= mode << pin;
}

void extiSetFallingTriggerInterrupt(ExtiRegs *extiLoc,int pin,FallingTriggerStatus mode){
		if(extiLoc==NULL || pin > 22)
				return ;
		extiLoc->FTSR &= ~(1 << pin);
		extiLoc->FTSR |= mode << pin;
}
