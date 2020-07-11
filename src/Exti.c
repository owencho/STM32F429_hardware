#include "Exti.h"
#include <stddef.h>

void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode){
		if(extiLoc==NULL || pin > 22){
				return ;
		}
		extiLoc->imr &= ~(1 << pin);
		extiLoc->imr |= mode << pin;
}

void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc,int pin,RisingTriggerStatus mode){
		if(extiLoc==NULL || pin > 22){
				return ;
		}
		extiLoc->rtsr &= ~(1 << pin);
		extiLoc->rtsr |= mode << pin;
}

void extiSetFallingTriggerInterrupt(ExtiRegs *extiLoc,int pin,FallingTriggerStatus mode){
		if(extiLoc==NULL || pin > 22){
				return ;
		}
		extiLoc->ftsr &= ~(1 << pin);
		extiLoc->ftsr |= mode << pin;
}

void extiSetSoftwareInterruptEvent(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22){
				return ;
		}
		extiLoc->swier &= ~(1 << pin);
		extiLoc->swier |= 1 << pin;
}

void extiSetPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22){
				return ;
		}
		extiLoc->pr |= 1 << pin;
}

int extiReadPendingRegister(ExtiRegs *extiLoc,int pin){
		if(extiLoc==NULL || pin > 22){
				return 0; //error
		}
		return (extiLoc->pr >> pin) & 0x1;
}
