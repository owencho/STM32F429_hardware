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
    IoRegister imr;
    IoRegister emr;
    IoRegister rtsr;
    IoRegister ftsr;
    IoRegister swier;
    IoRegister pr;
};

#define exti ((ExtiRegs*)(EXTI_BASEADDRESS))
void extiSetInterruptMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode);
void extiSetEventMaskRegister(ExtiRegs *extiLoc , int pin,RequestMasked mode);
void extiSetRisingTriggerInterrupt(ExtiRegs *extiLoc , int pin,RisingTriggerStatus mode);
void extiSetFallingTriggerInterrupt(ExtiRegs *extiLoc , int pin,FallingTriggerStatus mode);
void extiSetSoftwareInterruptEvent(ExtiRegs *extiLoc, int pin);
void extiSetPendingRegister(ExtiRegs *extiLoc, int pin );
int extiReadPendingRegister(ExtiRegs *extiLoc , int pin);
#endif // EXTI_H
