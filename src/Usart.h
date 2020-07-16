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
    IDLE_INTERRUPT,READ_DATA_NOT_EMPTY,TRANS_COMPLETE,TRANS_DATA_EMPTY,
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

#define usart1 ((UsartRegs*)(USART1_BASEADDRESS))
#define usart2 ((UsartRegs*)(USART2_BASEADDRESS))
#define usart3 ((UsartRegs*)(USART3_BASEADDRESS))
#define uart4 ((UsartRegs*)(UART4_BASEADDRESS))
#define uart5 ((UsartRegs*)(UART5_BASEADDRESS))
#define usart6 ((UsartRegs*)(USART6_BASEADDRESS))
#define uart7 ((UsartRegs*)(UART7_BASEADDRESS))
#define uart8 ((UsartRegs*)(UART8_BASEADDRESS))

uint32_t usartReceive(UsartRegs* usart);
void usartSend(UsartRegs* usart,uint32_t data);
///For baudRate
void usartSetBaudRate(UsartRegs* usart,uint32_t baudRate);
uint32_t getClockForBaudRate(UsartRegs* usart);
double getUsartDivider(UsartRegs* usart,uint32_t baudRate,int over8);
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
void setUsartWakeupMode(UsartRegs* usart,WakeupMode type);
void setUsartParityMode(UsartRegs* usart,ParityMode type);

void usartSetReceiverWakeupMode(UsartRegs* usart,ReceiverWakeUpMode mode);
void usartEnableClock(UsartRegs* usart,EnableDisable mode);
void usartSetUsartAddressNode(UsartRegs* usart,uint32_t address);
void usartHalfDuplexMode(UsartRegs* usart,EnableDisable mode);
#endif // USART_H
