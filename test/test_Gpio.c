#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Gpio.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
CEXCEPTION_T ex;
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
    TEST_ASSERT_EQUAL(0,fakeGpio.ospeedr);
}

void test_Gpio_gpioSetPinSpeed_set_Pin0_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_0 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL(3 ,fakeGpio.ospeedr);
}

void test_Gpio_gpioSetPinSpeed_set_Pin5_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_5 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL(3 << 10,fakeGpio.ospeedr);
}

void test_Gpio_gpioSetPinSpeed_set_Pin5_Pin4_very_high_Speed(void){
    gpioSetPinSpeed(&fakeGpio , PIN_5 ,VERY_HI_SPEED);
    gpioSetPinSpeed(&fakeGpio , PIN_4 ,VERY_HI_SPEED);
    TEST_ASSERT_EQUAL((3 << 10 | 3<< 8),fakeGpio.ospeedr);
}

void test_Gpio_gpioSetPinSpeed_set_Ptr_NULL(void){
    Try{
        gpioSetPinSpeed(NULL, PIN_0 ,LOW_SPEED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioSetPinSpeed_neg_pin(void){
    Try{
        gpioSetPinSpeed(&fakeGpio, -1 ,LOW_SPEED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetPinSpeed_larger_pin(void){
    Try{
        gpioSetPinSpeed(&fakeGpio, 17 ,LOW_SPEED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetPinSpeed_invalid_neg_speed(void){
    Try{
        gpioSetPinSpeed(&fakeGpio, 0 ,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_SPEED_MODE,ex->errorCode);
    }
}

void test_Gpio_gpioSetPinSpeed_invalid_speed(void){
    Try{
        gpioSetPinSpeed(&fakeGpio, 0 ,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_SPEED_MODE,ex->errorCode);
    }
}
//GPIO_IN,GPIO_OUT,GPIO_ALT,GPIO_ANALOG,
void test_Gpio_gpioSetMode_set_Pin0_input(void){
    gpioSetMode(&fakeGpio , PIN_0 ,GPIO_IN);
    TEST_ASSERT_EQUAL(0,fakeGpio.moder);
}

void test_Gpio_gpioSetMode_set_Pin5_out(void){
    gpioSetMode(&fakeGpio , PIN_5 ,GPIO_OUT);
    TEST_ASSERT_EQUAL(1<<(5*2) ,fakeGpio.moder);
}

void test_Gpio_gpioSetMode_set_Pin5_analog(void){
    gpioSetMode(&fakeGpio , PIN_3 ,GPIO_ANALOG);
    TEST_ASSERT_EQUAL(3<<(3*2) ,fakeGpio.moder);
}

void test_Gpio_gpioSetMode_set_Pin6_ALT_mode(void){
    gpioSetMode(&fakeGpio , PIN_6 ,GPIO_ALT);
    TEST_ASSERT_EQUAL(2 << (6*2),fakeGpio.moder);
}

void test_Gpio_gpioSetMode_set_Pin6_Pin5_IN_ALT_mode(void){
    gpioSetMode(&fakeGpio , PIN_6 ,GPIO_ALT);
    gpioSetMode(&fakeGpio , PIN_5 ,GPIO_OUT);
    TEST_ASSERT_EQUAL(2 << (12)|1<<(10),fakeGpio.moder);
}
void test_Gpio_gpioSetMode_set_Ptr_NULL(void){
    Try{
        gpioSetMode(NULL, PIN_0 ,GPIO_ALT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioSetMode_neg_pin(void){
    Try{
        gpioSetMode(&fakeGpio, -1 ,GPIO_ALT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetMode_larger_pin(void){
    Try{
        gpioSetMode(&fakeGpio, 17 ,GPIO_ALT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetMode_invalid_neg_speed(void){
    Try{
        gpioSetMode(&fakeGpio, 0 ,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN_MODE,ex->errorCode);
    }
}

void test_Gpio_gpioSetMode_invalid_speed(void){
    Try{
        gpioSetMode(&fakeGpio, 0 ,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN_MODE,ex->errorCode);
    }
}

void test_Gpio_gpioWrite_value(void){
    gpioWrite(&fakeGpio , 0xff);
    TEST_ASSERT_EQUAL(0xff,fakeGpio.bsrr);
}

void test_Gpio_gpioWrite_set_Ptr_NULL(void){
    Try{
        gpioWrite(NULL, 123 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Gpio_gpioWriteBit_set_Pin0_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_0 ,1);
    TEST_ASSERT_EQUAL(1,fakeGpio.bsrr);
}

void test_Gpio_gpioWriteBit_set_Pin5_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_5 ,1);
    TEST_ASSERT_EQUAL(1<<5,fakeGpio.bsrr);
}


void test_Gpio_gpioWriteBit_set_Pin6_bit0(void){
    gpioWriteBit(&fakeGpio , PIN_6 ,1);
    TEST_ASSERT_EQUAL(1<<6,fakeGpio.bsrr);
    gpioWriteBit(&fakeGpio , PIN_6 ,0);
    TEST_ASSERT_EQUAL(1<<22,fakeGpio.bsrr);
}
void test_Gpio_gpioWriteBit_set_Ptr_NULL(void){
    Try{
        gpioWriteBit(NULL , PIN_6 ,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioWriteBit_set_bitNumber_larger_than15(void){
    Try{
        gpioWriteBit(&fakeGpio , 16 ,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioWriteBit_set_bitNumber_smaller_than0(void){
    Try{
        gpioWriteBit(&fakeGpio , -1 ,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioWriteBit_set_value_neg1(void){
    Try{
        gpioWriteBit(&fakeGpio , PIN_6 ,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_VALUE,ex->errorCode);
    }
}

void test_Gpio_gpioWriteBit_set_value_2(void){
    Try{
        gpioWriteBit(&fakeGpio , PIN_6 ,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_VALUE,ex->errorCode);
    }
}

void test_Gpio_gpioReadBit_set_Pin0_bit1(void){
    gpioWriteBit(&fakeGpio , PIN_0 ,1);
    TEST_ASSERT_EQUAL(1,fakeGpio.bsrr);
}

void test_Gpio_gpioReadBit_set_Pin5_bit1(void){
    fakeGpio.idr = 1<<5;
    TEST_ASSERT_EQUAL(1, gpioReadBit(&fakeGpio , 5));
}

void test_Gpio_gpioReadBit_set_Pin6_bit0(void){
    fakeGpio.idr = 0<<6;
    TEST_ASSERT_EQUAL(0, gpioReadBit(&fakeGpio , 6));
}
void test_Gpio_gpioReadBit_set_Ptr_NULL(void){
    Try{
        gpioReadBit(NULL, 1 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioReadBit_set_bit_NUM_larger_15(void){
    Try{
        gpioReadBit(&fakeGpio, 16 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioReadBit_set_bit_NUM_smaller_0(void){
    Try{
        gpioReadBit(&fakeGpio, -1 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioToggleBit_set_Pin1(void){
    gpioToggleBit(&fakeGpio ,PIN_1);
    TEST_ASSERT_EQUAL(1<<1,fakeGpio.odr);
    gpioToggleBit(&fakeGpio ,PIN_1);
    TEST_ASSERT_EQUAL(0,fakeGpio.odr);
}

void test_Gpio_gpioToggleBit_set_Ptr_NULL(void){
    Try{
        gpioToggleBit(NULL, 1 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioToggleBit_set_bit_NUM_larger_15(void){
    Try{
        gpioToggleBit(&fakeGpio, 16 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioToggleBit_set_bit_NUM_smaller_0(void){
    Try{
        gpioToggleBit(&fakeGpio, -1 );
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_BIT_NUM,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_set_Ptr_NULL(void){
    Try{
        gpioSetAlternateFunction(NULL, PIN_0 ,AF0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_neg_pin(void){
    Try{
        gpioSetAlternateFunction(&fakeGpio, -1 ,AF0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_larger_pin(void){
    Try{
        gpioSetAlternateFunction(&fakeGpio, 17 ,AF0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_PIN,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_invalid_neg_alt_function(void){
    Try{
        gpioSetAlternateFunction(&fakeGpio, 0 ,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_ALT_FUNCTION,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_invalid_alt_function(void){
    Try{
        gpioSetAlternateFunction(&fakeGpio, 0 ,17);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(GPIO_INVALID_ALT_FUNCTION,ex->errorCode);
    }
}

void test_Gpio_gpioSetAlternateFunction_set_Pin0_AF3(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_0,AF3);
    TEST_ASSERT_EQUAL(3,fakeGpio.afrl);
}

void test_Gpio_gpioSetAlternateFunction_set_Pin2_AF4(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_2,AF4);
    TEST_ASSERT_EQUAL(4<<(2*4),fakeGpio.afrl);
}

void test_Gpio_gpioSetAlternateFunction_set_Pin4_AF15(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_4,AF15);
    TEST_ASSERT_EQUAL(15<<(4*4),fakeGpio.afrl);
}


void test_Gpio_gpioSetAlternateFunction_set_Pin7_AF15(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_7,AF15);
    TEST_ASSERT_EQUAL_INT32(15<<(7*4),fakeGpio.afrl);
}

void test_Gpio_gpioSetAlternateFunction_set_Pin8_AF11(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_8,AF11);
    TEST_ASSERT_EQUAL_INT32(11,fakeGpio.afrh);
}

void test_Gpio_gpioSetAlternateFunction_set_Pin10_AF5(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_10,AF5);
    TEST_ASSERT_EQUAL_INT32(5<<(2*4),fakeGpio.afrh);
}

void test_Gpio_gpioSetAlternateFunction_set_Pin15_AF5(void){
    gpioSetAlternateFunction(&fakeGpio ,PIN_15,AF5);
    TEST_ASSERT_EQUAL_INT32(5<<(7*4),fakeGpio.afrh);
}
