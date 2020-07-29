#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "TimerMacro.h"
typedef enum{
  	UIF_FLAG,CC1IF_FLAG,CC2IF_FLAG,CC3IF_FLAG,CC4IF_FLAG,COMIF_FLAG,TIF_FLAG,
    BIF_FLAG,TIMER_RESERVED_FLAG,CC1OF_FLAG,CC2OF_FLAG,CC3OF_FLAG,CC4OF_FLAG,
} TimerFlag;

typedef enum{
    UG_EGR,CC1G_EGR,CC2G_EGR,CC3G_EGR,CC4G_EGR,COMG_EGR,TG_EGR,BG_EGR
} TimerEvtGeneration;

typedef enum{
    TIMER_LOCK_OFF ,TIMER_LOCK_L1,TIMER_LOCK_L2,TIMER_LOCK_L3
} TimerLockConfig;

typedef enum{
    UIE_INT,CC1_INT,CC2_INT,CC3_INT,CC4_INT,COM_INT,TRIG_INT,
    BREAK_INT,UPDATE_DMA_REQ,CC1_DMA_REQ,CC2_DMA_REQ,CC3_DMA_REQ,
    CC4_DMA_REQ,COM_DMA_REQ,TRIG_DMA_REQ
} TimerInterrupt;

typedef struct TimerRegs TimerRegs;
struct TimerRegs {
    IoRegister cr1;
    IoRegister cr2;
    IoRegister smcr;
    IoRegister dier;
    IoRegister sr;
    IoRegister egr;
    IoRegister ccmr1;
    IoRegister ccmr2;
    IoRegister ccer;
    IoRegister cnt;
    IoRegister psc;
    IoRegister arr;
    IoRegister rcr;
    IoRegister ccr1;
    IoRegister ccr2;
    IoRegister ccr3;
    IoRegister ccr4;
    IoRegister bdtr;
    IoRegister dcr;
    IoRegister dmar;
};
//function
void timerSetControlRegister(TimerRegs * regs,int control);
void timerSetSlaveMasterRegister(TimerRegs * regs,int control);
void timerSetCompareCaptureModeRegister(TimerRegs * regs,int control);
void timerSetCompareCaptureEnableRegister(TimerRegs * regs,int control);
void timerEnableInterrupt(TimerRegs *regs , TimerInterrupt interrupt);
void timerDisableInterrupt(TimerRegs *regs , TimerInterrupt interrupt);
void timerEventGeneration(TimerRegs *regs , TimerEvtGeneration evtGen);
void timerResetFlags(TimerRegs *regs , TimerFlag flag);

int timerReadCounter(TimerRegs * regs);

void timerWritePrescaler(TimerRegs * regs , int prescaler);
int timerReadPrescaler(TimerRegs * regs);

void timerWriteAutoReloadReg(TimerRegs * regs , int aReloadValue);
int timerReadAutoReloadReg(TimerRegs * regs);

void timerWriteRepetitionCounter(TimerRegs * regs , int counter);
int timerReadRepetitionCounter(TimerRegs * regs);

void timerWriteCapComReg1(TimerRegs * regs , int count);
int timerReadCapComReg1(TimerRegs * regs );

void timerWriteCapComReg2(TimerRegs * regs , int count);
int timerReadCapComReg2(TimerRegs * regs);

void timerWriteCapComReg3(TimerRegs * regs , int count);
int timerReadCapComReg3(TimerRegs * regs);

void timerWriteCapComReg4(TimerRegs * regs , int count);
int timerReadCapComReg4(TimerRegs * regs );

void timerMainOutputDisable(TimerRegs * regs);
void timerMainOutputEnable(TimerRegs * regs);

void timerAutomaticOutputDisable(TimerRegs * regs);
void timerAutomaticOutputEnable(TimerRegs * regs);

void timerBreakInputDisable(TimerRegs * regs);
void timerBreakInputEnable(TimerRegs * regs);

void timerBreakInputSetActiveLow(TimerRegs * regs);
void timerBreakInputSetActiveHigh(TimerRegs * regs);

void timerOSSIdleDisable(TimerRegs * regs);
void timerOSSIdleEnable(TimerRegs * regs);

void timerOSSRunDisable(TimerRegs * regs);
void timerOSSRunEnable(TimerRegs * regs);

void TimerLockConfiguration(TimerRegs * regs,TimerLockConfig config);
#endif // TIMER_H
