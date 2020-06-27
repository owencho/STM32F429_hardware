#include "Usart.h"
#include "Clock.h"
#include "Math.h"


uint32_t usartReceive(UsartRegs* usart){
    if(usart == NULL)
        return 0;
    return (usart->DR & 0x1FF);
}

void usartSend(UsartRegs* usart,uint32_t data){
    if(data > 511 || usart == NULL)
        return ;
    usart->DR = data;
}

uint32_t getClockForBaudRate(UsartRegs* usart){
    if(usart==NULL)
        return 0;
    if(usart == usart1 || usart == usart6 )
        return getPCLK2Clock();
    else
        return getPCLK1Clock();
}

double getUsartDivider(UsartRegs* usart,uint32_t baudRate,int over8){
    uint32_t fclk;
    double den,num;

    fclk  =getClockForBaudRate(usart);
    den = 8 * (2-over8);
    num = ((double)fclk / (double)baudRate) ;
    return num/den; //eqn for usartDIV
}

void usartSetBaudRate(UsartRegs* usart,uint32_t baudRate){
    int mantissaDIV , fracDIV,over8;
    double fraction,usartDIV;

    if(usart == NULL)
        return ;
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
    usart->BRR = (mantissaDIV<<4) | (fracDIV);
}

void usartEnableInterrupt(UsartRegs* usart,UsartInterrupt type){
    if(type == CTS_INTERRUPT){
        usart->CR3 |= 1 <<10;
    }
    else if (type == ERROR_INTERRUPT){
        usart->CR3 |= 1;
    }
    else{
        usart->CR1 |= 1<< type +4;
    }
}

void usartDisableInterrupt(UsartRegs* usart,UsartInterrupt type){
    if(type == CTS_INTERRUPT){
        usart->CR3 &= ~(1 << 10);
        usart->CR3 |= 0<<10;
    }
    else if (type == ERROR_INTERRUPT){
        usart->CR3 &= ~1;
        usart->CR3 |= 0;
    }
    else{
        usart->CR1 &= ~(1 << type +4);
        usart->CR1 |= 0<< type +4;
    }
}

int usartGetOversamplingMode(UsartRegs* usart){
    if(usart == NULL)
        return 0;
    return (usart->CR1 >> 15) & 0x1;
}

void setUsartOversamplingMode(UsartRegs* usart,OversampMode mode){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 15);
    usart->CR1 |= mode<< 15;
}

void enableUsart(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 13);
    usart->CR1 |= 1 << 13;
}

void disableUsart(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 13);
    usart->CR1 |= 0 << 13;
}

void usartEnableReceiver(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 2);
    usart->CR1 |= 1 << 2;
}

void usartDisableReceiver(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 2);
    usart->CR1 |= 0 << 2;
}
void usartEnableTransmission(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 3);
    usart->CR1 |= 1 << 3;
}

void usartDisableTransmission(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 3);
    usart->CR1 |= 0 << 3;

}void usartEnableParityControl(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 10);
    usart->CR1 |= 1 << 10;
}

void usartDisableParityControl(UsartRegs* usart){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 10);
    usart->CR1 |= 0 << 10;
}

void setUsartWordLength(UsartRegs* usart,WordLength type){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 12);
    usart->CR1 |= type << 12;
}

void setUsartWakeupMode(UsartRegs* usart,WakeupMode type){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 11);
    usart->CR1 |= type << 11;
}

void setUsartParityMode(UsartRegs* usart,ParityMode type){
    if(usart == NULL)
        return ;
    usart->CR1 &= ~(1 << 9);
    usart->CR1 |= type << 9;
}
