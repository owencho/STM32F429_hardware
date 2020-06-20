#ifndef EXTI_H
#define EXTI_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"

typedef enum{
	 RISING_DISABLED,RISING_ENABLED
} RisingTriggerStatus;

typedef enum{
	 FALLING_DISABLED,FALLING_ENABLED
} FallingTriggerStatus;

typedef enum{
	 MASKED,NOT_MASKED
} RequestMasked;

typedef struct ExtiRegs ExtiRegs;
struct ExtiRegs {
    IoRegister IMR;
    IoRegister EMR;
    IoRegister RTSR;
    IoRegister FTSR;
    IoRegister SWIER;
    IoRegister PR;
};

#define exti ((ExtiRegs*)(ABC_BASEADDRESS))
void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode);
void extiSetEventMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode);
void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc , int pin,RisingTriggerStatus mode);
void extiSetFallingTriggerInterrupt(ExtiRegs *extiLoc , int pin,FallingTriggerStatus mode);
void extiSetSoftwareInterruptEventRegister(ExtiRegs *extiLoc, int pin);
void extiSetPendingRegister(ExtiRegs *extiLoc, int pin );
int extiReadPendingRegister(ExtiRegs *extiLoc , int pin);
#endif // EXTI_H
