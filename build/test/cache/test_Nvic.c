#include "build/temp/_test_Nvic.c"
#include "Core/Inc/Common.h"
#include "test/support/BaseAddress.h"
#include "Core/Inc/Nvic.h"
#include "C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"








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

    ((NvicRegs*)(getNvicBaseAddress()))->ISER[2]=0xffaabb;

    UnityAssertEqualNumber((UNITY_INT)((0xffaabb)), (UNITY_INT)((fakeNvic.ISER[2])), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicEnableInterrupt_given_interruptNum_75_expect_ISER_register_array2(void){

    nvicEnableInterrupt(75);

    UnityAssertEqualNumber((UNITY_INT)((1<<11)), (UNITY_INT)((fakeNvic.ISER[2])), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicDisableInterrupt_given_interruptNum_75_expect_ICER_register_array2(void){

    nvicDisableInterrupt(73);

    UnityAssertEqualNumber((UNITY_INT)((1<<9)), (UNITY_INT)((fakeNvic.ICER[2])), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicSetPendingInterrupt_given_interruptNum_12_expect_ISPR_register_array0(void){

    nvicSetPendingInterrupt(12);

    UnityAssertEqualNumber((UNITY_INT)((1<<12)), (UNITY_INT)((fakeNvic.ISPR[0])), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicClearPendingInterrupt_given_interruptNum_32_expect_ICPR_register_array1(void){

    nvicClearPendingInterrupt(32);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((fakeNvic.ICPR[1])), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicIsInterruptActive_given_interruptNum_120_expect_IABR_register_array3(void){

    ((NvicRegs*)(getNvicBaseAddress()))->IABR[3]= 1<<24;

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((nvicIsInterruptActive(120))), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicSetInterruptPriority_given_interruptNum_210_expect_IPRx_register_array3(void){

    nvicSetInterruptPriority(210,5);

    UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((fakeNvic.IPR[52]>>16)), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

}



void test_Nvic_nvicGetInterruptPriority_given_interruptNum_31_expect_IPRx_register_array(void){

    nvicSetInterruptPriority(31,200);

    UnityAssertEqualNumber((UNITY_INT)((200)), (UNITY_INT)((nvicGetInterruptPriority(31))), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

}



void test_nvicSoftwareTriggerInterrupt_given_interruptNum_50_expect_STIR_register_array(void){

    nvicSoftwareTriggerInterrupt(50);

    UnityAssertEqualNumber((UNITY_INT)((50)), (UNITY_INT)((fakeNvic.STIR)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

}
