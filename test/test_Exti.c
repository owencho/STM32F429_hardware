#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Exti.h"

/*
* EXTI GIPO MAPPING
* PIN_0 for PORT_A0 -> K0
* PIN_1 for PORT_A1 -> K1
* PIN_2 for PORT_A2 -> K2
* PIN_3 for PORT_A3 -> K3
* PIN_4 for PORT_A4 -> K4
* .
* .
* PIN_15 for PORT_A15 -> K15
* PIN_16 for PVD output
* PIN_17 for RTC Alarm/event
* PIN_18 for USB OTG FS Wakeup event
* PIN_19 for Ethernet Wakeup event
* PIN_20 for USB OTG HS (configured in FS) Wakeup event
* PIN_21 for RTC tamper and TimeStamp event
* PIN_22 for RTC Wakeup event
*/

ExtiRegs fakeExti;

void setUp(void){
    int i;
    char * ptr =(char*)&fakeExti;
    for(i =0; i< sizeof(ExtiRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getExtiBaseAddress(){
    return (uintptr_t)&fakeExti;
}
// exti must set pin as unmasked to enable Interrupt on certain pin number
// eg if user gonna set pin 0 on port A to enable Interrupt it must unmasked pin 0
// eg extiSetInterruptMaskRegister(exti,PIN_0,NOT_MASKED);
void test_Exti_extiSetInterruptMaskRegister_given_port0_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,PIN_0,NOT_MASKED);
    TEST_ASSERT_EQUAL(1,fakeExti.IMR);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,PIN_5,NOT_MASKED);
    TEST_ASSERT_EQUAL(1<<5,fakeExti.IMR);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_masked(void){
    extiSetInterruptMaskRegister(&fakeExti,PIN_5,NOT_MASKED);
    TEST_ASSERT_EQUAL(1<<5,fakeExti.IMR);
    extiSetInterruptMaskRegister(&fakeExti,PIN_5,MASKED);
    TEST_ASSERT_EQUAL(0,fakeExti.IMR);
}

void test_Exti_extiSetInterruptMaskRegister_given_loc_null_unmasked(void){
    extiSetInterruptMaskRegister(NULL,PIN_0,NOT_MASKED);
    TEST_ASSERT_EQUAL(0,fakeExti.IMR);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_port1_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,PIN_5,NOT_MASKED);
    extiSetInterruptMaskRegister(&fakeExti,PIN_6,NOT_MASKED);
    TEST_ASSERT_EQUAL((1<<5 | 1<<6 ),fakeExti.IMR);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory
void test_Exti_extiSetInterruptMaskRegister_given_pin_23_where_not_available_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,PIN_23,NOT_MASKED);
    TEST_ASSERT_EQUAL(0,fakeExti.IMR);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port0_rising(void){
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_0,RISING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.RTSR);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port0_rising_disabled(void){
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_0,RISING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.RTSR);
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_0,RISING_DISABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.RTSR);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_input_NULL(void){
    extiSetRisingTriggerInterrupt(NULL,PIN_5,RISING_ENABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.RTSR);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port5_port6_(void){
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_5,RISING_ENABLED);
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_6,RISING_ENABLED);
    TEST_ASSERT_EQUAL((1<<5 | 1<<6 ),fakeExti.RTSR);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory
void test_Exti_extiSetRisingTriggerInterrupt_given_pin_31_where_not_available_unmasked(void){
    extiSetRisingTriggerInterrupt(&fakeExti,PIN_31,RISING_ENABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.RTSR);
}

void test_Exti_extiSetFallingInterrupt_given_port0_falling(void){
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_0,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.FTSR);
}

void test_Exti_extiSetFallingInterrupt_given_port0_rising_disabled(void){
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_0,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.FTSR);
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_0,FALLING_DISABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.FTSR);
}

void test_Exti_extiSetFallingInterrupt_given_input_NULL(void){
    extiSetFallingTriggerInterrupt(NULL,PIN_5,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.FTSR);
}

void test_Exti_extiSetFallingInterrupt_given_port5_port6_(void){
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_6,FALLING_ENABLED);
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_7,FALLING_ENABLED);
    TEST_ASSERT_EQUAL((1<<6 | 1<<7 ),fakeExti.FTSR);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory
void test_Exti_extiSetFallingInterrupt_given_pin_25_where_not_available_unmasked(void){
    extiSetFallingTriggerInterrupt(&fakeExti,PIN_25,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.FTSR);
}

void test_Exti_extiSetSoftwareInterruptEvent_given_port5_(void){
    extiSetSoftwareInterruptEvent(&fakeExti,PIN_5);
    TEST_ASSERT_EQUAL((1<<5),fakeExti.SWIER);
}

void test_Exti_extiSetSoftwareInterruptEvent_given_port7(void){
    extiSetSoftwareInterruptEvent(&fakeExti,PIN_7);
    TEST_ASSERT_EQUAL((1<<7),fakeExti.SWIER);
}

void test_Exti_extiSetPendingRegister_given_port6_(void){
    extiSetPendingRegister(&fakeExti,PIN_6);
    TEST_ASSERT_EQUAL((1<<6),fakeExti.PR);
}

void test_Exti_extiSetPendingRegister_given_port11(void){
    extiSetPendingRegister(&fakeExti,PIN_11);
    TEST_ASSERT_EQUAL((1<<11),fakeExti.PR);
}

void test_Exti_extiReadPendingRegister_given_port11(void){
    extiSetPendingRegister(&fakeExti,PIN_11);
    TEST_ASSERT_EQUAL((1<<11),fakeExti.PR);
    TEST_ASSERT_EQUAL(1,extiReadPendingRegister(&fakeExti,PIN_11));
}
