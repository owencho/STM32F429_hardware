#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Rcc.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include "ExceptionTestSupport.h"
CEXCEPTION_T ex;

RccRegs fakeRcc;
void setUp(void){
    int i;
    char * ptr =(char*)&fakeRcc;
    for(i =0; i< sizeof(RccRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getRCCBaseAddress(){
    return (uintptr_t)&fakeRcc;
}

void test_enableGpioG(void){
   enableGpioG();
   TEST_ASSERT_EQUAL(1<<6,fakeRcc.ahb1enr);
   TEST_ASSERT_EQUAL(0<<6,fakeRcc.ahb1rstr);
}

void test_disableGpioG(void){
   enableGpioG();
   TEST_ASSERT_EQUAL(1<<6,fakeRcc.ahb1enr);
   TEST_ASSERT_EQUAL(0<<6,fakeRcc.ahb1rstr);
   disableGpioG();
   TEST_ASSERT_EQUAL(0<<6,fakeRcc.ahb1enr);
   TEST_ASSERT_EQUAL(1<<6,fakeRcc.ahb1rstr);
}

void test_enableGpioA(void){
   enableGpioA();
   TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1enr);
   TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
}

void test_disableGpioA(void){
    enableGpioA();
    TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0<<0,fakeRcc.ahb1rstr);
    disableGpioA();
    TEST_ASSERT_EQUAL(0<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1rstr);
}

void test_enableGpioAandG(void){
    enableGpioA();
    enableGpioG();
    TEST_ASSERT_EQUAL(1<<6|1<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
}

void test_disableGpioAandG(void){
    disableGpioA();
    disableGpioG();
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(1<<6|1<<0,fakeRcc.ahb1rstr);
}

void test_enableUART4(void){
    enableUART4();
    TEST_ASSERT_EQUAL(1<<19,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL(0<<19,fakeRcc.apb1rstr);
}

void test_disableUART4(void){
    enableUART4();
    TEST_ASSERT_EQUAL(1<<19,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL(0<<19,fakeRcc.apb1rstr);
    disableUART4();
    TEST_ASSERT_EQUAL(0<<19,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL(1<<19,fakeRcc.apb1rstr);
}

void test_enableUART8(void){
    enableUART8();
    TEST_ASSERT_EQUAL_INT32(1<<31,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<31,fakeRcc.apb1rstr);
}

void test_disableUART8(void){
    enableUART8();
    TEST_ASSERT_EQUAL_INT32(1<<31,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<31,fakeRcc.apb1rstr);
    disableUART8();
    TEST_ASSERT_EQUAL_INT32(0<<31,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(1<<31,fakeRcc.apb1rstr);
}

void test_enableUSART1(void){
    enableUSART1();
    TEST_ASSERT_EQUAL_INT32(1<<4,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<4,fakeRcc.apb2rstr);
}

void test_disableUSART1(void){
    enableUSART1();
    TEST_ASSERT_EQUAL_INT32(1<<4,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<4,fakeRcc.apb2rstr);
    disableUSART1();
    TEST_ASSERT_EQUAL_INT32(0<<4,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(1<<4,fakeRcc.apb2rstr);
}

void test_enableUSART6(void){
    enableUSART6();
    TEST_ASSERT_EQUAL_INT32(1<<5,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<5,fakeRcc.apb2rstr);
}

void test_disableUSART6(void){
    enableUSART6();
    TEST_ASSERT_EQUAL_INT32(1<<5,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<5,fakeRcc.apb2rstr);
    disableUSART6();
    TEST_ASSERT_EQUAL_INT32(0<<5,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(1<<5,fakeRcc.apb2rstr);
}

void test_enableUART5(void){
     enableUART5();
     TEST_ASSERT_EQUAL_INT32(1<<20,fakeRcc.apb1enr);
     TEST_ASSERT_EQUAL_INT32(0<<20,fakeRcc.apb1rstr);
}

void test_disableUART5(void){
    enableUART5();
    TEST_ASSERT_EQUAL_INT32(1<<20,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<20,fakeRcc.apb1rstr);
    disableUART5();
    TEST_ASSERT_EQUAL_INT32(0<<20,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(1<<20,fakeRcc.apb1rstr);
}

void test_enableGpio_PORT_A(void){
    enableGpio(PORT_A);
    TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
}

void test_enableGpio_PORT_K(void){
    enableGpio(PORT_K);
    TEST_ASSERT_EQUAL(1<<10,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
}

void test_enableGpio_neg_value(void){
    Try{
        enableGpio(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(RCC_INVALID_PORTNAME,ex->errorCode);
    }
}

void test_enableGpio_invalid_gpio(void){
    Try{
        enableGpio(11);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(RCC_INVALID_PORTNAME,ex->errorCode);
    }
}

void test_disableGpio_PORT_A(void){
    enableGpio(PORT_A);
    TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
    disableGpio(PORT_A);
    TEST_ASSERT_EQUAL(0<<0,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(1<<0,fakeRcc.ahb1rstr);
}

void test_disableGpio_PORT_K(void){
    enableGpio(PORT_K);
    TEST_ASSERT_EQUAL(1<<10,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(0,fakeRcc.ahb1rstr);
    disableGpio(PORT_K);
    TEST_ASSERT_EQUAL(0<<10,fakeRcc.ahb1enr);
    TEST_ASSERT_EQUAL(1<<10,fakeRcc.ahb1rstr);
}

void test_disableGpio_neg_value(void){
    Try{
        disableGpio(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(RCC_INVALID_PORTNAME,ex->errorCode);
    }
}

void test_disableGpio_invalid_gpio(void){
    Try{
        disableGpio(11);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(RCC_INVALID_PORTNAME,ex->errorCode);
    }
}

void test_enableTimer4(void){
     enableTimer4();
     TEST_ASSERT_EQUAL_INT32(1<<2,fakeRcc.apb1enr);
     TEST_ASSERT_EQUAL_INT32(0<<2,fakeRcc.apb1rstr);
}

void test_disableTimer4(void){
    enableTimer4();
    TEST_ASSERT_EQUAL_INT32(1<<2,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<2,fakeRcc.apb1rstr);
    disableTimer4();
    TEST_ASSERT_EQUAL_INT32(0<<2,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(1<<2,fakeRcc.apb1rstr);
}

void test_enableSpi1(void){
     enableSpi1();
     TEST_ASSERT_EQUAL_INT32(1<<12,fakeRcc.apb2enr);
     TEST_ASSERT_EQUAL_INT32(0<<12,fakeRcc.apb2rstr);
}

void test_disableSpi1(void){
    enableSpi1();
    TEST_ASSERT_EQUAL_INT32(1<<12,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<12,fakeRcc.apb2rstr);
    disableSpi1();
    TEST_ASSERT_EQUAL_INT32(0<<12,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(1<<12,fakeRcc.apb2rstr);
}

void test_enableSpi2(void){
     enableSpi2();
     TEST_ASSERT_EQUAL_INT32(1<<14,fakeRcc.apb1enr);
     TEST_ASSERT_EQUAL_INT32(0<<14,fakeRcc.apb1rstr);
}

void test_disableSpi2(void){
    enableSpi2();
    TEST_ASSERT_EQUAL_INT32(1<<14,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<14,fakeRcc.apb1rstr);
    disableSpi2();
    TEST_ASSERT_EQUAL_INT32(0<<14,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(1<<14,fakeRcc.apb1rstr);
}

void test_enableSpi3(void){
     enableSpi3();
     TEST_ASSERT_EQUAL_INT32(1<<15,fakeRcc.apb1enr);
     TEST_ASSERT_EQUAL_INT32(0<<15,fakeRcc.apb1rstr);
}

void test_disableSpi3(void){
    enableSpi3();
    TEST_ASSERT_EQUAL_INT32(1<<15,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(0<<15,fakeRcc.apb1rstr);
    disableSpi3();
    TEST_ASSERT_EQUAL_INT32(0<<15,fakeRcc.apb1enr);
    TEST_ASSERT_EQUAL_INT32(1<<15,fakeRcc.apb1rstr);
}

void test_enableSpi4_5(void){
     enableSpi4_5();
     TEST_ASSERT_EQUAL_INT32(1<<13,fakeRcc.apb2enr);
     TEST_ASSERT_EQUAL_INT32(0<<13,fakeRcc.apb2rstr);
}

void test_disableSpi4_5(void){
    enableSpi4_5();
    TEST_ASSERT_EQUAL_INT32(1<<13,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(0<<13,fakeRcc.apb2rstr);
    disableSpi4_5();
    TEST_ASSERT_EQUAL_INT32(0<<13,fakeRcc.apb2enr);
    TEST_ASSERT_EQUAL_INT32(1<<13,fakeRcc.apb2rstr);
}
