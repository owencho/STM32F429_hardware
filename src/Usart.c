#include "Usart.h"
#include "Clock.h"
#include "math.h"
#include "Exception.h"
#include "STM32Error.h"
#include <stddef.h>
void usartClearCtsFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 9);
    usart->sr |= 0 << 9;
}

void usartClearLbdFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 8);
    usart->sr |= 0 << 8;
}

void usartClearTxeFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 7);
    usart->sr |= 0 << 7;
}

void usartClearTcFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 6);
    usart->sr |= 0 << 6;
}

void usartClearRxneFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 5);
    usart->sr |= 0 << 5;
}

void usartClearIdleFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 4);
    usart->sr |= 0 << 4;
}

void usartClearOreFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 3);
    usart->sr |= 0 << 3;
}

void usartClearNfFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 2);
    usart->sr |= 0 << 2;
}

void usartClearFeFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 1);
    usart->sr |= 0 << 1;
}

void usartClearPeFlag(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->sr &= ~(1 << 0);
    usart->sr |= 0 << 0;
}

uint32_t usartReceive(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    return (usart->dr & 0x1FF);
}

void usartSend(UsartRegs* usart,uint32_t data){
    if( usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }else if (data < 0 ||data > 511){
        throwException(USART_SEND_INVALID_DATA,"Data for usart send is invalid size");
    }
    usart->dr = data;
}

uint32_t getClockForBaudRate(UsartRegs* usart){
    if(usart==NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    if(usart == usart1 || usart == usart6 )
        return getPCLK2Clock();
    else
        return getPCLK1Clock();
}

double getUsartDivider(UsartRegs* usart,uint32_t baudRate,int over8){
    uint32_t fclk;
    double den,num;
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    fclk  =getClockForBaudRate(usart);
    den = 8 * (2-over8);
    num = ((double)fclk / (double)baudRate) ;
    return num/den; //eqn for usartDIV
}

void usartSetBaudRate(UsartRegs* usart,uint32_t baudRate){
    int mantissaDIV , fracDIV,over8;
    double fraction,usartDIV;

    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    over8 =usartGetOversamplingMode(usart);
    usartDIV = getUsartDivider(usart,baudRate,over8);
    //to divide fraction and mantissa part
    //fraction << 4 or 3 depends on oversampling
    mantissaDIV = (int)usartDIV;
    fraction = usartDIV - mantissaDIV;
    fracDIV = (fraction *(pow(2, 4-over8)))+1 ;
    //only 3 bit for over8 ==1
    if(over8 && fracDIV > 7){
        mantissaDIV++;
        fracDIV = fracDIV -8 ;
    }
    else if(!over8 && fracDIV > 15){
        mantissaDIV++;
        fracDIV = fracDIV -16 ;
    }
    usart->brr = (mantissaDIV<<4) | (fracDIV);
}

void usartEnableInterrupt(UsartRegs* usart,UsartInterrupt type){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(type > ERROR_INTERRUPT){
        throwException(USART_INVALID_INTERRUPT,"usart interrupt input is invalid");
    }
    else if(type == CTS_INTERRUPT){
        usart->cr3 |= 1 <<10;
    }
    else if (type == ERROR_INTERRUPT){
        usart->cr3 |= 1;
    }
    else{
        usart->cr1 |= 1<< (type +4);
    }
}

void usartDisableInterrupt(UsartRegs* usart,UsartInterrupt type){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(type > ERROR_INTERRUPT || type < IDLE_INTERRUPT){
        throwException(USART_INVALID_INTERRUPT,"usart interrupt input is invalid");
    }
    else if(type == CTS_INTERRUPT){
        usart->cr3 &= ~(1 << 10);
        usart->cr3 |= 0<<10;
    }
    else if (type == ERROR_INTERRUPT){
        usart->cr3 &= ~1;
        usart->cr3 |= 0;
    }
    else{
        usart->cr1 &= ~(1 << (type +4));
        usart->cr1 |= 0<< (type +4);
    }
}

int usartGetOversamplingMode(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    return (usart->cr1 >> 15) & 0x1;
}

void setUsartOversamplingMode(UsartRegs* usart,OversampMode mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 15);
    usart->cr1 |= mode<< 15;
}

void enableUsart(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 13);
    usart->cr1 |= 1 << 13;
}

void disableUsart(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 13);
    usart->cr1 |= 0 << 13;
}

