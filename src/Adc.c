#include "Adc.h"

//SR
int adcOverrunFlagCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 5) & 0x1;
}

int adcRegularChannelStartFlagCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 4) & 0x1;
}

int adcInjectedChannelStartFlagCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 3) & 0x1;
}
int adcInjectedChannelEOConversionCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 2) & 0x1;
}

int adcRegularChannelEOConversionCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 1) & 0x1;
}

int adcAnalogWatchDogFlagCheck(AdcReg* adc){
    if(adc != NULL){
        return 0;
    }
    return (adc->sr >> 0) & 0x1;
}
//interrupt
void adcEnableOverrunInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1 << 26);
    adc->cr1 |= 1 << 26;
}

void adcDisableOverrunInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 |= (1<<26);
		adc->cr1 &= ~ (1<<26);
}

void adcEnableInjectedChannelInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1 << 7);
    adc->cr1 |= 1 << 7;
}

void adcDisableInjectedChannelInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 |= (1<<7);
		adc->cr1 &= ~ (1<<7);
}

void adcEnableAnalogWatchdogInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1 << 6);
    adc->cr1 |= 1 << 6;
}

void adcDisableAnalogWatchdogInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 |= (1<<6);
		adc->cr1 &= ~(1<<6);
}

void adcEnableEOCInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1 << 5);
    adc->cr1 |= 1 << 5;
}

void adcDisableEOCInterrupt(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 |= (1<<5);
		adc->cr1 &= ~(1<<5);
}

void adcSetADCResolution(AdcReg* adc,AdcResolution value){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(3<<25);
		adc->cr1 |= (value<<25);
}

void adcSetWatchdogRegularChannel(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<23);
		adc->cr1 |= (mode<<23);
}

void adcSetWatchdogInjectedChannel(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<22);
		adc->cr1 |= (mode<<22);
}

void adcSetWatchdogInjectedChannel(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<22);
		adc->cr1 |= (mode<<22);
}

void adcSetDiscontinuousModeChannelCount(AdcReg* adc,ChannelName channel){
    if(adc != NULL || channel > 7){
        return ;
    }
    adc->cr1 &= ~(7<<15);
		adc->cr1 |= (channel<<15);
}

void adcSetDiscontinuousModeInjectedChannels(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<12);
		adc->cr1 |= (mode<<12);
}

void adcSetDiscontinuousModeRegularChannels(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<11);
		adc->cr1 |= (mode<<11);
}


void adcSetAutomaticInjectedGroupConversion(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<10);
		adc->cr1 |= (mode<<10);
}

void adcEnableAnalogWatchdogsOnAllChannels(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<9);
    adc->cr1 |= (0 << 9);
}

void adcEnableAnalogWatchdogsOnSingleChannels(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<9);
    adc->cr1 |= (1<<9);
}

void adcSetScanMode(AdcReg* adc,EnableDisable mode){
    if(adc != NULL){
        return ;
    }
    adc->cr1 &= ~(1<<8);
		adc->cr1 |= (mode<<8);
}

void adcAnalogWatchdogChannelSelect(AdcReg* adc,ChannelName channel){
    if(adc != NULL || channel > 18){
        return ;
    }
    adc->cr1 &= ~(31<<4);
    adc->cr1 |= (mode<<4);
}

void adcSetStartRegularConversion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<30);
    adc->cr2 |= (1<<30);
}

void adcSetExternalTriggerRegularChannel(AdcReg* adc,TriggerDetection value){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(3<<29);
    adc->cr2 |= (value<<29);
}

void adcSetStartInjectedConversion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    //set ADON
    adc->cr2 &= ~(1<<22);
    adc->cr2 |= (1<<22);
}

void adcSetExternalTriggerInjectedChannel(AdcReg* adc,TriggerDetection value){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(3<<21);
    adc->cr2 |= (value<<21);
}

void adcSetRightDataAlignment(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<11);
    adc->cr2 |= (0<<11);
}

void adcSetLeftDataAlignment(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<11);
    adc->cr2 |= (1<<11);
}

void adcSetContinousConvertion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<1);
    adc->cr2 |= (1<<1);
}

void adcSetSingleConvertion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<1);
    adc->cr2 |= (0<<1);
}

void adcEnableADCConversion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<0);
    adc->cr2 |= (1<<0);
}

void adcDisableADCConversion(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->cr2 &= ~(1<<0);
    adc->cr2 |= (0<<0);
}

void adcSetSamplingTime(AdcReg* adc,ChannelName channel,AdcSamplingCycle cycleTime){
    if(adc != NULL || cycleTime > 7 || channel > 18){
        return ;
    }
    if(channel > 9){
        adc->smp1 &= ~(1<<(2*(channel-9)));
        adc->smp1 |= (cycleTime<<(2*(channel-9)));
    }
    else{
        adc->smp2 &= ~(1<<(2*(channel)));
        adc->smp2 |= (cycleTime<<(2*(channel)));
    }
}

void adcSetWatchdogHigherThreshold(AdcReg* adc,int threshold){
    if(adc != NULL ){
        return ;
    }
    adc->htr = threshold & 0xFFF;
}

void adcSetWatchdogLowerThreshold(AdcReg* adc,int threshold){
    if(adc != NULL){
        return ;
    }
    adc->ltr = threshold & 0xFFF;
}

void adcSetRegularSequence(AdcReg* adc , ChannelName []sequence){
  if(adc != NULL){
      return ;
  }
  int arraySize = sequence / sizeof(ChannelName);
  if(arraySize > 16){
      return;
  }
  for(int i = 0 ; i =< arraySize;i++){
      if(i < 7){
          adc->sqr3 &= ~(31<<(4+(i*5)));
          adc->sqr3 |= (sequence[i]<<(4+(i*5)));
      }
      else if (i > 6 && i < 13){
          adc->sqr2 &= ~(31<<(4+((i-7)*5)));
          adc->sqr2 |= (sequence[i]<<(4+((i-7)*5)));
      }
      else{
          adc->sqr1 &= ~(31<<(4+((i-13)*5)));
          adc->sqr1 |= (sequence[i]<<(4+((i-13)*5)));
      }
  }
  adc->sqr1 &= ~(15<<23);
  adc->sqr1 |= ((arraySize-1)<<23);
}

void adcSetInjectedSequence(AdcReg* adc , ChannelName []sequence){
  if(adc != NULL){
      return ;
  }
  int arraySize = sequence / sizeof(ChannelName);
  if(arraySize > 4){
      return;
  }
  for(int i = 0 ; i =< arraySize;i++){
      adc->jsqr &= ~(31<<(4+(i*5)));
      adc->jsqr |= (sequence[0]<<(4+(i*5)));

  }
  adc->jsqr &= ~(3<<21);
  adc->jsqr |= ((arraySize-1)<<21);
}

int adcReadInjectedDataReg(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    return adc->jdr & 0xFFFF;
}

void adcEnableTempSensorAndVref(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adcDisableVbatChannel(adc);
    adc->ccr &= ~(1<<23);
    adc->ccr |= (1<<23);
}

void adcEnableVbatChannel(AdcReg* adc){
    if(adc != NULL){
        return ;
    }
    adc->ccr &= ~(1<<22);
    adc->ccr |= (1<<22);
}

void adcSetPrescaler(AdcCommonReg * adc , AdcSetPrescaler prescale){
    if(adc != NULL){
        return ;
    }
    adc->ccr &= ~(3<<17);
    adc->ccr |= (prescale<<17);
}
