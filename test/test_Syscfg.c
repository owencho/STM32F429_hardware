#include "unity.h"

#include "Syscfg.h"

void setUp(void){}

void tearDown(void){}

void test_syscfgLoc_0XFF_expect_same_value_assign_on_same_iser_array(void){
    nvic->ISER[2]=0xffaabb;
    TEST_ASSERT_EQUAL(0xffaabb,fakeNvic.ISER[2]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_75_expect_ISER_register_array2(void){
    nvicEnableInterrupt(75);
    TEST_ASSERT_EQUAL(1<<11,fakeNvic.ISER[2]);
}