void usartEnableReceiver(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 2);
    usart->cr1 |= 1 << 2;
}

void usartDisableReceiver(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 2);
    usart->cr1 |= 0 << 2;
}
void usartEnableTransmission(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 3);
    usart->cr1 |= 1 << 3;
}

void usartDisableTransmission(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 3);
    usart->cr1 |= 0 << 3;

}void usartEnableParityControl(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 10);
    usart->cr1 |= 1 << 10;
}

void usartDisableParityControl(UsartRegs* usart){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    usart->cr1 &= ~(1 << 10);
    usart->cr1 |= 0 << 10;
}

void setUsartWordLength(UsartRegs* usart,WordLength type){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(type > DATA_9_BITS || type < DATA_8_BITS){
        throwException(USART_INVALID_TYPE,"usart input for word length type is invalid");
    }
    usart->cr1 &= ~(1 << 12);
    usart->cr1 |= type << 12;
}

void setUsartWakeupMode(UsartRegs* usart,WakeupMode mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ADDRESS_MARK || mode < IDLE_LINE){
        throwException(USART_INVALID_MODE,"usart input for wake up mode is invalid");
    }
    usart->cr1 &= ~(1 << 11);
    usart->cr1 |= mode << 11;
}

void setUsartParityMode(UsartRegs* usart,ParityMode mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ODD_PARITY || mode < EVEN_PARITY){
        throwException(USART_INVALID_MODE,"usart input for set parity mode is invalid");
    }
    usart->cr1 &= ~(1 << 9);
    usart->cr1 |= mode << 9;

}

void usartSetReceiverWakeupMode(UsartRegs* usart,ReceiverWakeUpMode mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > MUTE_MODE || mode < ACTIVE_MODE){
        throwException(USART_INVALID_MODE,"usart input for recevier wakeupMode is invalid");
    }
    usart->cr1 &= ~(1 << 1);
    usart->cr1 |= mode << 1;
}

void usartSetStopBit(UsartRegs* usart,StopBit mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > STOP_BIT_1_POINT_5 || mode < STOP_BIT_1){
        throwException(USART_INVALID_MODE,"usart input for recevier wakeupMode is invalid");
    }
    usart->cr2 &= ~(3 << 12);
    usart->cr2 |= mode << 12;
}

void usartClockMode(UsartRegs* usart,EnableDisable mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(USART_INVALID_MODE,"usart input for clock mode is invalid");
    }
    usart->cr2 &= ~(1 << 11);
    usart->cr2 |= mode << 11;
}
void usartSetUsartAddressNode(UsartRegs* usart,uint32_t address){
  if(usart == NULL){
      throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
  }
  else if(address > 15 || address < 0){
      throwException(USART_ADDRESS_INVALID,"usart address is invalid");
  }
    if(usart == NULL || address > 15){
        return ;
    }
    usart->cr2 &= ~(15 << 0);
    usart->cr2 |= address << 0;
}

void usartSetUsartLinMode(UsartRegs* usart,EnableDisable mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(USART_INVALID_MODE,"usart input for Lin mode is invalid");
    }
    usart->cr2 &= ~(1 << 14);
    usart->cr2 |= mode << 14;
}

void usartSetUsartSmartCardMode(UsartRegs* usart,EnableDisable mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(USART_INVALID_MODE,"usart input for SmartCard mode is invalid");
    }
    usart->cr3 &= ~(1 << 5);
    usart->cr3 |= mode << 5;
}

void usartSetUsartIrDAMode(UsartRegs* usart,EnableDisable mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(USART_INVALID_MODE,"usart input for SmartCard mode is invalid");
    }
    usart->cr3 &= ~(1 << 1);
    usart->cr3 |= mode << 1;
}


void usartSetHalfDuplexMode(UsartRegs* usart,EnableDisable mode){
    if(usart == NULL){
        throwException(USART_REG_INPUT_NULL,"usart register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(USART_INVALID_MODE,"usart input for SmartCard mode is invalid");
    }
    if(mode){
        //LINEN
        usartSetUsartLinMode(usart,DISABLE_MODE);
        //CLKEN
        usartClockMode(usart,DISABLE_MODE);
        //SCEN
        usartSetUsartSmartCardMode(usart,DISABLE_MODE);
        //IREN
        usartSetUsartIrDAMode(usart,DISABLE_MODE);
    }
    usart->cr3 &= ~(1 << 3);
    usart->cr3 |= mode << 3;
}
