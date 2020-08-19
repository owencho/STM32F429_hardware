#ifndef USART_H
#define USART_H

#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"


typedef struct UsartRegs UsartRegs;
struct UsartRegs {
    IoRegister sr;
    IoRegister dr;
    IoRegister brr;
    IoRegister cr1;
    IoRegister cr2;
    IoRegister cr3;
    IoRegister gtpr;
};

typedef enum{
    IDLE_INTERRUPT,RXNE_INTERRUPT,TRANS_COMPLETE,TRANS_DATA_EMPTY,
    PARITY_ERROR,CTS_INTERRUPT,ERROR_INTERRUPT
} UsartInterrupt;

typedef enum{
    OVER_16,OVER_8
} OversampMode;

typedef enum{
    EVEN_PARITY,ODD_PARITY
} ParityMode;

typedef enum{
    IDLE_LINE,ADDRESS_MARK
} WakeupMode;

typedef enum{
    ACTIVE_MODE,MUTE_MODE
} ReceiverWakeUpMode;

typedef enum{
    DATA_8_BITS,DATA_9_BITS
} WordLength;

typedef enum{
    STOP_BIT_1,STOP_BIT_POINT_5,
    STOP_BIT_2 ,STOP_BIT_1_POINT_5
} StopBit;

#define usart1 ((UsartRegs*)(USART1_BASEADDRESS))
#define usart2 ((UsartRegs*)(USART2_BASEADDRESS))
#define usart3 ((UsartRegs*)(USART3_BASEADDRESS))
#define uart4 ((UsartRegs*)(UART4_BASEADDRESS))
#define uart5 ((UsartRegs*)(UART5_BASEADDRESS))
#define usart6 ((UsartRegs*)(USART6_BASEADDRESS))
#define uart7 ((UsartRegs*)(UART7_BASEADDRESS))
#define uart8 ((UsartRegs*)(UART8_BASEADDRESS))


void usartClearCtsFlag(UsartRegs* usart);
void usartClearLbdFlag(UsartRegs* usart);
void usartClearTxeFlag(UsartRegs* usart);
void usartClearTcFlag(UsartRegs* usart);
void usartClearRxneFlag(UsartRegs* usart);
void usartClearIdleFlag(UsartRegs* usart);
void usartClearOreFlag(UsartRegs* usart);
void usartClearNfFlag(UsartRegs* usart);
void usartClearFeFlag(UsartRegs* usart);
void usartClearPeFlag(UsartRegs* usart);

uint32_t usartReceive(UsartRegs* usart);
void usartSend(UsartRegs* usart,int data);
///For baudRate
void usartSetBaudRate(UsartRegs* usart,int baudRate);
uint32_t getClockForBaudRate(UsartRegs* usart);
double getUsartDivider(UsartRegs* usart,int baudRate,int over8);
//Other
void usartEnableInterrupt(UsartRegs* usart,UsartInterrupt type);
void usartDisableInterrupt(UsartRegs* usart,UsartInterrupt type);
int usartGetOversamplingMode(UsartRegs* usart);
void setUsartOversamplingMode(UsartRegs* usart,OversampMode mode);
void enableUsart(UsartRegs* usart);
void disableUsart(UsartRegs* usart);
void usartEnableReceiver(UsartRegs * usart);
void usartDisableReceiver(UsartRegs * usart);
void usartEnableTransmission(UsartRegs * usart);
void usartDisableTransmission(UsartRegs * usart);
void usartEnableParityControl(UsartRegs* usart);
void usartDisableParityControl(UsartRegs* usart);
void setUsartWordLength(UsartRegs* usart,WordLength type);
void setUsartWakeupMode(UsartRegs* usart,WakeupMode mode);
void setUsartParityMode(UsartRegs* usart,ParityMode mode);
void usartSetStopBit(UsartRegs* usart,StopBit mode);
void usartSetReceiverWakeupMode(UsartRegs* usart,ReceiverWakeUpMode mode);
void usartClockMode(UsartRegs* usart,EnableDisable mode);
void usartSetUsartAddressNode(UsartRegs* usart,uint32_t address);
void usartSetHalfDuplexMode(UsartRegs* usart,EnableDisable mode);
void usartSetUsartLinMode(UsartRegs* usart,EnableDisable mode);
void usartSetUsartSmartCardMode(UsartRegs* usart,EnableDisable mode);
void usartSetUsartIrDAMode(UsartRegs* usart,EnableDisable mode);
#endif // USART_H
