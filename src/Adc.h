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

typedef struct AdcRegMap AdcRegMap;
struct AdcRegMap {
    AdcReg adc1;
    IoRegister reserved0[44];
    AdcReg adc2;
    IoRegister reserved1[44];
    AdcReg adc3;
    IoRegister reserved2[44];
    AdcCommonReg adcCommon;
};

typedef enum{
	 OVERRUN_INTERRUPT,JEOCIE_INTERRUPT,AWDIE_INTERRUPT,
   EOCIE_INTERRUPT,
} AdcInterrupt;

typedef enum{
	 12_BIT_ADC_RES,10_BIT_ADC_RES,8_BIT_ADC_RES,
   6_BIT_ADC_RES,
} AdcResolution;

typedef enum{
	 DIVIDE_2,DIVIDE_4,DIVIDE_6,DIVIDE_8,
} AdcSetPrescaler;

typedef enum{
	 3_CYCLES,15_CYCLES,28_CYCLES,56_CYCLES,
   84_CYCLES,112_CYCLES,144_CYCLES,480_CYCLES
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
void adcSetADCResolution(AdcReg* adc,,AdcResolution value); //
void adcSetWatchdogRegularChannel(AdcReg* adc,EnableDisable mode);
void adcSetWatchdogInjectedChannel(AdcReg* adc,EnableDisable mode);
void adcSetDiscontinuousModeChannelCount(AdcReg* adc , ChannelName channel);
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
void adcSetSamplingTime(AdcReg* adc,ChannelName channel,AdcCycleTime cycleTime);

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
void adcSetRegularSequence(AdcReg* adc , ChannelName []sequence);
void adcSetInjectedSequence(AdcReg* adc , ChannelName []sequence);

//read
int adcReadInjectedDataReg(AdcReg* adc);
int adcReadRegularDataReg(AdcReg* adc);

//common
void adcEnableTempSensorAndVref(AdcReg* adc);
void adcDisableTempSensorAndVref(AdcReg* adc);
void adcEnableVbatChannel(AdcReg* adc);
void adcDisableVbatChannel(AdcReg* adc);
void adcSetPrescaler(AdcCommonReg * adc , AdcSetPrescaler prescale);
//void adcSetDMAModeforMultiADC(AdcCommonReg * adc,int mode);
//void adcSetDMARequestModeforMultiADC(AdcReg* adc,int value);
//void adcSetDelayBetween2SampPhase(AdcCommonReg * adc , int mode);
//void adcSetMultiProcessorMode(AdcCommonReg * adc , int mode);
#endif // ADC_H
