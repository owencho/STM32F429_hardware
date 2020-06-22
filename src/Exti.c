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

void extiSetSoftwareInterruptEvent(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22)
				return ;
		extiLoc->SWIER &= ~(1 << pin);
		extiLoc->SWIER |= 1 << pin;
}

void extiSetPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22)
				return ;
		extiLoc->PR |= 1 << pin;
}

int extiReadPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22)
				return 0; //error
		return (extiLoc->PR >> pin) & 0x1;
}
