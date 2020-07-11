#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Syscfg.h"

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
    syscfgExternalInterruptConfig(NULL,EXTI_0,PORT_A);
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
