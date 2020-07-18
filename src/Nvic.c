/*
 * Nvic.c
 *
 *  Created on: Jun 12, 2020
 *      Author: academic
 */
#include "Nvic.h"
#include <stdint.h>
#include <stddef.h>
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"

int arrayNumber;
int arrayPartLoc;
void nvicEnableInterrupt(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
    arrayNumber = (interruptNum >> 5);
    nvic->iser[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicDisableInterrupt(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
    arrayNumber = (interruptNum >> 5);
    nvic->icer[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicSetPendingInterrupt(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
  	arrayNumber = (interruptNum >> 5);
  	nvic->ispr[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicClearPendingInterrupt(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
  	arrayNumber = (interruptNum >> 5);
  	nvic->icpr[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

int nvicIsInterruptActive(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
    arrayNumber = (interruptNum >> 5);
  	return nvic->iabr[arrayNumber] >> (interruptNum - (arrayNumber << 5)) & 0x1;
}
void nvicSetInterruptPriority(int interruptNum, int interruptPriority){
    if(interruptNum > 239 || interruptNum < 0 ){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
    else if (interruptPriority < 0 || interruptPriority > 255){
        throwException(NVIC_INVALID_INTERRUPT_PRIORTY,"NVIC interrupt priorty is invalid only (0 -> 256) is accepted");
    }
    arrayNumber = (interruptNum >> 2);
    arrayPartLoc = 8*(interruptNum - (arrayNumber << 2));
  	nvic->ipr[arrayNumber] |= (interruptPriority <<arrayPartLoc);
}

int nvicGetInterruptPriority(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
    arrayNumber = (interruptNum >> 2);
    arrayPartLoc = 8*(interruptNum - (arrayNumber << 2));
    return ((nvic->ipr[arrayNumber] >>(arrayPartLoc))& 0xff);
}

void nvicSoftwareTriggerInterrupt(int interruptNum){
    if(interruptNum > 239 || interruptNum < 0){
        throwException(NVIC_INVALID_INTERRUPT_NUM,"NVIC interrupt number is invalid only (0 -> 239) is accepted");
    }
  	nvic->stir = (interruptNum & 0xff) ;
}
