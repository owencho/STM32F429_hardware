#include "ADC.h"
#include <stddef.h>
#include <stdint.h>
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
//SR
int adcOverrunFlagCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return (adc->sr >> 5) & 0x1;
}

int adcRegularChannelStartFlagCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return (adc->sr >> 4) & 0x1;
}

int adcInjectedChannelStartFlagCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return (adc->sr >> 3) & 0x1;
}
int adcInjectedChannelEOConversionCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return (adc->sr >> 2) & 0x1;
}

int adcRegularChannelEOConversionCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return (adc->sr >> 1) & 0x1;
}

int adcAnalogWatchDogFlagCheck(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");;
    }
    return (adc->sr >> 0) & 0x1;
}
//interrupt
void adcEnableOverrunInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1 << 26);
    adc->cr1 |= 1 << 26;
}

void adcDisableOverrunInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 |= (1<<26);
		adc->cr1 &= ~ (1<<26);
}

void adcEnableInjectedChannelInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1 << 7);
    adc->cr1 |= 1 << 7;
}

void adcDisableInjectedChannelInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 |= (1<<7);
		adc->cr1 &= ~ (1<<7);
}

void adcEnableAnalogWatchdogInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1 << 6);
    adc->cr1 |= 1 << 6;
}

void adcDisableAnalogWatchdogInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 |= (1<<6);
		adc->cr1 &= ~(1<<6);
}

void adcEnableEOCInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1 << 5);
    adc->cr1 |= 1 << 5;
}

void adcDisableEOCInterrupt(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 |= (1<<5);
		adc->cr1 &= ~(1<<5);
}

void adcSetADCResolution(AdcReg* adc,AdcResolution value){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(value > 4 || value <0 ){
        throwException(ADC_INVALID_RESOLUTION,"ADC input resolution is invalid ");
    }
    adc->cr1 &= ~(3<<24);
		adc->cr1 |= (value<<24);
}

void adcSetWatchdogRegularChannel(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE ){
        throwException(ADC_INVALID_MODE,"ADC input WatchdogRegularChannel mode is invalid ");
    }
    adc->cr1 &= ~(1<<23);
		adc->cr1 |= (mode<<23);
}

void adcSetWatchdogInjectedChannel(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(ADC_INVALID_MODE,"ADC input WatchdogInjectedChannel mode is invalid ");
    }
    adc->cr1 &= ~(1<<22);
		adc->cr1 |= (mode<<22);
}

void adcSetDiscontinuousModeChannelCount(AdcReg* adc,int numberOfChannel){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if( numberOfChannel > 8 ||numberOfChannel < 0 ){
        throwException(ADC_INVALID_NUMBER_OF_CHANNEL,"ADC number of channel is invalid ");
    }
    adc->cr1 &= ~(7<<13);
		adc->cr1 |= ((numberOfChannel-1)<<13);
}

void adcSetDiscontinuousModeInjectedChannels(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(ADC_INVALID_MODE,"ADC input Discontinuous Mode Injected Channels mode is invalid ");
    }
    adc->cr1 &= ~(1<<12);
		adc->cr1 |= (mode<<12);
}

void adcSetDiscontinuousModeRegularChannels(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(ADC_INVALID_MODE,"ADC input Discontinuous Mode Regular Channels mode is invalid ");
    }
    adc->cr1 &= ~(1<<11);
		adc->cr1 |= (mode<<11);
}


void adcSetAutomaticInjectedGroupConversion(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(ADC_INVALID_MODE,"ADC input automatic injected Group Conversion mode is invalid ");
    }
    adc->cr1 &= ~(1<<10);
		adc->cr1 |= (mode<<10);
}

void adcEnableAnalogWatchdogsOnAllChannels(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1<<9);
    adc->cr1 |= (0 << 9);
}

void adcEnableAnalogWatchdogsOnSingleChannels(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr1 &= ~(1<<9);
    adc->cr1 |= (1<<9);
}

void adcSetScanMode(AdcReg* adc,EnableDisable mode){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(mode > ENABLE_MODE || mode < DISABLE_MODE){
        throwException(ADC_INVALID_MODE,"ADC input automatic injected Group Conversion mode is invalid ");
    }
    adc->cr1 &= ~(1<<8);
		adc->cr1 |= (mode<<8);
}

void adcAnalogWatchdogChannelSelect(AdcReg* adc,ChannelName channel){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(channel > CHANNEL_18 ||channel < CHANNEL_0 ){
        throwException(ADC_INVALID_CHANNEL,"ADC selected channel for analog watchdogs is invalid ");
    }
    adc->cr1 &= ~(31<<0);
    adc->cr1 |= (channel<<0);
}

