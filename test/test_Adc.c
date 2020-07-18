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

void test_Adc_adcOverrunFlagCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcOverrunFlagCheck(adc1));
}
void test_Adc_adcOverrunFlagCheck_one(void){
    adc1->sr |= (1 << 5);
    TEST_ASSERT_EQUAL(1,adcOverrunFlagCheck(adc1));
}
void test_Adc_adcOverrunFlagCheck_NULL_input(void){
    Try{
        adcOverrunFlagCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcRegularChannelStartFlagCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcRegularChannelStartFlagCheck(adc1));
}
void test_Adc_adcRegularChannelStartFlagCheck_one(void){
    adc1->sr |= (1 << 4);
    TEST_ASSERT_EQUAL(1,adcRegularChannelStartFlagCheck(adc1));
}
void test_Adc_adcRegularChannelStartFlagCheck_NULL_input(void){
    Try{
        adcRegularChannelStartFlagCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcInjectedChannelStartFlagCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcInjectedChannelStartFlagCheck(adc1));
}
void test_Adc_adcInjectedChannelStartFlagCheck_one(void){
    adc1->sr |= (1 << 3);
    TEST_ASSERT_EQUAL(1,adcInjectedChannelStartFlagCheck(adc1));
}
void test_Adc_adcInjectedChannelStartFlagCheck_NULL_input(void){
    Try{
        adcInjectedChannelStartFlagCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcInjectedChannelEOConversionCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcInjectedChannelEOConversionCheck(adc1));
}
void test_Adc_adcInjectedChannelEOConversionCheck_one(void){
    adc1->sr |= (1 << 2);
    TEST_ASSERT_EQUAL(1,adcInjectedChannelEOConversionCheck(adc1));
}
void test_Adc_adcInjectedChannelEOConversionCheck_NULL_input(void){
    Try{
        adcInjectedChannelEOConversionCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcRegularChannelEOConversionCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcRegularChannelEOConversionCheck(adc1));
}
void test_Adc_adcRegularChannelEOConversionCheck_one(void){
    adc1->sr |= (1 << 1);
    TEST_ASSERT_EQUAL(1,adcRegularChannelEOConversionCheck(adc1));
}
void test_Adc_adcRegularChannelEOConversionCheck_NULL_input(void){
    Try{
        adcRegularChannelEOConversionCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcAnalogWatchDogFlagCheck_zero(void){
    TEST_ASSERT_EQUAL(0,adcAnalogWatchDogFlagCheck(adc1));
}
void test_Adc_adcAnalogWatchDogFlagCheck_one(void){
    adc1->sr |= (1 << 0);
    TEST_ASSERT_EQUAL(1,adcAnalogWatchDogFlagCheck(adc1));
}
void test_Adc_adcAnalogWatchDogFlagCheck_NULL_input(void){
    Try{
        adcAnalogWatchDogFlagCheck(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcEnableOverrunInterrupt_zero(void){
    adcEnableOverrunInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<26,adc1->cr1);
}
void test_Adc_adcEnableOverrunInterrupt_NULL(void){
    Try{
        adcEnableOverrunInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcDisableOverrunInterrupt_zero(void){
    adcEnableOverrunInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<26,adc1->cr1);
    adcDisableOverrunInterrupt(adc1);
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}
void test_Adc_adcDisableOverrunInterrupt_NULL(void){
    Try{
        adcDisableOverrunInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcEnableInjectedChannelInterrupt(void){
    adcEnableInjectedChannelInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<7,adc1->cr1);
}
void test_Adc_adcEnableInjectedChannelInterrupt_NULL(void){
    Try{
        adcEnableInjectedChannelInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcDisableInjectedChannelInterrupt(void){
    adcEnableInjectedChannelInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<7,adc1->cr1);
    adcDisableInjectedChannelInterrupt(adc1);
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}
void test_Adc_adcDisableInjectedChannelInterrupt_NULL(void){
    Try{
        adcDisableInjectedChannelInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}

void test_Adc_adcEnableAnalogWatchdogInterrupt(void){
    adcEnableAnalogWatchdogInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<6,adc1->cr1);
}
void test_Adc_adcEnableAnalogWatchdogInterrupt_NULL(void){
    Try{
        adcEnableAnalogWatchdogInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}
void test_Adc_adcDisableAnalogWatchdogInterrupt(void){
    adcEnableAnalogWatchdogInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<6,adc1->cr1);
    adcDisableAnalogWatchdogInterrupt(adc1);
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}
void test_Adc_adcDisableAnalogWatchdogInterrupt_NULL(void){
    Try{
        adcDisableAnalogWatchdogInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}

void test_Adc_adcEnableEOCInterrupt_zero(void){
    adcEnableEOCInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<5,adc1->cr1);
}
void test_Adc_adcEnableEOCInterrupt_NULL(void){
    Try{
        adcEnableEOCInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}

void test_Adc_adcDisableEOCInterrupt_zero(void){
    adcEnableEOCInterrupt(adc1);
    TEST_ASSERT_EQUAL(1<<5,adc1->cr1);
    adcDisableEOCInterrupt(adc1);
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}
void test_Adc_adcDisableEOCInterrupt_NULL(void){
    Try{
        adcDisableEOCInterrupt(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetADCResolution_12(void){
    adcSetADCResolution(adc1,ADC_RES_12_BIT);
    TEST_ASSERT_EQUAL(0,adc1->cr1);
}

void test_Adc_adcSetADCResolution_6(void){
    adcSetADCResolution(adc1,ADC_RES_6_BIT);
    TEST_ASSERT_EQUAL(3<<24,adc1->cr1);
}

void test_Adc_adcSetADCResolution_10(void){
    adcSetADCResolution(adc1,ADC_RES_10_BIT);
    TEST_ASSERT_EQUAL(1<<24,adc1->cr1);
}

void test_Adc_adcSetADCResolution_8(void){
    adcSetADCResolution(adc1,ADC_RES_8_BIT);
    TEST_ASSERT_EQUAL(2<<24,adc1->cr1);
}
void test_Adc_adcSetADCResolution_NULL(void){
    Try{
        adcSetADCResolution(NULL,ADC_RES_12_BIT);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetADCResolution_res_larger(void){
    Try{
        adcSetADCResolution(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_RESOLUTION,ex->errorCode);
    }
}

void test_Adc_adcSetADCResolution_res_neg_error(void){
    Try{
        adcSetADCResolution(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_RESOLUTION,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogRegularChannel_DISABLE(void){
    adcSetWatchdogRegularChannel(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<23,adc1->cr1);
}

void test_Adc_adcSetWatchdogRegularChannel_ENABLE(void){
    adcSetWatchdogRegularChannel(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<23,adc1->cr1);
}

void test_Adc_adcSetWatchdogRegularChannel_NULL(void){
    Try{
        adcSetWatchdogRegularChannel(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogRegularChannel_res_larger(void){
    Try{
        adcSetWatchdogRegularChannel(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogRegularChannel_res_neg_error(void){
    Try{
        adcSetWatchdogRegularChannel(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogInjectedChannel_DISABLE(void){
    adcSetWatchdogInjectedChannel(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<22,adc1->cr1);
}

void test_Adc_adcSetWatchdogInjectedChannel_ENABLE(void){
    adcSetWatchdogInjectedChannel(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<22,adc1->cr1);
}
void test_Adc_adcSetWatchdogInjectedChannel_NULL(void){
    Try{
        adcSetWatchdogInjectedChannel(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogInjectedChannel_res_larger(void){
    Try{
        adcSetWatchdogInjectedChannel(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogInjectedChannel_res_neg_error(void){
    Try{
        adcSetWatchdogInjectedChannel(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeChannelCount_1_channel(void){
    adcSetDiscontinuousModeChannelCount(adc1,1);
    TEST_ASSERT_EQUAL(0<<13,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeChannelCount_8_channel(void){
    adcSetDiscontinuousModeChannelCount(adc1,8);
    TEST_ASSERT_EQUAL(7<<13,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeChannelCount_4_channel(void){
    adcSetDiscontinuousModeChannelCount(adc1,4);
    TEST_ASSERT_EQUAL(3<<13,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeChannelCount_NULL(void){
    Try{
        adcSetDiscontinuousModeChannelCount(NULL,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeChannelCount_res_larger(void){
    Try{
        adcSetDiscontinuousModeChannelCount(adc1,12);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_NUMBER_OF_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeChannelCount_res_neg_error(void){
    Try{
        adcSetDiscontinuousModeChannelCount(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_NUMBER_OF_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeInjectedChannels_DISABLE(void){
    adcSetDiscontinuousModeInjectedChannels(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<12,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeInjectedChannels_ENABLE(void){
    adcSetDiscontinuousModeInjectedChannels(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<12,adc1->cr1);
}
void test_Adc_adcSetDiscontinuousModeInjectedChannels_NULL(void){
    Try{
        adcSetDiscontinuousModeInjectedChannels(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeInjectedChannels_res_larger(void){
    Try{
        adcSetDiscontinuousModeInjectedChannels(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeInjectedChannels_res_neg_error(void){
    Try{
        adcSetDiscontinuousModeInjectedChannels(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeRegularChannels_DISABLE(void){
    adcSetDiscontinuousModeRegularChannels(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<11,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeRegularChannels_ENABLE(void){
    adcSetDiscontinuousModeRegularChannels(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<11,adc1->cr1);
}

void test_Adc_adcSetDiscontinuousModeRegularChannels_NULL(void){
    Try{
        adcSetDiscontinuousModeRegularChannels(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeRegularChannels_res_larger(void){
    Try{
        adcSetDiscontinuousModeRegularChannels(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetDiscontinuousModeRegularChannels_res_neg_error(void){
    Try{
        adcSetDiscontinuousModeRegularChannels(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetAutomaticInjectedGroupConversion_DISABLE(void){
    adcSetAutomaticInjectedGroupConversion(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<10,adc1->cr1);
}

void test_Adc_adcSetAutomaticInjectedGroupConversion_ENABLE(void){
    adcSetAutomaticInjectedGroupConversion(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<10,adc1->cr1);
}

void test_Adc_adcSetAutomaticInjectedGroupConversion_NULL(void){
    Try{
        adcSetAutomaticInjectedGroupConversion(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetAutomaticInjectedGroupConversion_res_larger(void){
    Try{
        adcSetAutomaticInjectedGroupConversion(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetAutomaticInjectedGroupConversion_res_neg_error(void){
    Try{
        adcSetAutomaticInjectedGroupConversion(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcEnableAnalogWatchdogsOnAllChannels(void){
    adcEnableAnalogWatchdogsOnAllChannels(adc1);
    TEST_ASSERT_EQUAL(0<<9,adc1->cr1);
}
void test_Adc_adcEnableAnalogWatchdogsOnAllChannels_NULL(void){
    Try{
        adcEnableAnalogWatchdogsOnAllChannels(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcEnableAnalogWatchdogsOnSingleChannels(void){
    adcEnableAnalogWatchdogsOnAllChannels(adc1);
    TEST_ASSERT_EQUAL(0<<9,adc1->cr1);
    adcEnableAnalogWatchdogsOnSingleChannels(adc1);
    TEST_ASSERT_EQUAL(1<<9,adc1->cr1);
}
void test_Adc_adcEnableAnalogWatchdogsOnSingleChannels_NULL(void){
    Try{
        adcEnableAnalogWatchdogsOnSingleChannels(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetScanMode_DISABLE(void){
    adcSetScanMode(adc1,DISABLE_MODE);
    TEST_ASSERT_EQUAL(0<<8,adc1->cr1);
}

void test_Adc_adcSetScanMode_ENABLE(void){
    adcSetScanMode(adc1,ENABLE_MODE);
    TEST_ASSERT_EQUAL(1<<8,adc1->cr1);
}
void test_Adc_adcSetScanMode_NULL(void){
    Try{
        adcSetScanMode(NULL,ENABLE_MODE);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetScanMode_res_larger(void){
    Try{
        adcSetScanMode(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcSetScanMode_res_neg_error(void){
    Try{
        adcSetScanMode(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_MODE,ex->errorCode);
    }
}

void test_Adc_adcAnalogWatchdogChannelSelect_channel_0(void){
    adcAnalogWatchdogChannelSelect(adc1,CHANNEL_0);
    TEST_ASSERT_EQUAL(0<<0,adc1->cr1);
}

void test_Adc_adcAnalogWatchdogChannelSelect_channel_18(void){
    adcAnalogWatchdogChannelSelect(adc1,CHANNEL_18);
    TEST_ASSERT_EQUAL(18<<0,adc1->cr1);
}

void test_Adc_adcAnalogWatchdogChannelSelect_channel_14(void){
    adcAnalogWatchdogChannelSelect(adc1,CHANNEL_14);
    TEST_ASSERT_EQUAL(14<<0,adc1->cr1);
}
void test_Adc_adcAnalogWatchdogChannelSelect_NULL(void){
    Try{
        adcAnalogWatchdogChannelSelect(NULL,CHANNEL_14);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcAnalogWatchdogChannelSelect_res_larger(void){
    Try{
        adcAnalogWatchdogChannelSelect(adc1,20);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcAnalogWatchdogChannelSelect_res_neg_error(void){
    Try{
        adcAnalogWatchdogChannelSelect(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetStartRegularConversion(void){
    adcSetStartRegularConversion(adc1);
    TEST_ASSERT_EQUAL(1<<30,adc1->cr2);
}
void test_Adc_adcSetStartRegularConversion_NULL(void){
    Try{
        adcSetStartRegularConversion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcSetExternalTriggerRegularChannel_DISABLE(void){
    adcSetExternalTriggerRegularChannel(adc1,T_DETECTION_DISABLED);
    TEST_ASSERT_EQUAL(0<<28,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerRegularChannel_RISING(void){
    adcSetExternalTriggerRegularChannel(adc1,T_DETECTION_RISING);
    TEST_ASSERT_EQUAL(1<<28,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerRegularChannel_FALLING(void){
    adcSetExternalTriggerRegularChannel(adc1,T_DETECTION_FALLING);
    TEST_ASSERT_EQUAL(2<<28,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerRegularChannel_BOTH(void){
    adcSetExternalTriggerRegularChannel(adc1,T_DETECTION_BOTH_EDGE);
    TEST_ASSERT_EQUAL(3<<28,adc1->cr2);
}
void test_Adc_adcSetExternalTriggerRegularChannel_NULL(void){
    Try{
        adcSetExternalTriggerRegularChannel(NULL,T_DETECTION_RISING);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetExternalTriggerRegularChannel_res_larger(void){
    Try{
        adcSetExternalTriggerRegularChannel(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_TRIGGER_DET,ex->errorCode);
    }
}

void test_Adc_adcSetExternalTriggerRegularChannel_res_neg_error(void){
    Try{
        adcSetExternalTriggerRegularChannel(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_TRIGGER_DET,ex->errorCode);
    }
}

void test_Adc_adcSetStartInjectedConversion(void){
    adcSetStartInjectedConversion(adc1);
    TEST_ASSERT_EQUAL(1<<22,adc1->cr2);
}
void test_Adc_adcSetStartInjectedConversion_NULL(void){
    Try{
        adcSetStartInjectedConversion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcSetExternalTriggerInjectedChannel_DISABLE(void){
    adcSetExternalTriggerInjectedChannel(adc1,T_DETECTION_DISABLED);
    TEST_ASSERT_EQUAL(0<<20,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerInjectedChannel_RISING(void){
    adcSetExternalTriggerInjectedChannel(adc1,T_DETECTION_RISING);
    TEST_ASSERT_EQUAL(1<<20,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerInjectedChannel_FALLING(void){
    adcSetExternalTriggerInjectedChannel(adc1,T_DETECTION_FALLING);
    TEST_ASSERT_EQUAL(2<<20,adc1->cr2);
}

void test_Adc_adcSetExternalTriggerInjectedChannel_BOTH(void){
    adcSetExternalTriggerInjectedChannel(adc1,T_DETECTION_BOTH_EDGE);
    TEST_ASSERT_EQUAL(3<<20,adc1->cr2);
}
void test_Adc_adcSetExternalTriggerInjectedChannel_NULL(void){
    Try{
        adcSetExternalTriggerInjectedChannel(NULL,T_DETECTION_RISING);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetExternalTriggerInjectedChannel_res_larger(void){
    Try{
        adcSetExternalTriggerInjectedChannel(adc1,5);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_TRIGGER_DET,ex->errorCode);
    }
}

void test_Adc_adcSetExternalTriggerInjectedChannel_res_neg_error(void){
    Try{
        adcSetExternalTriggerInjectedChannel(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_TRIGGER_DET,ex->errorCode);
    }
}
void test_Adc_adcSetLeftDataAlignment(void){
    adcSetLeftDataAlignment(adc1);
    TEST_ASSERT_EQUAL(1<<11,adc1->cr2);
}
void test_Adc_adcSetLeftDataAlignment_NULL(void){
    Try{
        adcSetLeftDataAlignment(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcSetRightDataAlignment(void){
    adcSetLeftDataAlignment(adc1);
    TEST_ASSERT_EQUAL(1<<11,adc1->cr2);
    adcSetRightDataAlignment(adc1);
    TEST_ASSERT_EQUAL(0<<11,adc1->cr2);
}
void test_Adc_adcSetRightDataAlignment_NULL(void){
    Try{
        adcSetRightDataAlignment(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetContinousConvertion(void){
    adcSetContinousConvertion(adc1);
    TEST_ASSERT_EQUAL(1<<1,adc1->cr2);
}
void test_Adc_adcSetContinousConvertion_NULL(void){
    Try{
        adcSetContinousConvertion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}


void test_Adc_adcSetSingleConvertion(void){
    adcSetContinousConvertion(adc1);
    TEST_ASSERT_EQUAL(1<<1,adc1->cr2);
    adcSetSingleConvertion(adc1);
    TEST_ASSERT_EQUAL(0<<1,adc1->cr2);
}
void test_Adc_adcSetSingleConvertion_NULL(void){
    Try{
        adcSetSingleConvertion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcEnableADCConversion(void){
    adcEnableADCConversion(adc1);
    TEST_ASSERT_EQUAL(1<<0,adc1->cr2);
}
void test_Adc_adcEnableADCConversion_NULL(void){
    Try{
        adcEnableADCConversion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcDisableADCConversion(void){
    adcEnableADCConversion(adc1);
    TEST_ASSERT_EQUAL(1<<0,adc1->cr2);
    adcDisableADCConversion(adc1);
    TEST_ASSERT_EQUAL(0<<0,adc1->cr2);
}
void test_Adc_adcDisableADCConversion_NULL(void){
    Try{
        adcDisableADCConversion(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetSamplingTime_channel0_480cycles(void){
    adcSetSamplingTime(adc1,CHANNEL_0,ADC_SAMP_480_CYCLES);
    TEST_ASSERT_EQUAL(7,adc1->smpr2);
}

void test_Adc_adcSetSamplingTime_channel5_15cycles(void){
    adcSetSamplingTime(adc1,CHANNEL_5,ADC_SAMP_15_CYCLES);
    TEST_ASSERT_EQUAL(ADC_SAMP_15_CYCLES<<15,adc1->smpr2);
}

void test_Adc_adcSetSamplingTime_channel9_56cycles(void){
    adcSetSamplingTime(adc1,CHANNEL_9,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL(3<<27,adc1->smpr2);
}

void test_Adc_adcSetSamplingTime_channel11_56cycles(void){
    adcSetSamplingTime(adc1,CHANNEL_11,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL(3<<3,adc1->smpr1);
}

void test_Adc_adcSetSamplingTime_channel18_56cycles(void){
    adcSetSamplingTime(adc1,CHANNEL_18,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL(3<<24,adc1->smpr1);
}

void test_Adc_adcSetSamplingTime_channel18_56cycles_diff_channel(void){
    adcSetSamplingTime(adc1,CHANNEL_18,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL(3<<24,adc1->smpr1);
    adcSetSamplingTime(adc1,CHANNEL_17,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL((3<<24)|(3<<21),adc1->smpr1);
}

void test_Adc_adcSetSamplingTime_channel18_56cycles_override(void){
    adcSetSamplingTime(adc1,CHANNEL_18,ADC_SAMP_56_CYCLES);
    TEST_ASSERT_EQUAL(3<<24,adc1->smpr1);
    adcSetSamplingTime(adc1,CHANNEL_18,ADC_SAMP_480_CYCLES);
    TEST_ASSERT_EQUAL(7<<24,adc1->smpr1);
}
void test_Adc_adcSetSamplingTime_NULL(void){
    Try{
        adcSetSamplingTime(NULL,CHANNEL_18,ADC_SAMP_56_CYCLES);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetSamplingTime_channel_larger_than_c18(void){
    Try{
        adcSetSamplingTime(adc1,20,ADC_SAMP_56_CYCLES);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetSamplingTime_channel_neg_channel(void){
    Try{
        adcSetSamplingTime(adc1,-1,ADC_SAMP_56_CYCLES);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CHANNEL,ex->errorCode);
    }
}

void test_Adc_adcSetSamplingTime_error_sampling_neg(void){
    Try{
        adcSetSamplingTime(adc1,CHANNEL_18,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CYCLETIME,ex->errorCode);
    }
}

void test_Adc_adcSetSamplingTime_error_sampling_larger_than7(void){
    Try{
        adcSetSamplingTime(adc1,CHANNEL_18,8);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_CYCLETIME,ex->errorCode);
    }
}


void test_Adc_adcSetWatchdogHigherThreshold(void){
    adcSetWatchdogHigherThreshold(adc1,4095);
    TEST_ASSERT_EQUAL(4095,adc1->htr);
}
void test_Adc_adcSetWatchdogHigherThreshold_larger_than_4095(void){
    Try{
        adcSetWatchdogHigherThreshold(adc1,4096);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_THRESHOLD_VALUE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogHigherThreshold_smaller_than_0(void){
    Try{
        adcSetWatchdogHigherThreshold(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_THRESHOLD_VALUE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogHigherThreshold_random(void){
    adcSetWatchdogHigherThreshold(adc1,1234);
    TEST_ASSERT_EQUAL(1234,adc1->htr);
}

void test_Adc_adcSetWatchdogHigherThreshold_NULL(void){
    Try{
        adcSetWatchdogHigherThreshold(NULL,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogLowerThreshold(void){
    adcSetWatchdogLowerThreshold(adc1,4095);
    TEST_ASSERT_EQUAL(4095,adc1->ltr);
}

void test_Adc_adcSetWatchdogLowerThreshold_larger_than_4095(void){
    Try{
        adcSetWatchdogLowerThreshold(adc1,4096);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_THRESHOLD_VALUE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogLowerThreshold_smaller_than_0(void){
    Try{
        adcSetWatchdogLowerThreshold(adc1,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_THRESHOLD_VALUE,ex->errorCode);
    }
}

void test_Adc_adcSetWatchdogLowerThreshold_random(void){
    adcSetWatchdogLowerThreshold(adc1,1234);
    TEST_ASSERT_EQUAL(1234,adc1->ltr);
}
void test_Adc_adcSetWatchdogLowerThreshold_NULL(void){
    Try{
        adcSetWatchdogLowerThreshold(NULL,1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcReadInjectedDataReg1_zero(void){
    TEST_ASSERT_EQUAL(0,adcReadInjectedDataReg1(adc1));
}
void test_Adc_adcReadInjectedDataReg1(void){
    adc1->jdr1 = 1234;
    TEST_ASSERT_EQUAL(1234,adcReadInjectedDataReg1(adc1));
}

void test_Adc_adcReadInjectedDataReg1_NULL(void){
    Try{
        adcReadInjectedDataReg1(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcReadInjectedDataReg2_zero(void){
    TEST_ASSERT_EQUAL(0,adcReadInjectedDataReg2(adc1));
}
void test_Adc_adcReadInjectedDataReg2(void){
    adc1->jdr2 = 1234;
    TEST_ASSERT_EQUAL(1234,adcReadInjectedDataReg2(adc1));
}
void test_Adc_adcReadInjectedDataReg2_NULL(void){
    Try{
        adcReadInjectedDataReg2(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}
void test_Adc_adcReadInjectedDataReg3_zero(void){
    TEST_ASSERT_EQUAL(0,adcReadInjectedDataReg3(adc1));
}
void test_Adc_adcReadInjectedDataReg3(void){
    adc1->jdr3 = 0xABC;
    TEST_ASSERT_EQUAL(0xABC,adcReadInjectedDataReg3(adc1));
}

void test_Adc_adcReadInjectedDataReg3_NULL(void){
    Try{
        adcReadInjectedDataReg3(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcReadInjectedDataReg4_zero(void){
    TEST_ASSERT_EQUAL(0,adcReadInjectedDataReg4(adc1));
}
void test_Adc_adcReadInjectedDataReg4(void){
    adc1->jdr4 = 0xABC;
    TEST_ASSERT_EQUAL(0xABC,adcReadInjectedDataReg4(adc1));
}

void test_Adc_adcReadInjectedDataReg4_NULL(void){
    Try{
        adcReadInjectedDataReg4(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcEnableTempSensorAndVref(void){
    adcEnableVbatChannel(adcCommonReg);
    adcEnableTempSensorAndVref(adcCommonReg);
    TEST_ASSERT_EQUAL(1<<23,adcCommonReg->ccr);
}

void test_Adc_adcEnableTempSensorAndVref_NULL(void){
    Try{
        adcEnableTempSensorAndVref(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}


void test_Adc_adcDisableTempSensorAndVref(void){
    adcEnableTempSensorAndVref(adcCommonReg);
    TEST_ASSERT_EQUAL(1<<23,adcCommonReg->ccr);
    adcDisableTempSensorAndVref(adcCommonReg);
    TEST_ASSERT_EQUAL(0,adcCommonReg->ccr);
}

void test_Adc_adcDisableTempSensorAndVref_NULL(void){
    Try{
        adcDisableTempSensorAndVref(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcEnableVbatChannel(void){
    adcEnableVbatChannel(adcCommonReg);
    TEST_ASSERT_EQUAL(1<<22,adcCommonReg->ccr);
}

void test_Adc_adcEnableVbatChannel_NULL(void){
    Try{
        adcEnableVbatChannel(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcDisableVbatChannel(void){
    adcEnableVbatChannel(adcCommonReg);
    TEST_ASSERT_EQUAL(1<<22,adcCommonReg->ccr);
    adcDisableVbatChannel(adcCommonReg);
    TEST_ASSERT_EQUAL(0,adcCommonReg->ccr);
}

void test_Adc_adcDisableVbatChannel_NULL(void){
    Try{
        adcDisableVbatChannel(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetPrescaler_ADC_PRESCALE_DIVIDE_2(void){
    adcSetPrescaler(adcCommonReg,ADC_PRESCALE_DIVIDE_2);
    TEST_ASSERT_EQUAL(0<<16,adcCommonReg->ccr);
}

void test_Adc_adcSetPrescaler_ADC_PRESCALE_DIVIDE_4(void){
    adcSetPrescaler(adcCommonReg,ADC_PRESCALE_DIVIDE_4);
    TEST_ASSERT_EQUAL(1<<16,adcCommonReg->ccr);
}

void test_Adc_adcSetPrescaler_ADC_PRESCALE_DIVIDE_6(void){
    adcSetPrescaler(adcCommonReg,ADC_PRESCALE_DIVIDE_6);
    TEST_ASSERT_EQUAL(2<<16,adcCommonReg->ccr);
}

void test_Adc_adcSetPrescaler_ADC_PRESCALE_DIVIDE_8(void){
    adcSetPrescaler(adcCommonReg,ADC_PRESCALE_DIVIDE_8);
    TEST_ASSERT_EQUAL(3<<16,adcCommonReg->ccr);
}
void test_Adc_adcSetPrescaler_NULL(void){
    Try{
        adcSetPrescaler(NULL,ADC_PRESCALE_DIVIDE_8);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Adc_adcSetPrescaler_error_sampling_larger_than3(void){
    Try{
        adcSetPrescaler(adcCommonReg,4);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_PRESCALER,ex->errorCode);
    }
}

void test_Adc_adcSetPrescaler_error_sampling_negative(void){
    Try{
        adcSetPrescaler(adcCommonReg,-1);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");
    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(ADC_INVALID_PRESCALER,ex->errorCode);
    }
}
