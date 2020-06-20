/*
 * Nvic.c
 *
 *  Created on: Jun 12, 2020
 *      Author: academic
 */
#include "Nvic.h"
#include <stdint.h>
#include <stddef.h>

int arrayNumber;
int arrayPartLoc;
void nvicEnableInterrupt(int interruptNum){
    if(interruptNum > 239)
        return ;
  	arrayNumber = (interruptNum >> 5) ;
  	nvic->ISER[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicDisableInterrupt(int interruptNum){
    if(interruptNum > 239)
        return ;
  	arrayNumber = (interruptNum >> 5)  ;
  	nvic->ICER[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicSetPendingInterrupt(int interruptNum){
    if(interruptNum > 239)
        return ;
  	arrayNumber = (interruptNum >> 5)  ;
  	nvic->ISPR[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

void nvicClearPendingInterrupt(int interruptNum){
    if(interruptNum > 239)
        return ;
  	arrayNumber = (interruptNum >> 5)  ;
  	nvic->ICPR[arrayNumber] |= 1 <<(interruptNum - (arrayNumber << 5));
}

int nvicIsInterruptActive(int interruptNum){
    if(interruptNum > 239)
        return 0 ; //return error
  	arrayNumber = (interruptNum >> 5)  ;
  	return nvic->IABR[arrayNumber] >> (interruptNum - (arrayNumber << 5)) & 0x1;
}

void nvicSetInterruptPriority(int interruptNum, int interruptPriority){
    if(interruptNum > 239 || interruptNum > 256)
        return ;
  	arrayNumber = (interruptNum >> 2)  ;
    arrayPartLoc = 8*(interruptNum - (arrayNumber << 2));
  	nvic->IPR[arrayNumber] |= (interruptPriority <<arrayPartLoc);
}

int nvicGetInterruptPriority(int interruptNum){
    if(interruptNum > 239)
        return 0;
  	arrayNumber = (interruptNum >> 2);
    arrayPartLoc = 8*(interruptNum - (arrayNumber << 2));
    return ((nvic->IPR[arrayNumber] >>(arrayPartLoc))& 0xff);
}

void nvicSoftwareTriggerInterrupt(int interruptNum){
    if(interruptNum > 239)
        return ;
  	nvic->STIR = (interruptNum & 0xff) ;
}
