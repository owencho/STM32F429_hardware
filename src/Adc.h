#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
typedef struct AdcReg AdcReg;
struct AdcReg {
    IoRegister sr;
    IoRegister cr1;
    IoRegister cr2;
    IoRegister smpr1;
    IoRegister smpr2;
    IoRegister jofr1;
    IoRegister jofr2;
    IoRegister jofr3;
    IoRegister jofr4;
    IoRegister htr;
    IoRegister ltr;
    IoRegister sqr1;
    IoRegister sqr2;
    IoRegister sqr3;
    IoRegister jsqr;
    IoRegister jdr1;
    IoRegister jdr2;
    IoRegister jdr3;
    IoRegister jdr4;
    IoRegister dr;
};

typedef struct AdcCommonReg AdcCommonReg;
struct AdcCommonReg {
    IoRegister csr;
    IoRegister ccr;
    IoRegister cdr;
};

#define adc1 ((AdcReg*)(ADC1_BASEADDRESS))
#define adc2 ((AdcReg*)(ADC2_BASEADDRESS))
#define adc3 ((AdcReg*)(ADC3_BASEADDRESS))
#define adcCommonReg ((AdcCommonReg*)(ADC_COMMON_BASEADDRESS))

typedef enum{
	 ADC_RES_12_BIT,ADC_RES_10_BIT,ADC_RES_8_BIT,
   ADC_RES_6_BIT,
} AdcResolution;

typedef enum{
	 ADC_PRESCALE_DIVIDE_2,ADC_PRESCALE_DIVIDE_4,
   ADC_PRESCALE_DIVIDE_6,ADC_PRESCALE_DIVIDE_8,
} AdcSetPrescaler;

typedef enum{
	 ADC_SAMP_3_CYCLES,ADC_SAMP_15_CYCLES,ADC_SAMP_28_CYCLES,
   ADC_SAMP_56_CYCLES,ADC_SAMP_84_CYCLES,ADC_SAMP_112_CYCLES,
   ADC_SAMP_144_CYCLES,ADC_SAMP_480_CYCLES
} AdcSamplingCycle;

//interrupt
void adcEnableOverrunInterrupt(AdcReg* adc);
void adcDisableOverrunInterrupt(AdcReg* adc);
void adcEnableInjectedChannelInterrupt(AdcReg* adc);
void adcDisableInjectedChannelInterrupt(AdcReg* adc);
void adcEnableAnalogWatchdogInterrupt(AdcReg* adc);
void adcDisableAnalogWatchdogInterrupt(AdcReg* adc);
void adcEnableEOCInterrupt(AdcReg* adc);
void adcDisableEOCInterrupt(AdcReg* adc);
//SR
int adcOverrunFlagCheck(AdcReg* adc);
int adcRegularChannelStartFlagCheck(AdcReg* adc);
int adcInjectedChannelStartFlagCheck(AdcReg* adc);
int adcInjectedChannelEOConversionCheck(AdcReg* adc);
int adcRegularChannelEOConversionCheck(AdcReg* adc);
int adcAnalogWatchDogFlagCheck(AdcReg* adc);
//CR1
void adcSetADCResolution(AdcReg* adc,AdcResolution value); //
void adcSetWatchdogRegularChannel(AdcReg* adc,EnableDisable mode);
void adcSetWatchdogInjectedChannel(AdcReg* adc,EnableDisable mode);
void adcSetDiscontinuousModeChannelCount(AdcReg* adc,int numberOfChannel);
void adcSetDiscontinuousModeInjectedChannels(AdcReg* adc,EnableDisable mode);
void adcSetDiscontinuousModeRegularChannels(AdcReg* adc,EnableDisable mode);
void adcSetAutomaticInjectedGroupConversion(AdcReg* adc,EnableDisable mode);
void adcEnableAnalogWatchdogsOnAllChannels(AdcReg* adc);
void adcEnableAnalogWatchdogsOnSingleChannels(AdcReg* adc);
void adcSetScanMode(AdcReg* adc,EnableDisable mode);
void adcAnalogWatchdogChannelSelect(AdcReg* adc,ChannelName channel);

//CR2
void adcSetStartRegularConversion(AdcReg* adc); //
void adcSetExternalTriggerRegularChannel(AdcReg* adc,TriggerDetection value); //
//void adcSetExternalEventSelectForRegularGroup(AdcReg* adc,int value);
void adcSetStartInjectedConversion(AdcReg* adc); // must set ADON as one
void adcSetExternalTriggerInjectedChannel(AdcReg* adc,TriggerDetection value); //
//void adcSetExternalEventSelectForInjectedGroup(AdcReg* adc,int value);
void adcSetRightDataAlignment(AdcReg* adc); //
void adcSetLeftDataAlignment(AdcReg* adc); //
//void adcSetEndOfConversionMode(AdcReg* adc,int value);
//void adcSetDMARequestMode(AdcReg* adc,int value);
//void adcSetDMAMode(AdcReg* adc,int value);
void adcSetContinousConvertion(AdcReg* adc); //
void adcSetSingleConvertion(AdcReg* adc); //
void adcEnableADCConversion(AdcReg* adc); //
void adcDisableADCConversion(AdcReg* adc); //

//sampling
void adcSetSamplingTime(AdcReg* adc,ChannelName channel,AdcSamplingCycle cycleTime);

//jofr
/*
void adcSetOffsetforInjectedChannel1(AdcReg* adc,int offset);
void adcSetOffsetforInjectedChannel2(AdcReg* adc,int offset);
void adcSetOffsetforInjectedChannel3(AdcReg* adc,int offset);
void adcSetOffsetforInjectedChannel4(AdcReg* adc,int offset);
*/
//watchdogs threshold
void adcSetWatchdogHigherThreshold(AdcReg* adc,int threshold);
void adcSetWatchdogLowerThreshold(AdcReg* adc,int threshold);

//sequence
void adcSetRegularSequence(AdcReg* adc , ChannelName sequence[]);
void adcSetRegularSequenceLength(AdcReg* adc,int length);
void adcSetSingleSequenceRegister(AdcReg* adc,ChannelName channel,int sequenceNum);
void adcSetInjectedSequence(AdcReg* adc , ChannelName sequence[]);
void adcSetInjectedSequenceLength(AdcReg* adc,int length);
void adcSetSingleInjectionRegister(AdcReg* adc,ChannelName channel,int sequenceNum);

//read
int adcReadInjectedDataReg1(AdcReg* adc);
int adcReadInjectedDataReg2(AdcReg* adc);
int adcReadInjectedDataReg3(AdcReg* adc);
int adcReadInjectedDataReg4(AdcReg* adc);
int adcReadRegularDataReg(AdcReg* adc);

//common
void adcEnableTempSensorAndVref(AdcCommonReg * adcCommon);
void adcDisableTempSensorAndVref(AdcCommonReg * adcCommon);
void adcEnableVbatChannel(AdcCommonReg * adcCommon);
void adcDisableVbatChannel(AdcCommonReg * adcCommon);
void adcSetPrescaler(AdcCommonReg * adcCommon , AdcSetPrescaler prescale);
//void adcSetDMAModeforMultiADC(AdcCommonReg * adc,int mode);
//void adcSetDMARequestModeforMultiADC(AdcReg* adc,int value);
//void adcSetDelayBetween2SampPhase(AdcCommonReg * adc , int mode);
//void adcSetMultiProcessorMode(AdcCommonReg * adc , int mode);
#endif // ADC_H
