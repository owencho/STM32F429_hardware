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
void test_Adc_adcSetSingleSequenceRegister_channel1_on_sq1(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_1,1);
    TEST_ASSERT_EQUAL(1,adc1->sqr3);
}

void test_Adc_adcSetSingleSequenceRegister_channel2_on_sq2_override(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_3,2);
    TEST_ASSERT_EQUAL(3<<5,adc1->sqr3);
    adcSetSingleSequenceRegister(adc1,CHANNEL_2,2);
    TEST_ASSERT_EQUAL(2<<5,adc1->sqr3);
}

void test_Adc_adcSetSingleSequenceRegister_channel3_on_sq6(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_3,6);
    TEST_ASSERT_EQUAL(3<<25,adc1->sqr3);
}

void test_Adc_adcSetSingleSequenceRegister_channel3_on_sq7(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_3,7);
    TEST_ASSERT_EQUAL(3,adc1->sqr2);
}

void test_Adc_adcSetSingleSequenceRegister_channel5_on_sq9(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_5,9);
    TEST_ASSERT_EQUAL(5<<10,adc1->sqr2);
}

void test_Adc_adcSetSingleSequenceRegister_channel5_on_sq25(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_5,12);
    TEST_ASSERT_EQUAL(5<<25,adc1->sqr2);
}

void test_Adc_adcSetSingleSequenceRegister_channel3_on_sq13(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_3,13);
    TEST_ASSERT_EQUAL(3,adc1->sqr1);
}

void test_Adc_adcSetSingleSequenceRegister_channel6_on_sq14(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_6,14);
    TEST_ASSERT_EQUAL(6<<5,adc1->sqr1);
}

void test_Adc_adcSetSingleSequenceRegister_channel3_on_sq16(void){
    adcSetSingleSequenceRegister(adc1,CHANNEL_3,16);
    TEST_ASSERT_EQUAL(3<<15,adc1->sqr1);
}
void test_Adc_adcSetSingleSequenceRegister_NULL(void){
    Try{
        adcSetSingleSequenceRegister(NULL,CHANNEL_3,16);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetSingleSequenceRegister_exceed_seq16(void){
    Try{
        adcSetSingleSequenceRegister(adc1,CHANNEL_3,17);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_NUM,ex->errorCode);
    }
}

void test_Adc_adcSetSingleSequenceRegister_exceed_negative_value(void){
    Try{
        adcSetSingleSequenceRegister(adc1,CHANNEL_3,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_NUM,ex->errorCode);
    }
}

void test_Adc_adcSetSingleSequenceRegister_exceed_channel18(void){
    Try{
        adcSetSingleSequenceRegister(adc1,20,15);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetSingleSequenceRegister_negative_channel(void){
    Try{
        adcSetSingleSequenceRegister(adc1,-1,15);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetRegularSequenceLength_16(void){
    adcSetRegularSequenceLength(adc1,16);
    TEST_ASSERT_EQUAL(15<<20,adc1->sqr1);
    // value 15 is 16 conversion
}

void test_Adc_adcSetRegularSequenceLength_15(void){
    adcSetRegularSequenceLength(adc1,15);
    TEST_ASSERT_EQUAL(14<<20,adc1->sqr1);
    // value 14 is 15 conversion
}

void test_Adc_adcSetRegularSequenceLength_exceed_length_16(void){
    Try{
        adcSetRegularSequenceLength(adc1,17);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_LENGTH,ex->errorCode);
    }
}
void test_Adc_adcSetRegularSequenceLength_negative(void){
    Try{
        adcSetRegularSequenceLength(adc1,0);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_LENGTH,ex->errorCode);
    }
}
void test_Adc_adcSetRegularSequenceLength_NULL(void){
    Try{
        adcSetRegularSequenceLength(NULL,12);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetRegularSequence_3set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,END_OF_CHANNEL_SEQ};
    adcSetRegularSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10),adc1->sqr3);
    TEST_ASSERT_EQUAL(2<<20,adc1->sqr1); //3 conversion
}

void test_Adc_adcSetRegularSequence_9set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,
                            CHANNEL_1,CHANNEL_3,CHANNEL_5,
                            CHANNEL_0,CHANNEL_6,CHANNEL_8,
                            END_OF_CHANNEL_SEQ};
    adcSetRegularSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)|
                      (CHANNEL_1<<15)|(CHANNEL_3<<20)|(CHANNEL_5 << 25),adc1->sqr3);
    TEST_ASSERT_EQUAL((CHANNEL_0<<0)|(CHANNEL_6<<5)|(CHANNEL_8 << 10),adc1->sqr2);
    TEST_ASSERT_EQUAL(8<<20,adc1->sqr1); //9 conversion
}

void test_Adc_adcSetRegularSequence_16set(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,CHANNEL_1,CHANNEL_3,
                            CHANNEL_5,CHANNEL_0,CHANNEL_6,CHANNEL_8,CHANNEL_10,
                            CHANNEL_15,CHANNEL_12,CHANNEL_16,CHANNEL_18,
                            CHANNEL_17,CHANNEL_15,
                            END_OF_CHANNEL_SEQ};
    adcSetRegularSequence(adc1,sequence);
    TEST_ASSERT_EQUAL((CHANNEL_2<<0)|(CHANNEL_2<<5)|(CHANNEL_9 << 10)|
                      (CHANNEL_1<<15)|(CHANNEL_3<<20)|(CHANNEL_5 << 25),adc1->sqr3);
    TEST_ASSERT_EQUAL((CHANNEL_0<<0)|(CHANNEL_6<<5)|(CHANNEL_8 << 10)
                      |(CHANNEL_10<<15)|(CHANNEL_15<<20)|(CHANNEL_12 << 25),adc1->sqr2);
    TEST_ASSERT_EQUAL((CHANNEL_16<<0)|(CHANNEL_18<<5)|(CHANNEL_17 << 10)|
                      (CHANNEL_15<<15)|(15<<20),adc1->sqr1);
    TEST_ASSERT_EQUAL(15,adc1->sqr1 >> 20); //16 conversion
}

void test_Adc_adcSetRegularSequence_16set_but_one_of_them_is_invalid(void){
    ChannelName sequence[] ={CHANNEL_2,CHANNEL_2,CHANNEL_9,CHANNEL_1,CHANNEL_3,
                            CHANNEL_5,CHANNEL_0,CHANNEL_6,CHANNEL_8,CHANNEL_10,
                            CHANNEL_15,CHANNEL_12,CHANNEL_16,CHANNEL_18,
                            CHANNEL_17,20,
                            END_OF_CHANNEL_SEQ};
    Try{
        adcSetRegularSequence(adc1,sequence);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_SEQUENCE_NUM,ex->errorCode);
    }
}
