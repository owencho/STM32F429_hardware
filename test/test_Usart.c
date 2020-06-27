#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Usart.h"
#include "mock_Clock.h"

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
//Usart Send
void test_Usart_usartSend(void){
    usartSend(usart1,0x123);
    TEST_ASSERT_EQUAL(0x123,fakeUsart.DR);
}

void test_Usart_usartSend_exceed9bit(void){
    usartSend(usart1,0xFFF);
    TEST_ASSERT_EQUAL(0,fakeUsart.DR);
}

void test_Usart_usartSend_NULL(void){
    usartSend(NULL,0x123);
    TEST_IGNORE_MESSAGE("havent implement");
    TEST_ASSERT_EQUAL(0,fakeUsart.DR);
}
//Receive
void test_Usart_usartReceive(void){
    usart1->DR = 0x114;
    TEST_ASSERT_EQUAL(0x114,usartReceive(usart1));
}

void test_Usart_usartReceive_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
    TEST_ASSERT_EQUAL(0,usartReceive(NULL));
}

void test_Usart_usartReceive_only_check_9bit(void){
    usart1->DR = 0xFFF;
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
    TEST_IGNORE_MESSAGE("havent implement");
    TEST_ASSERT_EQUAL(0,getClockForBaudRate(NULL));
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
    TEST_IGNORE_MESSAGE("havent implement");
    TEST_ASSERT_EQUAL(0,getUsartDivider(NULL,5500,0));
}
//usartSetBaudRate

void test_Usart_usartSetBaudRate_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartSetBaudRate(NULL,9600);
}

void test_Usart_usartSetBaudRate_8oversamp_with_uart1(void){
    setUsartOversamplingMode(usart1,OVER_8);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,9600);
    TEST_ASSERT_EQUAL((586<<4),fakeUsart.BRR);
}

void test_Usart_usartSetBaudRate_8oversamp_with_uart1_with_fraction(void){
    setUsartOversamplingMode(usart1,OVER_8);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,3100);
    TEST_ASSERT_EQUAL((1814<<4)|5,fakeUsart.BRR);
}

void test_Usart_usartSetBaudRate_16oversamp_with_uart1(void){
    setUsartOversamplingMode(usart1,OVER_16);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,9600);
    TEST_ASSERT_EQUAL((293<<4),fakeUsart.BRR);
}

void test_Usart_usartSetBaudRate_16oversamp_with_5500baud_uart1(void){
    setUsartOversamplingMode(usart1,OVER_16);
    getPCLK2Clock_ExpectAndReturn(0x2AEA540);
    usartSetBaudRate(usart1,5500);
    TEST_ASSERT_EQUAL((511<<4)+(6<<0),fakeUsart.BRR);
}

//Enable Interrupt
void test_Usart_usartEnableInterrupt_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
}
void test_Usart_usartEnableInterrupt_IDLE_INTERRUPT(void){
    usartEnableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<4,fakeUsart.CR1);
}
void test_Usart_usartEnableInterrupt_READ_DATA_NOT_EMPTY(void){
    usartEnableInterrupt(usart1,READ_DATA_NOT_EMPTY);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.CR1);
}
void test_Usart_usartEnableInterrupt_TRANS_COMPLETE(void){
    usartEnableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(1<<6,fakeUsart.CR1);
}
void test_Usart_usartEnableInterrupt_TRANS_DATA_EMPTY(void){
    usartEnableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(1<<7,fakeUsart.CR1);
}
void test_Usart_usartEnableInterrupt_PARITY_ERROR(void){
    usartEnableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(1<<8,fakeUsart.CR1);
}
void test_Usart_usartEnableInterrupt_CTS_INTERRUPT(void){
    usartEnableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.CR3);
}
void test_Usart_usartEnableInterrupt_ERROR_INTERRUPT(void){
    usartEnableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(1,fakeUsart.CR3);
}
void test_Usart_usartDisableInterrupt_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
}
void test_Usart_usartDisableInterrupt_IDLE_INTERRUPT(void){
    usartEnableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<4,fakeUsart.CR1);
    usartDisableInterrupt(usart1,IDLE_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}
void test_Usart_usartDisableInterrupt_READ_DATA_NOT_EMPTY(void){
    usartEnableInterrupt(usart1,READ_DATA_NOT_EMPTY);
    TEST_ASSERT_EQUAL(1<<5,fakeUsart.CR1);
    usartDisableInterrupt(usart1,READ_DATA_NOT_EMPTY);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}
void test_Usart_usartDisableInterrupt_TRANS_COMPLETE(void){
    usartEnableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(1<<6,fakeUsart.CR1);
    usartDisableInterrupt(usart1,TRANS_COMPLETE);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}
