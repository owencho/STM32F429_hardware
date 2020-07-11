#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Rcc.h"

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
