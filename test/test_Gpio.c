#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Gpio.h"

GpioRegs fakeGpio;

void setUp(void){
    int i;
    char * ptr =(char*)&fakeGpio;
    for(i =0; i< sizeof(GpioRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getGpioBaseAddress(){
    return (uintptr_t)&fakeGpio;
}
// LOW_SPEED,MEDIUM_SPEED,HIGH_SPEED,VERY_HI_SPEED
void test_Gpio_gpioSetPinSpeed_set_Pin0_LowSpeed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_0 ,LOW_SPEED);
    TEST_ASSERT_EQUAL(0,fakeGpio.OSPEEDR);
}

void test_Gpio_gpioSetPinSpeed_set_Pin0_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_0 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL(3 ,fakeGpio.OSPEEDR);
}

void test_Gpio_gpioSetPinSpeed_set_Pin5_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_5 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL(3 << 10,fakeGpio.OSPEEDR);
}

void test_Gpio_gpioSetPinSpeed_set_Pin5_Pin4_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_5 ,VERY_HI_SPEED);
    gpioSetPinSpeed(&fakeGpio , PIN_4 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL((3 << 10 | 3<< 8),fakeGpio.OSPEEDR);
}

void test_Gpio_gpioSetPinSpeed_set_Ptr_NULL(void){
    //gpioSetPinSpeed(NULL, PIN_0 ,LOW_SPEED);
    TEST_IGNORE_MESSAGE("havent implement");
    //TEST_ASSERT_EQUAL(0,fakeGpio.OSPEEDR);
}
//GPIO_IN,GPIO_OUT,GPIO_ALT,GPIO_ANALOG,
void test_Gpio_gpioSetMode_set_Pin0_input(void){
    gpioSetMode(&fakeGpio , PIN_0 ,GPIO_IN);
    TEST_ASSERT_EQUAL(0,fakeGpio.MODER);
}

void test_Gpio_gpioSetMode_set_Pin5_out(void){
    gpioSetMode(&fakeGpio , PIN_5 ,GPIO_OUT);
    TEST_ASSERT_EQUAL(1<<(5*2) ,fakeGpio.MODER);
}

void test_Gpio_gpioSetMode_set_Pin5_analog(void){
    gpioSetMode(&fakeGpio , PIN_3 ,GPIO_ANALOG);
    TEST_ASSERT_EQUAL(3<<(3*2) ,fakeGpio.MODER);
}

void test_Gpio_gpioSetMode_set_Pin6_ALT_mode(void){
    gpioSetMode(&fakeGpio , PIN_6 ,GPIO_ALT);
    TEST_ASSERT_EQUAL(2 << (6*2),fakeGpio.MODER);
}

void test_Gpio_gpioSetMode_set_Pin6_Pin5_IN_ALT_mode(void){
    gpioSetMode(&fakeGpio , PIN_6 ,GPIO_ALT);
    gpioSetMode(&fakeGpio , PIN_5 ,GPIO_OUT);
    TEST_ASSERT_EQUAL(2 << (12)|1<<(10),fakeGpio.MODER);
}

void test_Gpio_gpioSetMode_set_Ptr_NULL(void){
    //gpioSetMode(NULL, PIN_0 ,LOW_SPEED);
    TEST_IGNORE_MESSAGE("havent implement");
    //TEST_ASSERT_EQUAL(0,fakeGpio.OSPEEDR);
}
void test_Gpio_gpioWrite_value(void){
    gpioWrite(&fakeGpio , 0xff);
    TEST_ASSERT_EQUAL(0xff,fakeGpio.BSRR);
}

void test_Gpio_gpioWrite_set_Ptr_NULL(void){
    //gpioWrite(NULL, 123 );
    TEST_IGNORE_MESSAGE("havent implement");
}
void test_Gpio_gpioWriteBit_set_Pin0_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_0 ,1);
    TEST_ASSERT_EQUAL(1,fakeGpio.BSRR);
}

void test_Gpio_gpioWriteBit_set_Pin5_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_5 ,1);
    TEST_ASSERT_EQUAL(1<<5,fakeGpio.BSRR);
}

void test_Gpio_gpioWriteBit_set_Pin5_Pin9bit1(void){
    gpioWriteBit(&fakeGpio , PIN_5 ,1);
    gpioWriteBit(&fakeGpio , PIN_9 ,1);
    TEST_ASSERT_EQUAL(1<<5 | 1<<9,fakeGpio.BSRR);
}

void test_Gpio_gpioWriteBit_set_Pin6_bit0(void){
    gpioWriteBit(&fakeGpio , PIN_6 ,1);
    TEST_ASSERT_EQUAL(1<<6,fakeGpio.BSRR);
    gpioWriteBit(&fakeGpio , PIN_6 ,0);
    TEST_ASSERT_EQUAL(0,fakeGpio.BSRR);
}
void test_Gpio_gpioWriteBit_set_Ptr_NULL(void){
    //gpioWriteBit(NULL, 123 );
    TEST_IGNORE_MESSAGE("havent implement");
}
void test_Gpio_gpioReadBit_set_Pin0_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_0 ,1);
    TEST_ASSERT_EQUAL(1,fakeGpio.BSRR);
}

void test_Gpio_gpioReadBit_set_Pin5_bit1(void){
    fakeGpio.IDR = 1<<5;
    TEST_ASSERT_EQUAL(1, gpioReadBit(&fakeGpio , 5));
}

void test_Gpio_gpioReadBit_set_Pin6_bit0(void){
    fakeGpio.IDR = 0<<6;
    TEST_ASSERT_EQUAL(0, gpioReadBit(&fakeGpio , 6));
}

void test_Gpio_gpioReadBit_set_Ptr_NULL(void){
    //gpioReadBit(NULL, 123 );
    TEST_IGNORE_MESSAGE("havent implement");
}
void test_Gpio_gpioToggleBit_set_Pin1(void){
    gpioToggleBit(&fakeGpio ,PIN_1);
    TEST_ASSERT_EQUAL(1<<1,fakeGpio.ODR);
    gpioToggleBit(&fakeGpio ,PIN_1);
    TEST_ASSERT_EQUAL(0,fakeGpio.ODR);
}

void test_Gpio_gpioToggleBit_set_Ptr_NULL(void){
    //gpioToggleBit(NULL, 123 );
    TEST_IGNORE_MESSAGE("havent implement");
}