void test_Usart_usartDisableInterrupt_TRANS_DATA_EMPTY(void){
    usartEnableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(1<<7,fakeUsart.CR1);
    usartDisableInterrupt(usart1,TRANS_DATA_EMPTY);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}
void test_Usart_usartDisableInterrupt_PARITY_ERROR(void){
    usartEnableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(1<<8,fakeUsart.CR1);
    usartDisableInterrupt(usart1,PARITY_ERROR);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}
void test_Usart_usartDisableInterrupt_CTS_INTERRUPT(void){
    usartEnableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.CR3);
    usartDisableInterrupt(usart1,CTS_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR3);
}
void test_Usart_usartDisableInterrupt_ERROR_INTERRUPT(void){
    usartEnableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(1,fakeUsart.CR3);
    usartDisableInterrupt(usart1,ERROR_INTERRUPT);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR3);
}

void test_Usart_setUsartOversamplingMode_SAMP_16(void){
    setUsartOversamplingMode(usart1,OVER_16);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_setUsartOversamplingMode_SAMP_8(void){
    setUsartOversamplingMode(usart1,OVER_8);
    TEST_ASSERT_EQUAL(1<<15,fakeUsart.CR1);
}

void test_Usart_setUsartOversamplingMode_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    setUsartOversamplingMode(NULL,OVER_8);
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
    TEST_IGNORE_MESSAGE("havent implement");
    TEST_ASSERT_EQUAL(0,usartGetOversamplingMode(NULL));
}

void test_Usart_enableUsart(void){
    enableUsart(usart1);
    TEST_ASSERT_EQUAL(1<<13,fakeUsart.CR1);
}

void test_Usart_enableUsart_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    enableUsart(NULL);
}

void test_Usart_disableUsart(void){
    enableUsart(usart1);
    TEST_ASSERT_EQUAL(1<<13,fakeUsart.CR1);
    disableUsart(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_disableUsart_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    disableUsart(NULL);
}

void test_Usart_usartEnableReceiver(void){
    usartEnableReceiver(usart1);
    TEST_ASSERT_EQUAL(1<<2,fakeUsart.CR1);
}

void test_Usart_usartEnableReceiver_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartEnableReceiver(NULL);
}

void test_Usart_usartDisableReceiver(void){
    usartEnableReceiver(usart1);
    TEST_ASSERT_EQUAL(1<<2,fakeUsart.CR1);
    usartDisableReceiver(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_usartDisableReceiver_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartDisableReceiver(NULL);
}

void test_Usart_usartEnableTransmission(void){
    usartEnableTransmission(usart1);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.CR1);
}

void test_Usart_usartEnableTransmission_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartEnableTransmission(NULL);
}

void test_Usart_usartDisableTransmission(void){
    usartEnableTransmission(usart1);
    TEST_ASSERT_EQUAL(1<<3,fakeUsart.CR1);
    usartDisableTransmission(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_usartDisableTransmission_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartDisableReceiver(NULL);
}

void test_Usart_usartEnableParityControl(void){
    usartEnableParityControl(usart1);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.CR1);
}

void test_Usart_usartEnableParityControl_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartEnableParityControl(NULL);
}

void test_Usart_usartDisableParityControl(void){
    usartEnableParityControl(usart1);
    TEST_ASSERT_EQUAL(1<<10,fakeUsart.CR1);
    usartDisableParityControl(usart1);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_usartDisableParityControl_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    usartDisableParityControl(NULL);
}

void test_Usart_setUsartWordLength(void){
    setUsartWordLength(usart1,DATA_9_BITS);
    TEST_ASSERT_EQUAL(1<<12,fakeUsart.CR1);
    setUsartWordLength(usart1,DATA_8_BITS);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_setUsartWordLength_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    setUsartWordLength(NULL,DATA_8_BITS);
}

void test_Usart_setUsartWakeupMode(void){
    setUsartWakeupMode(usart1,ADDRESS_MARK);
    TEST_ASSERT_EQUAL(1<<11,fakeUsart.CR1);
    setUsartWakeupMode(usart1,IDLE_LINE);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_setUsartWakeupMode_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    setUsartWakeupMode(NULL,IDLE_LINE);
}

void test_Usart_setUsartParityMode(void){
    setUsartParityMode(usart1,ODD_PARITY);
    TEST_ASSERT_EQUAL(1<<9,fakeUsart.CR1);
    setUsartParityMode(usart1,EVEN_PARITY);
    TEST_ASSERT_EQUAL(0,fakeUsart.CR1);
}

void test_Usart_setUsartParityMode_NULL_input(void){
    TEST_IGNORE_MESSAGE("havent implement");
    setUsartParityMode(NULL,ODD_PARITY);
}