#include "unity.h"
#include <stdint.h>
#include "Nvic.h"
#include "BaseAddress.h"
#include "Common.h"


NvicRegs fakeNvic;

void setUp(void){
    int i;
    char * ptr =(char*)&fakeNvic;
    for(i =0; i< sizeof(NvicRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getNvicBaseAddress(){
    return (uintptr_t)&fakeNvic;
}

void test_Nvic_0XFF_expect_same_value_assign_on_same_iser_array(void){
    nvic->ISER[2]=0xffaabb;
    TEST_ASSERT_EQUAL(0xffaabb,fakeNvic.ISER[2]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_75_expect_ISER_register_array2(void){
    nvicEnableInterrupt(75);
    TEST_ASSERT_EQUAL(1<<11,fakeNvic.ISER[2]);
}

void test_Nvic_nvicDisableInterrupt_given_interruptNum_75_expect_ICER_register_array2(void){
    nvicDisableInterrupt(73);
    TEST_ASSERT_EQUAL(1<<9,fakeNvic.ICER[2]);
}

void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_12_expect_ISPR_register_array0(void){
    nvicSetPendingInterrupt(12);
    TEST_ASSERT_EQUAL(1<<12,fakeNvic.ISPR[0]);
}

void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_32_expect_ICPR_register_array1(void){
    nvicClearPendingInterrupt(32);
    TEST_ASSERT_EQUAL(1,fakeNvic.ICPR[1]);
}

void test_Nvic_nvicIsInterruptActive_given_interruptNum_120_expect_IABR_register_array3(void){
    nvic->IABR[3]= 1<<24;
    TEST_ASSERT_EQUAL(1,nvicIsInterruptActive(120));
}

void test_Nvic_nvicSetInterruptPriority_given_interruptNum_210_expect_IPRx_register_array3(void){
    nvicSetInterruptPriority(210,5);
    TEST_ASSERT_EQUAL(5,fakeNvic.IPR[52]>>16);
}

void test_Nvic_nvicGetInterruptPriority_given_interruptNum_31_expect_IPRx_register_array(void){
    nvicSetInterruptPriority(31,200);
    TEST_ASSERT_EQUAL(200,nvicGetInterruptPriority(31));
}

void test_nvicSoftwareTriggerInterrupt_given_interruptNum_50_expect_STIR_register_array(void){
    nvicSoftwareTriggerInterrupt(50);
    TEST_ASSERT_EQUAL(50,fakeNvic.STIR);
}
