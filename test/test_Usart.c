#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Usart.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include "mock_Clock.h"
#include "ExceptionTestSupport.h"
CEXCEPTION_T ex;
UsartRegs fakeUsart;
UsartRegs fakeUsart3;
UsartRegs fakeUsart6;
void setUp(void){
    int i;
    char * ptr =(char*)&fakeUsart;
    for(i =0; i< sizeof(UsartRegs);i++)
        ptr[i] = 0;
    ptr =(char*)&fakeUsart3;
    for(i =0; i< sizeof(UsartRegs);i++)
        ptr[i] = 0;
    ptr =(char*)&fakeUsart6;
    for(i =0; i< sizeof(UsartRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getUsartBaseAddress(){
    return (uintptr_t)&fakeUsart;
}
uintptr_t getUsart3BaseAddress(){
    return (uintptr_t)&fakeUsart3;
}
uintptr_t getUsart6BaseAddress(){
    return (uintptr_t)&fakeUsart6;
}
void test_Usart_usartClearCtsFlag(void){
    fakeUsart.sr = (1 << 9);
    usartClearCtsFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearLbdFlag(void){
    fakeUsart.sr = (1 << 8);
    usartClearLbdFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearTxeFlag(void){
    fakeUsart.sr = (1 << 7);
    usartClearTxeFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearTcFlag(void){
    fakeUsart.sr = (1 << 6);
    usartClearTcFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearRxneFlag(void){
    fakeUsart.sr &= (1 << 5);
    usartClearRxneFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearIdleFlag(void){
    fakeUsart.sr &= (1 << 4);
    usartClearIdleFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearOreFlag(void){
    fakeUsart.sr &= (1 << 3);
    usartClearOreFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearNfFlag(void){
    fakeUsart.sr &= (1 << 2);
    usartClearNfFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearFeFlag(void){
    fakeUsart.sr &= (1 << 1);
    usartClearFeFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}

void test_Usart_usartClearPeFlag(void){
    fakeUsart.sr &= (1 << 0);
    usartClearPeFlag(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.sr);
}
//Usart Send
void test_Usart_usartSend(void){
    usartSend(usart1,0x123);
    TEST_ASSERT_EQUAL(0x123,fakeUsart.dr);
}

void test_Usart_usartSend_exceed9bit(void){
    Try{
        usartSend(usart1,0xFFF);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_SEND_INVALID_DATA,ex->errorCode);
    }
}

void test_Usart_usartSend_NULL(void){
    Try{
        usartSend(NULL,0x123);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}
//Receive
void test_Usart_usartReceive(void){
    usart1->dr = 0x114;
    TEST_ASSERT_EQUAL(0x114,usartReceive(usart1));
}

void test_Usart_usartReceive_NULL(void){
    Try{
        usartReceive(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartReceive_only_check_9bit(void){
    usart1->dr = 0xFFF;
    TEST_ASSERT_EQUAL(0x1FF,usartReceive(usart1));
}
//getClockForBaudRate
void test_Usart_getClockForBaudRate_with_uart1(void){
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(0x2AEA540,getClockForBaudRate(usart1));
}

void test_Usart_getClockForBaudRate_with_uart6(void){
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(0x2AEA540,getClockForBaudRate(usart6));
}

void test_Usart_getClockForBaudRate_with_uart3(void){
    getPCLK1Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(0x2AEA540,getClockForBaudRate(usart3));
}
void test_Usart_getClockForBaudRate_NULL(void){
    Try{
        getClockForBaudRate(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

//getUsartDivider
void test_Usart_getUsartDivider_with_uart1_over8_9600baud(void){
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(585.9375,getUsartDivider(usart1,9600,1));
}

void test_Usart_getUsartDivider_with_uart1_over16_9600baud(void){
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(292.96875,getUsartDivider(usart1,9600,0));
}

void test_Usart_getUsartDivider_with_uart1_over16_5500baud(void){
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    TEST_ASSERT_EQUAL(511.36,getUsartDivider(usart1,5500,0));
}
void test_Usart_getUsartDivider_NULL(void){
    Try{
        getUsartDivider(NULL,5500,0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}
//usartSetBaudRate

void test_Usart_usartSetBaudRate_NULL(void){
    Try{
        usartSetBaudRate(NULL,9600);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetBaudRate_8oversamp_with_uart1(void){
    setUsartOversamplingMode(usart1,OVER_8);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,9600);
    TEST_ASSERT_EQUAL((586<<4),fakeUsart.brr);
}

void test_Usart_usartSetBaudRate_8oversamp_with_uart1_with_fraction(void){
    setUsartOversamplingMode(usart1,OVER_8);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,3100);
    TEST_ASSERT_EQUAL((1814<<4)|5,fakeUsart.brr);
}

void test_Usart_usartSetBaudRate_16oversamp_with_uart1(void){
    setUsartOversamplingMode(usart1,OVER_16);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,9600);
    TEST_ASSERT_EQUAL((293<<4),fakeUsart.brr);
}

void test_Usart_usartSetBaudRate_16oversamp_with_5500baud_uart1(void){
    setUsartOversamplingMode(usart1,OVER_16);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,5500);
    TEST_ASSERT_EQUAL((511<<4)+(6<<0),fakeUsart.brr);
}

//Enable Interrupt
void test_Usart_usartEnableInterrupt_NULL(void){
    Try{
        usartEnableInterrupt(NULL,IDLE_INTERRUPT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Usart_usartEnableInterrupt_IDLE_INTERRUPT(void){
    usartEnableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<4,fakeUsart.cr1);
}
void test_Usart_usartEnableInterrupt_RXNE_INTERRUPT(void){
    usartEnableInterrupt(usart1,RXNE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.cr1);
}
void test_Usart_usartEnableInterrupt_TRANS_COMPLETE(void){
    usartEnableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(1<<6,fakeUsart.cr1);
}
void test_Usart_usartEnableInterrupt_TRANS_DATA_EMPTY(void){
    usartEnableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(1<<7,fakeUsart.cr1);
}
void test_Usart_usartEnableInterrupt_PARITY_ERROR(void){
    usartEnableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(1<<8,fakeUsart.cr1);
}
void test_Usart_usartEnableInterrupt_CTS_INTERRUPT(void){
    usartEnableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.cr3);
}
void test_Usart_usartEnableInterrupt_ERROR_INTERRUPT(void){
    usartEnableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(1,fakeUsart.cr3);
}
void test_Usart_usartDisableInterrupt_NULL(void){
    Try{
        usartDisableInterrupt(NULL,IDLE_INTERRUPT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartDisableInterrupt_INVALID_mode(void){
    Try{
        usartDisableInterrupt(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_INTERRUPT,ex->errorCode);
    }
}

void test_Usart_usartDisableInterrupt_INVALID_positive_mode(void){
    Try{
        usartDisableInterrupt(usart1,7);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_INTERRUPT,ex->errorCode);
    }
}
void test_Usart_usartDisableInterrupt_IDLE_INTERRUPT(void){
    usartEnableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<4,fakeUsart.cr1);
    usartDisableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartDisableInterrupt_READ_DATA_NOT_EMPTY(void){
    usartEnableInterrupt(usart1,RXNE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.cr1);
    usartDisableInterrupt(usart1,RXNE_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartDisableInterrupt_TRANS_COMPLETE(void){
    usartEnableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(1<<6,fakeUsart.cr1);
    usartDisableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartDisableInterrupt_TRANS_DATA_EMPTY(void){
    usartEnableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(1<<7,fakeUsart.cr1);
    usartDisableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartDisableInterrupt_PARITY_ERROR(void){
    usartEnableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(1<<8,fakeUsart.cr1);
    usartDisableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartDisableInterrupt_CTS_INTERRUPT(void){
    usartEnableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.cr3);
    usartDisableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr3);
}
void test_Usart_usartDisableInterrupt_ERROR_INTERRUPT(void){
    usartEnableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(1,fakeUsart.cr3);
    usartDisableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr3);
}

void test_Usart_setUsartOversamplingMode_SAMP_16(void){
    setUsartOversamplingMode(usart1,OVER_16);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_setUsartOversamplingMode_SAMP_8(void){
    setUsartOversamplingMode(usart1,OVER_8);
    TEST_ASSERT_EQUAL(1<<15,fakeUsart.cr1);
}

void test_Usart_setUsartOversamplingMode_NULL_input(void){
    Try{
        setUsartOversamplingMode(NULL,OVER_8);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartGetOversamplingMode_SAMP_16(void){
    setUsartOversamplingMode(usart1,OVER_16);
    TEST_ASSERT_EQUAL(0,usartGetOversamplingMode(usart1));
}

void test_Usart_usartGetOversamplingMode_SAMP_8(void){
    setUsartOversamplingMode(usart1,OVER_8);
    TEST_ASSERT_EQUAL(1,usartGetOversamplingMode(usart1));
}

void test_Usart_usartGetOversamplingMode_NULL_input(void){
    Try{
        usartGetOversamplingMode(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_enableUsart(void){
    enableUsart(usart1);
    TEST_ASSERT_EQUAL(1<<13,fakeUsart.cr1);
}

void test_Usart_enableUsart_NULL_input(void){
    Try{
        enableUsart(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_disableUsart(void){
    enableUsart(usart1);
    TEST_ASSERT_EQUAL(1<<13,fakeUsart.cr1);
    disableUsart(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_disableUsart_NULL_input(void){
    Try{
        disableUsart(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartEnableReceiver(void){
    usartEnableReceiver(usart1);
    TEST_ASSERT_EQUAL(1<<2,fakeUsart.cr1);
}

void test_Usart_usartEnableReceiver_NULL_input(void){
    Try{
        usartEnableReceiver(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartDisableReceiver(void){
    usartEnableReceiver(usart1);
    TEST_ASSERT_EQUAL(1<<2,fakeUsart.cr1);
    usartDisableReceiver(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_usartDisableReceiver_NULL_input(void){
    Try{
        usartDisableReceiver(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartEnableTransmission(void){
    usartEnableTransmission(usart1);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.cr1);
}

void test_Usart_usartEnableTransmission_NULL_input(void){
    Try{
        usartEnableTransmission(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartDisableTransmission(void){
    usartEnableTransmission(usart1);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.cr1);
    usartDisableTransmission(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_usartDisableTransmission_NULL_input(void){
    Try{
        usartDisableReceiver(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartEnableParityControl(void){
    usartEnableParityControl(usart1);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.cr1);
}

void test_Usart_usartEnableParityControl_NULL_input(void){
    Try{
        usartEnableParityControl(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartDisableParityControl(void){
    usartEnableParityControl(usart1);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.cr1);
    usartDisableParityControl(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_usartDisableParityControl_NULL_input(void){
    Try{
        usartDisableParityControl(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_setUsartWordLength(void){
    setUsartWordLength(usart1,DATA_9_BITS);
    TEST_ASSERT_EQUAL(1<<12,fakeUsart.cr1);
    setUsartWordLength(usart1,DATA_8_BITS);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_setUsartWordLength_NULL_input(void){
    Try{
        setUsartWordLength(NULL,DATA_8_BITS);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_setUsartWordLength_neg_invalid_input(void){
    Try{
        setUsartWordLength(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_TYPE,ex->errorCode);
    }
}

void test_Usart_setUsartWordLength_pos_invalid_input(void){
    Try{
        setUsartWordLength(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_TYPE,ex->errorCode);
    }
}

void test_Usart_usartSetStopBit(void){
    usartSetStopBit(usart1,STOP_BIT_1_POINT_5);
    TEST_ASSERT_EQUAL(3<<12,fakeUsart.cr2);
    usartSetStopBit(usart1,STOP_BIT_1);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr2);
}

void test_Usart_usartSetStopBit_NULL_input(void){
    Try{
        usartSetStopBit(NULL,STOP_BIT_1_POINT_5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetStopBit_neg_invalid_input(void){
    Try{
        usartSetStopBit(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetStopBit_pos_invalid_input(void){
    Try{
        usartSetStopBit(usart1,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}


void test_Usart_setUsartWakeupMode(void){
    setUsartWakeupMode(usart1,ADDRESS_MARK);
    TEST_ASSERT_EQUAL(1<<11,fakeUsart.cr1);
    setUsartWakeupMode(usart1,IDLE_LINE);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_setUsartWakeupMode_NULL_input(void){
    Try{
        setUsartWakeupMode(NULL,IDLE_LINE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_setUsartWakeupMode_neg_invalid_input(void){
    Try{
        setUsartWakeupMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_setUsartWakeupMode_pos_invalid_input(void){
    Try{
        setUsartWakeupMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_setUsartParityMode(void){
    setUsartParityMode(usart1,ODD_PARITY);
    TEST_ASSERT_EQUAL(1<<9,fakeUsart.cr1);
    setUsartParityMode(usart1,EVEN_PARITY);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}

void test_Usart_setUsartParityMode_NULL_input(void){
    Try{
        setUsartParityMode(NULL,ODD_PARITY);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_setUsartParityMode_neg_invalid_input(void){
    Try{
        setUsartParityMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_setUsartParityMode_pos_invalid_input(void){
    Try{
        setUsartParityMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetReceiverWakeupMode_NULL_input(void){
    Try{
        usartSetReceiverWakeupMode(NULL,ACTIVE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetReceiverWakeupMode_neg_invalid_input(void){
    Try{
        usartSetReceiverWakeupMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetReceiverWakeupMode_pos_invalid_input(void){
    Try{
        usartSetReceiverWakeupMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetReceiverWakeupMode_ACTIVE_MODE(void){
    usartSetReceiverWakeupMode(usart1,ACTIVE_MODE);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr1);
}
void test_Usart_usartSetReceiverWakeupMode_MUTE_MODE(void){
    usartSetReceiverWakeupMode(usart1,MUTE_MODE);
    TEST_ASSERT_EQUAL(1<<1,fakeUsart.cr1);
}
void test_Usart_usartClockMode_NULL_input(void){
    Try{
        usartClockMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartClockMode_neg_invalid_input(void){
    Try{
        usartSetReceiverWakeupMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartClockMode_pos_invalid_input(void){
    Try{
        usartSetReceiverWakeupMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartClockMode_enable(void){
    usartClockMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<11,fakeUsart.cr2);
}
void test_Usart_usartClockMode_disable(void){
    usartClockMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<11,fakeUsart.cr2);
    usartClockMode(usart1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<11,fakeUsart.cr2);
}
void test_Usart_usartSetUsartAddressNode_NULL_input(void){
    Try{
        usartSetUsartAddressNode(NULL,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetUsartAddressNode_neg_invalid_input(void){
    Try{
        usartSetUsartAddressNode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_ADDRESS_INVALID,ex->errorCode);
    }
}

void test_Usart_usartSetUsartAddressNode_pos_invalid_input(void){
    Try{
        usartSetUsartAddressNode(usart1,16);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_ADDRESS_INVALID,ex->errorCode);
    }
}
void test_Usart_usartSetUsartAddressNode_address_0(void){
    usartSetUsartAddressNode(usart1,0);
    TEST_ASSERT_EQUAL(0,fakeUsart.cr2);
}
void test_Usart_usartSetUsartAddressNode_address_5(void){
    usartSetUsartAddressNode(usart1,15);
    TEST_ASSERT_EQUAL(15,fakeUsart.cr2);
}
void test_Usart_usartSetHalfDuplexMode_NULL_input(void){
    Try{
        usartSetHalfDuplexMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetHalfDuplexMode_neg_invalid_input(void){
    Try{
        usartSetHalfDuplexMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetHalfDuplexMode_pos_invalid_input(void){
    Try{
        usartSetHalfDuplexMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetHalfDuplexMode_enable(void){
    usartSetHalfDuplexMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.cr3);
}
void test_Usart_usartSetHalfDuplexMode_disable(void){
    usartSetHalfDuplexMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.cr3);
    usartSetHalfDuplexMode(usart1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<3,fakeUsart.cr3);
}
void test_Usart_usartSetUsartLinMode_NULL_input(void){
    Try{
        usartSetUsartLinMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetUsartLinMode_neg_invalid_input(void){
    Try{
        usartSetUsartLinMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetUsartLinMode_pos_invalid_input(void){
    Try{
        usartSetUsartLinMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetUsartLinMode_enable(void){
    usartSetUsartLinMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<14,fakeUsart.cr2);
}
void test_Usart_usartSetUsartLinMode_disable(void){
    usartSetUsartLinMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<14,fakeUsart.cr2);
    usartSetUsartLinMode(usart1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<14,fakeUsart.cr2);
}
void test_Usart_usartSetUsartSmartCardMode_NULL_input(void){
    Try{
        usartSetUsartSmartCardMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetUsartSmartCardMode_neg_invalid_input(void){
    Try{
        usartSetUsartSmartCardMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetUsartSmartCardMode_pos_invalid_input(void){
    Try{
        usartSetUsartSmartCardMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetUsartSmartCardMode_enable(void){
    usartSetUsartSmartCardMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.cr3);
}

void test_Usart_usartSetUsartSmartCardMode_disable(void){
    usartSetUsartSmartCardMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.cr3);
    usartSetUsartSmartCardMode(usart1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<5,fakeUsart.cr3);
}
void test_Usart_usartSetUsartIrDAMode_NULL_input(void){
    Try{
        usartSetUsartIrDAMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Usart_usartSetUsartIrDAMode_neg_invalid_input(void){
    Try{
        usartSetUsartIrDAMode(usart1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}

void test_Usart_usartSetUsartIrDAMode_pos_invalid_input(void){
    Try{
        usartSetUsartIrDAMode(usart1,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(USART_INVALID_MODE,ex->errorCode);
    }
}
void test_Usart_usartSetUsartIrDAMode_enable(void){
    usartSetUsartIrDAMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<1,fakeUsart.cr3);
}

void test_Usart_usartSetUsartIrDAMode_disable(void){
    usartSetUsartIrDAMode(usart1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<1,fakeUsart.cr3);
    usartSetUsartIrDAMode(usart1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<1,fakeUsart.cr3);
}
