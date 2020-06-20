#include "Exti.h"

void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode){
	extiLoc->IMR &= ~(1 << pin);
	extiLoc->IMR |= mode << pin;
}

void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc,int pin,RisingTriggerStatus mode){
	extiLoc->RTSR &= ~(1 << pin);
	extiLoc->RTSR |= mode << pin;
}