void adcSetStartRegularConversion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<30);
    adc->cr2 |= (1<<30);
}

void adcSetExternalTriggerRegularChannel(AdcReg* adc,TriggerDetection value){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(value < T_DETECTION_DISABLED || value > T_DETECTION_BOTH_EDGE ){
        throwException(ADC_INVALID_TRIGGER_DET,"ADC input trigger detection is invalid");
    }
    adc->cr2 &= ~(3<<28);
    adc->cr2 |= (value<<28);
}

void adcSetStartInjectedConversion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<22);
    adc->cr2 |= (1<<22);
}

void adcSetExternalTriggerInjectedChannel(AdcReg* adc,TriggerDetection value){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(value < T_DETECTION_DISABLED || value > T_DETECTION_BOTH_EDGE ){
        throwException(ADC_INVALID_TRIGGER_DET,"ADC input trigger detection is invalid");
    }
    adc->cr2 &= ~(3<<20);
    adc->cr2 |= (value<<20);
}

void adcSetRightDataAlignment(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<11);
    adc->cr2 |= (0<<11);
}

void adcSetLeftDataAlignment(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<11);
    adc->cr2 |= (1<<11);
}

void adcSetContinousConvertion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<1);
    adc->cr2 |= (1<<1);
}

void adcSetSingleConvertion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<1);
    adc->cr2 |= (0<<1);
}

void adcEnableADCConversion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<0);
    adc->cr2 |= (1<<0);
}

void adcDisableADCConversion(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adc->cr2 &= ~(1<<0);
    adc->cr2 |= (0<<0);
}

void adcSetSamplingTime(AdcReg* adc,ChannelName channel,AdcSamplingCycle cycleTime){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(channel > 18 ||channel < 0 ){
        throwException(ADC_INVALID_CHANNEL,"ADC selected channel for sampling time is invalid ");
    }
    else if(cycleTime > ADC_SAMP_480_CYCLES ||cycleTime < ADC_SAMP_3_CYCLES ){
        throwException(ADC_INVALID_CYCLETIME,"ADC cycleTime for sampling time is invalid");
    }
    if(channel > 9){
        adc->smpr1 &= ~(7<<(3*(channel-10)));
        adc->smpr1 |= (cycleTime<<(3*(channel-10)));
    }
    else{
        adc->smpr2 &= ~(7<<(3*(channel)));
        adc->smpr2 |= (cycleTime<<(3*(channel)));
    }
}

void adcSetWatchdogHigherThreshold(AdcReg* adc,int threshold){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(threshold < 0 || threshold > 0xFFF){
        throwException(ADC_INVALID_THRESHOLD_VALUE,"ADC threshold value is invalid");
    }
    adc->htr = threshold & 0xFFF;
}

void adcSetWatchdogLowerThreshold(AdcReg* adc,int threshold){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if(threshold < 0 || threshold > 0xFFF){
        throwException(ADC_INVALID_THRESHOLD_VALUE,"ADC threshold value is invalid for watchdogs lower threshold");
    }
    adc->ltr = threshold & 0xFFF;
}

void adcSetRegularSequence(AdcReg* adc , ChannelName sequence[]){
    int arraySize = 0 ;
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    for(int i = 0 ; sequence[i] != END_OF_CHANNEL_SEQ ;i++){
        if(i > 15 && sequence[i] != END_OF_CHANNEL_SEQ ){
            throwException(ADC_REGULAR_SEQUENCE_OVER,"the sequence for injected only expect 4 item but the sequence array larger than 4");
            break;
        }else if(sequence[i] > CHANNEL_18 || sequence[i] < 0){
            throwException(ADC_INVALID_SEQUENCE_NUM,"invalid sequence number on sequence %d for regular sequence",i+1);
        }
        adcSetSingleSequenceRegister(adc,sequence[i],i+1);
        arraySize++;
    }
    adcSetRegularSequenceLength(adc,arraySize);
}

void adcSetRegularSequenceLength(AdcReg* adc,int length){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if ( length > 16 ||length <= 0 ){
        throwException(ADC_INVALID_SEQUENCE_LENGTH,"ADC invalid length for regular sequence");
    }
    adc->sqr1 &= ~(15<<20);
    adc->sqr1 |= ((length-1)<<20);
}

