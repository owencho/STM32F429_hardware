#include "Timer.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"

void timerSetControlRegister()



int timerReadCounter(TimerRegs * regs){
    return regs->cnt & 0xFFFF;
}

void timerWritePrescaler(TimerRegs * regs , int prescaler){
    regs->psc = prescaler & 0xFFFF;
}

int timerReadPrescaler(TimerRegs * regs){
    return regs->psc & 0xFFFF;
}

void timerWriteAutoReloadReg(TimerRegs * regs , int aReloadValue){
    regs->arr = aReloadValue & 0xFFFF;
}

int timerReadAutoReloadReg(TimerRegs * regs){
    return regs->arr & 0xFFFF;
}

void timerWriteRepetitionCounter(TimerRegs * regs , int counter){
    regs->rcr = counter & 0xFF;
}
int timerReadRepetitionCounter(TimerRegs * regs){
    return regs->rcr & 0xFF;
}

void timerWriteCapComReg1(TimerRegs * regs , int count){
    regs->ccr1 = count & 0xFFFF;
}
int timerReadCapComReg1(TimerRegs * regs ){
    return regs->ccr1 & 0xFFFF;
}

void timerWriteCapComReg2(TimerRegs * regs , int count){
    regs->ccr2 = count & 0xFFFF;
}
int timerReadCapComReg2(TimerRegs * regs ){
    return regs->ccr2 & 0xFFFF;
}

void timerWriteCapComReg3(TimerRegs * regs , int count){
    regs->ccr3 = count & 0xFFFF;
}
int timerReadCapComReg3(TimerRegs * regs ){
    return regs->ccr3 & 0xFFFF;
}

void timerWriteCapComReg4(TimerRegs * regs , int count){
    regs->ccr4 = count & 0xFFFF;
}
int timerReadCapComReg4(TimerRegs * regs){
    return regs->ccr4 & 0xFFFF;
}
