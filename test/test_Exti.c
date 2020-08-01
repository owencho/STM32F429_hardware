#include "unity.h"
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
#include "Exti.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include "ExceptionTestSupport.h"
CEXCEPTION_T ex;
/*
* EXTI GIPO MAPPING
* 0 for PORT_A0 -> K0
* 1 for PORT_A1 -> K1
* 2 for PORT_A2 -> K2
* 3 for PORT_A3 -> K3
* 4 for PORT_A4 -> K4
* .
* .
* 15 for PORT_A15 -> K15
* 16 for PVD output
* 17 for RTC Alarm/event
* 18 for USB OTG FS Wakeup event
* 19 for Ethernet Wakeup event
* 20 for USB OTG HS (configured in FS) Wakeup event
* 21 for RTC tamper and TimeStamp event
* 22 for RTC Wakeup event
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
// eg extiSetInterruptMaskRegister(exti,0,NOT_MASKED);
void test_Exti_extiSetInterruptMaskRegister_given_port0_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,0,NOT_MASKED);
    TEST_ASSERT_EQUAL(1,fakeExti.imr);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,5,NOT_MASKED);
    TEST_ASSERT_EQUAL(1<<5,fakeExti.imr);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_masked(void){
    extiSetInterruptMaskRegister(&fakeExti,5,NOT_MASKED);
    TEST_ASSERT_EQUAL(1<<5,fakeExti.imr);
    extiSetInterruptMaskRegister(&fakeExti,5,MASKED);
    TEST_ASSERT_EQUAL(0,fakeExti.imr);
}

void test_Exti_extiSetInterruptMaskRegister_given_port5_port1_unmasked(void){
    extiSetInterruptMaskRegister(&fakeExti,5,NOT_MASKED);
    extiSetInterruptMaskRegister(&fakeExti,6,NOT_MASKED);
    TEST_ASSERT_EQUAL((1<<5 | 1<<6 ),fakeExti.imr);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory
void test_Exti_extiSetInterruptMaskRegister_given_23_where_not_available_unmasked(void){
    Try{
        extiSetInterruptMaskRegister(&fakeExti,23,NOT_MASKED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiSetInterruptMaskRegister_input_NULL(void){
    Try{
        extiSetInterruptMaskRegister(NULL,23,NOT_MASKED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiSetInterruptMaskRegister_neg_masked_mode(void){
    Try{
        extiSetInterruptMaskRegister(&fakeExti,20,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_MASKED_MODE,ex->errorCode);
    }
}

void test_Exti_extiSetInterruptMaskRegister_positive_but_weird_masked_mode(void){
    Try{
        extiSetInterruptMaskRegister(&fakeExti,20,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_MASKED_MODE,ex->errorCode);
    }
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port0_rising(void){
    extiSetRisingTriggerInterrupt(&fakeExti,0,RISING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.rtsr);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port0_rising_disabled(void){
    extiSetRisingTriggerInterrupt(&fakeExti,0,RISING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.rtsr);
    extiSetRisingTriggerInterrupt(&fakeExti,0,RISING_DISABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.rtsr);
}

void test_Exti_extiSetRisingTriggerInterrupt_given_port5_port6_(void){
    extiSetRisingTriggerInterrupt(&fakeExti,5,RISING_ENABLED);
    extiSetRisingTriggerInterrupt(&fakeExti,6,RISING_ENABLED);
    TEST_ASSERT_EQUAL((1<<5 | 1<<6 ),fakeExti.rtsr);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory
void test_Exti_extiSetRisingTriggerInterrupt_given_23_where_not_available_unmasked(void){
    Try{
        extiSetRisingTriggerInterrupt(&fakeExti,31,RISING_ENABLED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiSetRisingTriggerInterrupt_input_NULL(void){
    Try{
        extiSetRisingTriggerInterrupt(NULL,23,RISING_ENABLED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiSetRisingTriggerInterrupt_neg_masked_mode(void){
    Try{
        extiSetRisingTriggerInterrupt(&fakeExti,20,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_RISING_TRIGGER_STATUS,ex->errorCode);
    }
}

void test_Exti_extiSetRisingTriggerInterrupt_positive_but_weird_masked_mode(void){
    Try{
        extiSetRisingTriggerInterrupt(&fakeExti,20,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_RISING_TRIGGER_STATUS,ex->errorCode);
    }
}

void test_Exti_extiSetFallingInterrupt_given_port0_falling(void){
    extiSetFallingTriggerInterrupt(&fakeExti,0,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.ftsr);
}

void test_Exti_extiSetFallingInterrupt_given_port0_rising_disabled(void){
    extiSetFallingTriggerInterrupt(&fakeExti,0,FALLING_ENABLED);
    TEST_ASSERT_EQUAL(1,fakeExti.ftsr);
    extiSetFallingTriggerInterrupt(&fakeExti,0,FALLING_DISABLED);
    TEST_ASSERT_EQUAL(0,fakeExti.ftsr);
}

void test_Exti_extiSetFallingInterrupt_given_port5_port6_(void){
    extiSetFallingTriggerInterrupt(&fakeExti,6,FALLING_ENABLED);
    extiSetFallingTriggerInterrupt(&fakeExti,7,FALLING_ENABLED);
    TEST_ASSERT_EQUAL((1<<6 | 1<<7 ),fakeExti.ftsr);
}
// this is tested where it only available from pin 0 - 22 ,
//where pin 23 onward is reserved memory

void test_Exti_extiSetFallingTriggerInterrupt_given_23_where_not_available_unmasked(void){
    Try{
        extiSetFallingTriggerInterrupt(&fakeExti,25,FALLING_ENABLED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiSetFallingTriggerInterrupt_input_NULL(void){
    Try{
        extiSetFallingTriggerInterrupt(NULL,23,FALLING_ENABLED);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiSetFallingTriggerInterrupt_neg_masked_mode(void){
    Try{
        extiSetFallingTriggerInterrupt(&fakeExti,20,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_FALLING_TRIGGER_STATUS,ex->errorCode);
    }
}

void test_Exti_extiSetFallingTriggerInterrupt_positive_but_weird_masked_mode(void){
    Try{
        extiSetFallingTriggerInterrupt(&fakeExti,20,2);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_FALLING_TRIGGER_STATUS,ex->errorCode);
    }
}

void test_Exti_extiSetSoftwareInterruptEvent_given_port5_(void){
    extiSetSoftwareInterruptEvent(&fakeExti,5);
    TEST_ASSERT_EQUAL((1<<5),fakeExti.swier);
}

void test_Exti_extiSetSoftwareInterruptEvent_given_port7(void){
    extiSetSoftwareInterruptEvent(&fakeExti,7);
    TEST_ASSERT_EQUAL((1<<7),fakeExti.swier);
}

void test_Exti_extiSetSoftwareInterruptEvent_input_NULL(void){
    Try{
        extiSetSoftwareInterruptEvent(NULL,7);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiSetSoftwareInterruptEvent_neg_masked_mode(void){
    Try{
        extiSetSoftwareInterruptEvent(&fakeExti,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiSetSoftwareInterruptEvent_positive_masked_mode(void){
    Try{
        extiSetSoftwareInterruptEvent(&fakeExti,23);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}


void test_Exti_extiSetPendingRegister_given_port6_(void){
    extiSetPendingRegister(&fakeExti,6);
    TEST_ASSERT_EQUAL((1<<6),fakeExti.pr);
}

void test_Exti_extiSetPendingRegister_given_port11(void){
    extiSetPendingRegister(&fakeExti,11);
    TEST_ASSERT_EQUAL((1<<11),fakeExti.pr);
}
void test_Exti_extiSetPendingRegister_input_NULL(void){
    Try{
        extiSetPendingRegister(NULL,7);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiSetPendingRegister_neg_masked_mode(void){
    Try{
        extiSetPendingRegister(&fakeExti,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiSetPendingRegister_positive_masked_mode(void){
    Try{
        extiSetPendingRegister(&fakeExti,23);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiReadPendingRegister_given_port11(void){
    extiSetPendingRegister(&fakeExti,11);
    TEST_ASSERT_EQUAL((1<<11),fakeExti.pr);
    TEST_ASSERT_EQUAL(1,extiReadPendingRegister(&fakeExti,11));
}

void test_Exti_extiReadPendingRegister_input_NULL(void){
    Try{
        extiReadPendingRegister(NULL,7);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Exti_extiReadPendingRegister_neg_masked_mode(void){
    Try{
        extiReadPendingRegister(&fakeExti,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}

void test_Exti_extiReadPendingRegister_positive_masked_mode(void){
    Try{
        extiReadPendingRegister(&fakeExti,23);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(EXTI_INVALID_PIN,ex->errorCode);
    }
}
