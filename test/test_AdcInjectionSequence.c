#include "unity.h"

#include "Adc.h"

AdcReg fakeAdc1,fakeAdc2,fakeAdc3;
AdcCommonReg fakeAdcCommon;
void setUp(void){
    int i;
    char * ptr =(char*)&fakeAdc1;
    for(i =0; i< sizeof(AdcReg);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getAdc1BaseAddress(){
    return (uintptr_t)&fakeAdc1;
}
uintptr_t getAdc2BaseAddress(){
    return (uintptr_t)&fakeAdc2;
}
uintptr_t getAdc3BaseAddress(){
    return (uintptr_t)&fakeAdc3;
}
uintptr_t getAdcCommonBaseAddress(){
    return (uintptr_t)&fakeAdcCommon;
}

///Sequence Register ////////////////
void test_Adc_adcSetSingleInjectionRegister_channel1_on_sq1(void){
    adcSetSingleInjectionRegister(adc1,CHANNEL_1,1);
    TEST_ASSERT_EQUAL(1,adc1->jsqr);
}

void test_Adc_adcSetSingleInjectionRegister_channel1_on_sq2(void){
    adcSetSingleInjectionRegister(adc1,CHANNEL_1,2);
    TEST_ASSERT_EQUAL(1<<5,adc1->jsqr);
}

void test_Adc_adcSetSingleInjectionRegister_channel1_on_sq4(void){
    adcSetSingleInjectionRegister(adc1,CHANNEL_1,4);
    TEST_ASSERT_EQUAL(1<<15,adc1->jsqr);
}

void test_Adc_adcSetSingleInjectionRegister_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetSingleInjectionRegister(NULL,CHANNEL_3,16);
}

void test_Adc_adcSetSingleInjectionRegister_exceed_seq(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetSingleInjectionRegister(adc1,CHANNEL_3,5);
}

void test_Adc_adcSetSingleInjectionRegister_exceed_channel_19(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetSingleInjectionRegister(adc1,19,4);
}

void test_Adc_adcSetInjectedSequenceLength_3(void){
    adcSetInjectedSequenceLength(adc1,3);
    TEST_ASSERT_EQUAL(2<<20,adc1->jsqr);
    // value 2 is 3 conversion
}

void test_Adc_adcSetInjectedSequenceLength_4(void){
    adcSetInjectedSequenceLength(adc1,4);
    TEST_ASSERT_EQUAL(3<<20,adc1->jsqr);
    // value 3 is 4 conversion
}

void test_Adc_adcSetInjectedSequenceLength_exceed_length_5(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetInjectedSequenceLength(adc1,5);
}

void test_Adc_adcSetInjectedSequenceLength_negative(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetInjectedSequenceLength(adc1,0);
}

void test_Adc_adcSetInjectedSequenceLength_NULL(void){
    TEST_IGNORE_MESSAGE("havent implement");
    adcSetInjectedSequenceLength(NULL,12);
}

void test_Adc_adcSetInjectedSequence_3set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,END_OF_CHANNEL_SEQ};
    adcSetInjectedSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)
                      | (2<<20),adc1->jsqr);
}

void test_Adc_adcSetInjectedSequence_5set_expect_one_missing(void){
    TEST_IGNORE_MESSAGE("must throw exception");
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,CHANNEL_5,
                            CHANNEL_1,END_OF_CHANNEL_SEQ};
    adcSetInjectedSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)|
                      (CHANNEL_5 << 15) | (3<<20),adc1->jsqr);
}
