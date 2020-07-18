#include "unity.h"
#include <stdint.h>
#include "Nvic.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
CEXCEPTION_T ex;

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
    nvic->iser[2]=0xffaabb;
    TEST_ASSERT_EQUAL(0xffaabb,fakeNvic.iser[2]);
}
void test_Nvic_nvicEnableInterrupt_given_interruptNum_10_expect_iser_register_array0(void){
    nvicEnableInterrupt(10);
    TEST_ASSERT_EQUAL(1<<10,fakeNvic.iser[0]);
}
void test_Nvic_nvicEnableInterrupt_given_interruptNum_33_expect_iser_register_array1(void){
    nvicEnableInterrupt(33);
    TEST_ASSERT_EQUAL(1<<1,fakeNvic.iser[1]);
}
void test_Nvic_nvicEnableInterrupt_given_interruptNum_70_expect_iser_register_array2(void){
    nvicEnableInterrupt(70);
    TEST_ASSERT_EQUAL(1<<6,fakeNvic.iser[2]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_169_expect_iser_register_array5(void){
    nvicEnableInterrupt(169);
    TEST_ASSERT_EQUAL(1<<9,fakeNvic.iser[5]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_193_expect_iser_register_array6(void){
    nvicEnableInterrupt(193);
    TEST_ASSERT_EQUAL(1<<1,fakeNvic.iser[6]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_235_expect_iser_register_array7(void){
    nvicEnableInterrupt(235);
    TEST_ASSERT_EQUAL(1<<11,fakeNvic.iser[7]);
}

void test_Nvic_nvicEnableInterrupt_given_interruptNum_235_and_236_expect_iser_register_array7(void){
    nvicEnableInterrupt(235);
    nvicEnableInterrupt(236);
    TEST_ASSERT_EQUAL((1<<11|1<<12),fakeNvic.iser[7]);
}


void test_Nvic_nvicEnableInterrupt_wrong_interrupt_number(void){
    Try{
        nvicEnableInterrupt(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicEnableInterrupt_neg_interrupt_number(void){
    Try{
        nvicEnableInterrupt(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}



void test_Nvic_nvicDisableInterrupt_given_interruptNum_11_expect_icer_register_array0(void){
    nvicDisableInterrupt(11);
    TEST_ASSERT_EQUAL(1<<11,fakeNvic.icer[0]);
}
void test_Nvic_nvicDisableInterrupt_given_interruptNum_33_expect_icer_register_array1(void){
    nvicDisableInterrupt(34);
    TEST_ASSERT_EQUAL(1<<2,fakeNvic.icer[1]);
}

void test_Nvic_nvicDisableInterrupt_given_interruptNum_75_expect_icer_register_array2(void){
    nvicDisableInterrupt(73);
    TEST_ASSERT_EQUAL(1<<9,fakeNvic.icer[2]);
}
void test_Nvic_nvicDisableInterrupt_given_interruptNum_123_expect_icer_register_array3(void){
    nvicDisableInterrupt(123);
    TEST_ASSERT_EQUAL(1<<27,fakeNvic.icer[3]);
}
void test_Nvic_nvicDisableInterrupt_given_interruptNum_128_expect_icer_register_array4(void){
    nvicDisableInterrupt(128);
    TEST_ASSERT_EQUAL(1,fakeNvic.icer[4]);
}
void test_Nvic_nvicDisableInterrupt_given_interruptNum_33_expect_iser_register_array7(void){
    nvicDisableInterrupt(235);
    TEST_ASSERT_EQUAL(1<<11,fakeNvic.icer[7]);
}

void test_Nvic_nvicDisableInterrupt_wrong_interrupt_number(void){
    Try{
        nvicDisableInterrupt(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicDisableInterrupt_neg_interrupt_number(void){
    Try{
        nvicDisableInterrupt(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}


void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_12_expect_ispr_register_array0(void){
    nvicSetPendingInterrupt(12);
    TEST_ASSERT_EQUAL(1<<12,fakeNvic.ispr[0]);
}
void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_33_expect_ispr_register_array1(void){
    nvicSetPendingInterrupt(34);
    TEST_ASSERT_EQUAL(1<<2,fakeNvic.ispr[1]);
}
void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_123_expect_ispr_register_array3(void){
    nvicSetPendingInterrupt(123);
    TEST_ASSERT_EQUAL(1<<27,fakeNvic.ispr[3]);
}

void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_168_expect_ispr_register_array5(void){
    nvicSetPendingInterrupt(168);
    TEST_ASSERT_EQUAL(1<<8,fakeNvic.ispr[5]);
}

void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_231_expect_ispr_register_array0(void){
    nvicSetPendingInterrupt(231);
    TEST_ASSERT_EQUAL(1<<7,fakeNvic.ispr[7]);
}


void test_Nvic_nvicSetPendingInterrupt_wrong_interrupt_number(void){
    Try{
        nvicSetPendingInterrupt(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicSetPendingInterrupt_neg_interrupt_number(void){
    Try{
        nvicSetPendingInterrupt(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}


void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_32_expect_icpr_register_array1(void){
    nvicClearPendingInterrupt(32);
    TEST_ASSERT_EQUAL(1,fakeNvic.icpr[1]);
}
void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_125_expect_icpr_register_array3(void){
    nvicClearPendingInterrupt(125);
    TEST_ASSERT_EQUAL(1<<29,fakeNvic.icpr[3]);
}

void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_32_expect_icpr_register_array7(void){
    nvicClearPendingInterrupt(229);
    TEST_ASSERT_EQUAL(1<<5,fakeNvic.icpr[7]);
}

void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_127_expect_icpr_register_array3(void){
    nvicClearPendingInterrupt(127);
    TEST_ASSERT_EQUAL_UINT32(1<<31,fakeNvic.icpr[3]);
}

void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_125_126_expect_icpr_register_array3(void){
    nvicClearPendingInterrupt(125);
    nvicClearPendingInterrupt(126);
    TEST_ASSERT_EQUAL((1<<29|1<<30),fakeNvic.icpr[3]);
}


void test_Nvic_nvicClearPendingInterrupt_wrong_interrupt_number(void){
    Try{
        nvicClearPendingInterrupt(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicClearPendingInterrupt_neg_interrupt_number(void){
    Try{
        nvicClearPendingInterrupt(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}



void test_Nvic_nvicIsInterruptActive_given_interruptNum_120_expect_iabr_register_array3(void){
    nvic->iabr[3]= 1<<24;
    TEST_ASSERT_EQUAL(1,nvicIsInterruptActive(120));
}

void test_Nvic_nvicIsInterruptActive_given_interruptNum_121_expect_iabr_register_array0(void){
    nvic->iabr[3]= 0;
    TEST_ASSERT_EQUAL(0,nvicIsInterruptActive(121));
}


void test_Nvic_nvicIsInterruptActive_wrong_interrupt_number(void){
    Try{
        nvicIsInterruptActive(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicIsInterruptActive_neg_interrupt_number(void){
    Try{
        nvicIsInterruptActive(-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicSetInterruptPriority_given_interruptNum_210_expect_iprx_register_array3(void){
    nvicSetInterruptPriority(210,5);
    TEST_ASSERT_EQUAL(5,fakeNvic.ipr[52]>>16);
}


void test_Nvic_nvicGetInterruptPriority_given_interruptNum_31_expect_iprx_register_array(void){
    nvicSetInterruptPriority(31,200);
    TEST_ASSERT_EQUAL(200,nvicGetInterruptPriority(31));
}

void test_Nvic_nvicSetInterruptPriority_wrong_interrupt_number(void){
    Try{
        nvicSetInterruptPriority(240,200);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicSetInterruptPriority_neg_interrupt_number(void){
    Try{
        nvicSetInterruptPriority(-1,200);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}

void test_Nvic_nvicSetInterruptPriority_wrong_interrupt_priority(void){
    Try{
        nvicSetInterruptPriority(238,300);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_PRIORTY,ex->errorCode);
    }
}

void test_Nvic_nvicSetInterruptPriority_neg_interrupt_priority(void){
    Try{
        nvicSetInterruptPriority(238,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_PRIORTY,ex->errorCode);
    }
}
void test_nvicSoftwareTriggerInterrupt_given_interruptNum_50_expect_stir_register_array(void){
    nvicSoftwareTriggerInterrupt(50);
    TEST_ASSERT_EQUAL(50,fakeNvic.stir);
}

void test_nvicSoftwareTriggerInterrupt_given_interruptNum_240_expect_error(void){
    Try{
        nvicSoftwareTriggerInterrupt(240);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(NVIC_INVALID_INTERRUPT_NUM,ex->errorCode);
    }
}
