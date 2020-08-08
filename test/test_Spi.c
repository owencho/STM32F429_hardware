#include "unity.h"
#include <stdint.h>
#include "Spi.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include "ExceptionTestSupport.h"
#include "SpiMacro.h"

CEXCEPTION_T ex;
SpiRegs fakeSpi;
#define BASE_CONTROL_TEST (SPI_2_LINE_UNIDIRECTION|SPI_TRANSMIT_RECEIVE | \
                          SPI_SOFTWARE_SLAVE_M_ENABLED |SPI_ENABLE |  \
                          SPI_BAUD_FCLK_DIV8 |SPI_TX_EMPTY_INT_ENABLE )
void setUp(void){
    int i;
    char * ptr =(char*)&fakeSpi;
    for(i =0; i< sizeof(SpiRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

void test_spiSetControlRegister(void){
    spiSetControlRegister(&fakeSpi,BASE_CONTROL_TEST);
    TEST_ASSERT_EQUAL((0<<15)|(0<<10)|(1<<9)|(1<<6)|(2<<3),fakeSpi.cr1);
    TEST_ASSERT_EQUAL((1<<7),fakeSpi.cr2);
}

void test_spiSetControlRegister_with_extra_setting_SPI_TI_MODE(void){
    spiSetControlRegister(&fakeSpi,BASE_CONTROL_TEST|SPI_TI_MODE);
    TEST_ASSERT_EQUAL((0<<15)|(0<<10)|(1<<9)|(1<<6)|(2<<3),fakeSpi.cr1);
    TEST_ASSERT_EQUAL((1<<7)|(1<<4),fakeSpi.cr2);
}

void test_spiReadDataRegister(void){
    fakeSpi.dr = 0xFF;
    TEST_ASSERT_EQUAL(0xFF,spiReadDataRegister(&fakeSpi));
}

void test_spiWriteDataRegister(void){
    spiWriteDataRegister(&fakeSpi,0x1243);
    TEST_ASSERT_EQUAL(0x1243,fakeSpi.dr);
}

void test_spiReadFlag_1bit(void){
    fakeSpi.sr = (1<<0);
    TEST_ASSERT_EQUAL(1,spiReadFlag(&fakeSpi,SPI_RECEIVE_NOT_EMPTY));
}

void test_spiReadFlag_2bit(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_UNDERRUN);
    TEST_ASSERT_EQUAL(1,spiReadFlag(&fakeSpi,SPI_UNDERRUN));
}

void test_spiResetFlag(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_UNDERRUN);
    spiResetFlag(&fakeSpi,SPI_UNDERRUN);
    TEST_ASSERT_EQUAL(1,fakeSpi.sr);
}

void test_spiResetFlag_SPI_OVERRUN(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_OVERRUN);
    spiResetFlag(&fakeSpi,SPI_OVERRUN);
    TEST_ASSERT_EQUAL(1,fakeSpi.sr);
}
// no change as we only reset the sr with the bit that available to unset with software
void test_spiResetFlag_SPI_FRAME_FORMAT_ERROR(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_FRAME_FORMAT_ERROR);
    spiResetFlag(&fakeSpi,SPI_FRAME_FORMAT_ERROR);
    TEST_ASSERT_EQUAL((1<<0)| (1<<SPI_FRAME_FORMAT_ERROR),fakeSpi.sr);
}

void test_spiResetFlag_SPI_CRC_ERROR(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_CRC_ERROR);
    spiResetFlag(&fakeSpi,SPI_CRC_ERROR);
    TEST_ASSERT_EQUAL(1,fakeSpi.sr);
}

void test_spiResetFlag_SPI_MODE_FAULT(void){
    fakeSpi.sr = (1<<0)| (1<<SPI_MODE_FAULT);
    spiResetFlag(&fakeSpi,SPI_MODE_FAULT);
    TEST_ASSERT_EQUAL(1,fakeSpi.sr);
}

void test_spiReadCRCPolynomialRegister(void){
    fakeSpi.crcpr = 0x12FF;
    TEST_ASSERT_EQUAL(0x12FF,spiReadCRCPolynomialRegister(&fakeSpi));
}

void test_spiWriteCRCPolynomialRegister(void){
    spiWriteCRCPolynomialRegister(&fakeSpi,0x1553);
    TEST_ASSERT_EQUAL(0x1553,fakeSpi.crcpr);
}

void test_spiReadReceiveCRCRegister(void){
    fakeSpi.rxcrcr = 0x1FFF;
    TEST_ASSERT_EQUAL(0x1FFF,spiReadReceiveCRCRegister(&fakeSpi));
}

void test_spiReadTransmitCRCRegister(void){
    fakeSpi.txcrcr = 0x10FF;
    TEST_ASSERT_EQUAL(0x10FF,spiReadTransmitCRCRegister(&fakeSpi));
}
