#ifndef SPI_H
#define SPI_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
typedef struct SpiRegs SpiRegs;
struct SpiRegs {
    IoRegister cr1;
    IoRegister cr2;
    IoRegister sr;
    IoRegister dr;
    IoRegister crcpr;
    IoRegister rxcrcr;
    IoRegister txcrcr;
    IoRegister i2scfgr;
    IoRegister i2spr;
};

typedef enum{
    SPI_RECEIVE_NOT_EMPTY ,SPI_TRANSMIT_EMPTY,CHANNEL_SIDE,SPI_UNDERRUN,SPI_CRC_ERROR,
    SPI_MODE_FAULT,SPI_OVERRUN,SPI_BUSY,SPI_FRAME_FORMAT_ERROR
} SpiFlags;


#define spi1 ((SpiRegs*)(SPI1_BASEADDRESS))
#define spi2 ((SpiRegs*)(SPI2_BASEADDRESS))
#define spi3 ((SpiRegs*)(SPI3_BASEADDRESS))
#define spi4 ((SpiRegs*)(SPI4_BASEADDRESS))
#define spi5 ((SpiRegs*)(SPI5_BASEADDRESS))
#define spi6 ((SpiRegs*)(SPI6_BASEADDRESS))

void spiSetControlRegister(SpiRegs * regs,int control);
int spiReadFlag(SpiRegs * regs , SpiFlags flag);
void spiResetFlag(SpiRegs * regs, SpiFlags flag);
int spiReadDataRegister(SpiRegs * regs);
void spiWriteDataRegister(SpiRegs * regs , int data);
int spiReadCRCPolynomialRegister(SpiRegs * regs);
void spiWriteCRCPolynomialRegister(SpiRegs * regs , int data);
int spiReadReceiveCRCRegister(SpiRegs * regs);
int spiReadTransmitCRCRegister(SpiRegs * regs);
#endif // SPI_H
