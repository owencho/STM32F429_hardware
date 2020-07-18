#include "unity.h"
#include "Adc.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
CEXCEPTION_T ex;

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
    Try{
        adcSetSingleInjectionRegister(NULL,CHANNEL_3,16);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetSingleInjectionRegister_channel_larger_than_c18(void){
    Try{
        adcSetSingleInjectionRegister(adc1,20,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetSingleInjectionRegister_negative_channel(void){
    Try{
        adcSetSingleInjectionRegister(adc1,-1,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetSingleInjectionRegister_zero_sequence(void){
    Try{
        adcSetSingleInjectionRegister(adc1,CHANNEL_18,0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_NUM,ex->errorCode);
    }
}

void test_Adc_adcSetSingleInjectionRegister_seq_5_error(void){
    Try{
        adcSetSingleInjectionRegister(adc1,CHANNEL_18,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_NUM,ex->errorCode);
    }
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
    Try{
        adcSetInjectedSequenceLength(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_LENGTH,ex->errorCode);
    }
}

void test_Adc_adcSetInjectedSequenceLength_negative(void){
    Try{
        adcSetInjectedSequenceLength(adc1,0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_LENGTH,ex->errorCode);
    }
}

void test_Adc_adcSetInjectedSequenceLength_NULL(void){
    Try{
        adcSetInjectedSequenceLength(NULL,12);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetInjectedSequence_3set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,END_OF_CHANNEL_SEQ};
    adcSetInjectedSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)
                      | (2<<20),adc1->jsqr);
}

void test_Adc_adcSetInjectedSequence_4set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,CHANNEL_3,END_OF_CHANNEL_SEQ};
    adcSetInjectedSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)
                      |(CHANNEL_3 << 15)| (3<<20),adc1->jsqr);
}

void test_Adc_adcSetInjectedSequence_5set_expect_one_missing(void){
    Try{
        ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,CHANNEL_5,
                                CHANNEL_1,END_OF_CHANNEL_SEQ};
        adcSetInjectedSequence(adc1,sequence);
        TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)|
                          (CHANNEL_5 << 15) | (3<<20),adc1->jsqr);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INJECT_SEQUENCE_OVER,ex->errorCode);
    }
}
