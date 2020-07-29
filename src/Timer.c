#include "Timer.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include <stddef.h>

void timerSetControlRegister(TimerRegs * regs,int control){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->cr1 = control & 0xFFFF;
    regs->cr2 = control >> 16;
}

void timerSetSlaveMasterRegister(TimerRegs * regs,int control){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->smcr = control & 0xFFFF;
}

void timerSetCompareCaptureModeRegister(TimerRegs * regs,int control){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccmr1 = control & 0xFFFF;
    regs->ccmr2 = control >> 16 ;
}

void timerSetCompareCaptureEnableRegister(TimerRegs * regs,int control){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccer = control & 0xFFFF;
}

void timerEnableInterrupt(TimerRegs *regs , TimerInterrupt interrupt){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->dier &= ~(1 << interrupt);
    regs->dier |= 1 << interrupt;
}

void timerDisableInterrupt(TimerRegs *regs , TimerInterrupt interrupt){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->dier &= ~(1 << interrupt);
    regs->dier |= 0 << interrupt;
}

void timerEventGeneration(TimerRegs *regs , TimerEvtGeneration evtGen){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->egr &= ~(1 << evtGen);
    regs->egr |= 1 << evtGen;
}

void timerResetFlags(TimerRegs *regs , TimerFlag flag){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->sr &= ~(1 << flag);
    regs->sr |= 0 << flag;
}


int timerReadCounter(TimerRegs * regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->cnt & 0xFFFF;
}

void timerWritePrescaler(TimerRegs * regs , int prescaler){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->psc = prescaler & 0xFFFF;
}

int timerReadPrescaler(TimerRegs * regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->psc & 0xFFFF;
}

void timerWriteAutoReloadReg(TimerRegs * regs , int aReloadValue){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->arr = aReloadValue & 0xFFFF;
}

int timerReadAutoReloadReg(TimerRegs * regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->arr & 0xFFFF;
}

void timerWriteRepetitionCounter(TimerRegs * regs , int counter){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->rcr = counter & 0xFF;
}
int timerReadRepetitionCounter(TimerRegs * regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->rcr & 0xFF;
}

void timerWriteCapComReg1(TimerRegs * regs , int count){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccr1 = count & 0xFFFF;
}
int timerReadCapComReg1(TimerRegs * regs ){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->ccr1 & 0xFFFF;
}

void timerWriteCapComReg2(TimerRegs * regs , int count){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccr2 = count & 0xFFFF;
}
int timerReadCapComReg2(TimerRegs * regs ){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->ccr2 & 0xFFFF;
}

void timerWriteCapComReg3(TimerRegs * regs , int count){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccr3 = count & 0xFFFF;
}
int timerReadCapComReg3(TimerRegs * regs ){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->ccr3 & 0xFFFF;
}

void timerWriteCapComReg4(TimerRegs * regs , int count){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->ccr4 = count & 0xFFFF;
}
int timerReadCapComReg4(TimerRegs * regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    return regs->ccr4 & 0xFFFF;
}

void timerMainOutputDisable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 15);
    regs->bdtr |= 0 << 15;
}

void timerMainOutputEnable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 15);
    regs->bdtr |= 1 << 15;
}

void timerAutomaticOutputDisable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 14);
    regs->bdtr |= 0 << 14;
}

void timerAutomaticOutputEnable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 14);
    regs->bdtr |= 1 << 14;
}

void timerBreakInputSetActiveLow(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 13);
    regs->bdtr |= 0 << 13;
}

void timerBreakInputSetActiveHigh(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 13);
    regs->bdtr |= 1 << 13;
}

void timerBreakInputDisable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 12);
    regs->bdtr |= 0 << 12;
}

void timerBreakInputEnable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 12);
    regs->bdtr |= 1 << 12;
}

void timerOSSIdleDisable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 10);
    regs->bdtr |= 0 << 10;
}

void timerOSSIdleEnable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 10);
    regs->bdtr |= 1 << 10;
}

void timerOSSRunDisable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 11);
    regs->bdtr |= 0 << 11;
}

void timerOSSRunEnable(TimerRegs *regs){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(1 << 11);
    regs->bdtr |= 1 << 11;
}

void TimerLockConfiguration(TimerRegs * regs,TimerLockConfig config){
    if(regs ==NULL){
        throwException(TIMER_REG_INPUT_NULL,"Timer register input is NULL");
    }
    regs->bdtr &= ~(3 << 8);
    regs->bdtr |= config << 8;
}
