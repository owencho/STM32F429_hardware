#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Syscfg.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
#include "ExceptionTestSupport.h"
CEXCEPTION_T ex;

SyscfgRegs fakeSyscfg;
void setUp(void){
    int i;
    char * ptr =(char*)&fakeSyscfg;
    for(i =0; i< sizeof(SyscfgRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getSyscfgBaseAddress(){
    return (uintptr_t)&fakeSyscfg;
}

void test_Syscfg_syscfgExternalInterruptConfig_NULL(void){
    Try{
        syscfgExternalInterruptConfig(NULL,EXTI_0,PORT_A);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Syscfg_syscfgExternalInterruptConfig_negative_extiPort(void){
    Try{
        syscfgExternalInterruptConfig(&fakeSyscfg,-1,PORT_A);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_INVALID_EXTI_PORT,ex->errorCode);
    }
}

void test_Syscfg_syscfgExternalInterruptConfig_pos_extiPort(void){
    Try{
        syscfgExternalInterruptConfig(&fakeSyscfg,16,PORT_A);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_INVALID_EXTI_PORT,ex->errorCode);
    }
}

void test_Syscfg_syscfgExternalInterruptConfig_negative_Port(void){
    Try{
        syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_0,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_INVALID_PORT,ex->errorCode);
    }
}

void test_Syscfg_syscfgExternalInterruptConfig_pos_Port(void){
    Try{
        syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_0,9);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_INVALID_PORT,ex->errorCode);
    }
}

void test_Syscfg_syscfgExternalInterruptConfig_portI_on_port12(void){
    Try{
        syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_12,PORT_I);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(SYSCFG_ERROR_CONFIG,ex->errorCode);
    }
}


void test_Syscfg_syscfgExternalInterruptConfig_PORTA_ON_EXTI0_INT(void){
    syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_0,PORT_A);
    TEST_ASSERT_EQUAL(0,fakeSyscfg.exticr[0]);
}

void test_Syscfg_syscfgExternalInterruptConfig_PORTF_ON_EXTI5_INT(void){
    syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_5,PORT_F);
    TEST_ASSERT_EQUAL(5<<4,fakeSyscfg.exticr[1]);
}

void test_Syscfg_syscfgExternalInterruptConfig_PORTF_ON_EXTI7_INT(void){
    syscfgExternalInterruptConfig(&fakeSyscfg,EXTI_7,PORT_E);
    TEST_ASSERT_EQUAL(PORT_E<<12,fakeSyscfg.exticr[1]);
}