void adcSetSingleSequenceRegister(AdcReg* adc,ChannelName channel,int sequenceNum){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if ( sequenceNum > 16 ||sequenceNum <= 0 ){
        throwException(ADC_INVALID_SEQUENCE_NUM,"ADC invalid sequence number for regular sequence");
    }
    if(channel < 0 ||channel >CHANNEL_18){
        throwException(ADC_INVALID_CHANNEL,"ADC invalid channel to set single sequence register");
    }
    int shiftBit = sequenceNum -1;
    if(sequenceNum < 7){
        adc->sqr3 &= ~(31<<(shiftBit*5));
        adc->sqr3 |= (channel<<(shiftBit*5));
    }
    else if (sequenceNum > 6 && sequenceNum < 13){
        adc->sqr2 &= ~(31<<((shiftBit-6)*5));
        adc->sqr2 |= (channel<<((shiftBit-6)*5));
    }
    else{
        adc->sqr1 &= ~(31<<((shiftBit-12)*5));
        adc->sqr1 |= (channel<<((shiftBit-12)*5));
    }
}


void adcSetInjectedSequence(AdcReg* adc , ChannelName sequence[]){
    int arraySize = 0 ;
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    for(int i = 0 ; sequence[i] != END_OF_CHANNEL_SEQ ;i++){
        if(i > 3 && sequence[i] != END_OF_CHANNEL_SEQ ){
            throwException(ADC_INJECT_SEQUENCE_OVER,"the sequence for injected only expect 4 item but the sequence array larger than 4");
            break;
        }else if(sequence[i] > CHANNEL_18 || sequence[i] < 0){
            throwException(ADC_INVALID_SEQUENCE_NUM,"invalid sequence number on sequence %d for regular sequence",i+1);
        }
        adcSetSingleInjectionRegister(adc,sequence[i],i+1);
        arraySize++;
    }
    adcSetInjectedSequenceLength(adc,arraySize);
}

void adcSetInjectedSequenceLength(AdcReg* adc,int length){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if ( length > 4 ||length <= 0 ){
        throwException(ADC_INVALID_SEQUENCE_LENGTH,"ADC invalid length for injected sequence");
    }
    adc->jsqr &= ~(3<<20);
    adc->jsqr |= ((length-1)<<20);
}

void adcSetSingleInjectionRegister(AdcReg* adc,ChannelName channel,int sequenceNum){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if ( sequenceNum > 4 ||sequenceNum <= 0 ){
        throwException(ADC_INVALID_SEQUENCE_NUM,"ADC invalid sequence number for regular sequence");
    }
    if(channel < 0 ||channel >CHANNEL_18){
        throwException(ADC_INVALID_CHANNEL,"ADC invalid channel to set single injected sequence register");
    }
    int shiftBit = sequenceNum -1;
    adc->jsqr &= ~(31<<((shiftBit*5)));
    adc->jsqr |= (channel<<((shiftBit*5)));
}


int adcReadInjectedDataReg1(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return adc->jdr1 & 0xFFFF;
}
int adcReadInjectedDataReg2(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return adc->jdr2 & 0xFFFF;
}
int adcReadInjectedDataReg3(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return adc->jdr3 & 0xFFFF;
}
int adcReadInjectedDataReg4(AdcReg* adc){
    if(adc == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    return adc->jdr4 & 0xFFFF;
}

void adcEnableTempSensorAndVref(AdcCommonReg * adcCommon){
    if(adcCommon == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adcDisableVbatChannel(adcCommon);
    adcCommon->ccr &= ~(1<<23);
    adcCommon->ccr |= (1<<23);
}

void adcDisableTempSensorAndVref(AdcCommonReg * adcCommon){
    if(adcCommon == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adcCommon->ccr &= ~(1<<23);
    adcCommon->ccr |= (0<<23);
}

void adcEnableVbatChannel(AdcCommonReg * adcCommon){
    if(adcCommon == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adcCommon->ccr &= ~(1<<22);
    adcCommon->ccr |= (1<<22);
}

void adcDisableVbatChannel(AdcCommonReg * adcCommon){
    if(adcCommon == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    adcCommon->ccr &= ~(1<<22);
    adcCommon->ccr |= (0<<22);
}

void adcSetPrescaler(AdcCommonReg * adcCommon , AdcSetPrescaler prescale){
    if(adcCommon == NULL){
        throwException(ADC_REG_INPUT_NULL,"ADC register input is NULL");
    }
    else if (prescale < ADC_PRESCALE_DIVIDE_2 || prescale > ADC_PRESCALE_DIVIDE_8){
        throwException(ADC_INVALID_PRESCALER,"invalid prescaler");
    }
    adcCommon->ccr &= ~(3<<16);
    adcCommon->ccr |= (prescale<<16);
}
