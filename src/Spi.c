#include "Spi.h"
#include "Exception.h"
#include "STM32Error.h"
#include <stddef.h>

void spiSetControlRegister(SpiRegs * regs,int control){
    regs->cr1 = control & 0xFFFF;
    regs->cr2 = control >> 16;
}

int spiReadDataRegister(SpiRegs * regs){
    return regs->dr;
}

void spiWriteDataRegister(SpiRegs * regs , int data){
    regs->dr = data;
}

int spiReadFlag(SpiRegs * regs, SpiFlags flag){
    return (regs->sr >> flag )& 0x1;
}

void spiResetFlag(SpiRegs * regs, SpiFlags flag){
    if(flag == SPI_UNDERRUN ||flag == SPI_CRC_ERROR ||
       flag == SPI_MODE_FAULT ||flag == SPI_OVERRUN ){
        regs->sr &= ~(1 << flag);
        regs->sr |= (0 << flag);
    }
}

int spiReadCRCPolynomialRegister(SpiRegs * regs){
    return regs->crcpr & 0xFFFF;
}

void spiWriteCRCPolynomialRegister(SpiRegs * regs , int data){
    regs->crcpr = data & 0xFFFF;
}

int spiReadReceiveCRCRegister(SpiRegs * regs){
    return regs->rxcrcr & 0xFFFF;
}

int spiReadTransmitCRCRegister(SpiRegs * regs){
    return regs->txcrcr & 0xFFFF;
}
