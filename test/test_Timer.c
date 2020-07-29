#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Timer.h"
#include "TimerMacro.h"
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"
CEXCEPTION_T ex;

TimerRegs timerRegs;

#define BASE_CONTROL_TEST (TIMER_CLK_DIV_1|ARR_ENABLE|TIMER_ONE_PULSE_ENABLE|T1_XOR_SELECT)
#define SM_BASE_TEST (SMS_RESET_M |TRIGGER_INT_1 | SLAVE_MODE | EXT_NO_FILER | ENABLE_EXT_CLK |EXT_TRIG_PRESCALE_DIV2)
#define CCMR_BASE_TEST (CC1_INPUT_IC1_MAP_TI1 |OC1_FAST_ENABLE | CC3_INPUT_IC1_MAP_TI4 | OC3_CLEAR_ENABLE)
#define CCER_BASE_TEST (OC1_ENABLE |OC1N_ENABLE | OC3N_ENABLE)

void setUp(void){
    int i;
    char * ptr =(char*)&timerRegs;
    for(i =0; i< sizeof(TimerRegs);i++)
        ptr[i] = 0;
}

void tearDown(void){}

void test_Timer_timerSetControlRegister_input_NULL(void){
    Try{
        timerSetControlRegister(NULL,BASE_CONTROL_TEST);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerSetControlRegister_with_base(void){
    Try{
        timerSetControlRegister(&timerRegs,BASE_CONTROL_TEST);
        TEST_ASSERT_EQUAL((1<<7)|(1<<3),timerRegs.cr1);
        TEST_ASSERT_EQUAL((1<<7),timerRegs.cr2);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetControlRegister_with_extra_control(void){
    Try{
        timerSetControlRegister(&timerRegs,BASE_CONTROL_TEST| TIMER_CC_DMA_UPDATE_EVT);
        TEST_ASSERT_EQUAL((1<<7)|(1<<3),timerRegs.cr1);
        TEST_ASSERT_EQUAL((1<<7)|(1<<3),timerRegs.cr2);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetSlaveMasterRegister_input_NULL(void){
    Try{
        timerSetSlaveMasterRegister(NULL,SM_BASE_TEST);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}
/*
#define SM_BASE_TEST (SMS_RESET_M |TRIGGER_INT_1 | SLAVE_MODE |
      EXT_TRIG_FILTER_FCK_2N | ENABLE_EXT_CLK |EXT_TRIG_PRESCALE_DIV2)
      */
void test_Timer_timerSetSlaveMasterRegister_with_base(void){
    Try{
        timerSetSlaveMasterRegister(&timerRegs,SM_BASE_TEST);
        TEST_ASSERT_EQUAL((1<<14)|(1<<12)|(0<<8)|(1<<4)|(4<<0),timerRegs.smcr);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetSlaveMasterRegister_with_extra_control(void){
    Try{
        timerSetSlaveMasterRegister(&timerRegs,SM_BASE_TEST|EXT_TRIG_FILTER_FDTS_16_8N);
        TEST_ASSERT_EQUAL((1<<14)|(1<<12)|(12<<8)|(1<<4)|(4<<0),timerRegs.smcr);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetCompareCaptureModeRegister_input_NULL(void){
    Try{
        timerSetCompareCaptureModeRegister(NULL,CCMR_BASE_TEST);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerSetCompareCaptureModeRegister_with_base(void){
    Try{
        timerSetCompareCaptureModeRegister(&timerRegs,CCMR_BASE_TEST);
        TEST_ASSERT_EQUAL((1<<2)|(1<<0),timerRegs.ccmr1);
        TEST_ASSERT_EQUAL((1<<7)|(2<<0),timerRegs.ccmr2);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetCompareCaptureModeRegister_with_extra_control(void){
    Try{
        timerSetCompareCaptureModeRegister(&timerRegs,CCMR_BASE_TEST|IC3_FILTER_FCK_2N);
        TEST_ASSERT_EQUAL((1<<2)|(1<<0),timerRegs.ccmr1);
        TEST_ASSERT_EQUAL((1<<4)|(1<<7)|(2<<0),timerRegs.ccmr2);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetCompareCaptureEnableRegister_input_NULL(void){
    Try{
        timerSetCompareCaptureEnableRegister(NULL,CCMR_BASE_TEST);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerSetCompareCaptureEnableRegister_with_base(void){
    Try{
        timerSetCompareCaptureEnableRegister(&timerRegs,CCER_BASE_TEST);
        TEST_ASSERT_EQUAL((OC1_ENABLE |OC1N_ENABLE | OC3N_ENABLE),timerRegs.ccer);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerSetCompareCaptureEnableRegister_with_extra_control(void){
    Try{
        timerSetCompareCaptureEnableRegister(&timerRegs,CCER_BASE_TEST|OC3N_ACTIVEHIGH);
        TEST_ASSERT_EQUAL((OC1_ENABLE |OC1N_ENABLE | OC3N_ENABLE|OC3N_ACTIVEHIGH),timerRegs.ccer);

    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerEnableInterrupt_input_NULL(void){
    Try{
        timerEnableInterrupt(NULL,UIF_FLAG);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerEnableInterrupt_with_one(void){
    Try{
        timerEnableInterrupt(&timerRegs,CC1IF_FLAG);
        TEST_ASSERT_EQUAL((1<<CC1IF_FLAG),timerRegs.dier);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerEnableInterrupt_with_two(void){
    Try{
        timerEnableInterrupt(&timerRegs,CC1IF_FLAG);
        timerEnableInterrupt(&timerRegs,CC1OF_FLAG);
        TEST_ASSERT_EQUAL((1<<CC1IF_FLAG)|(1<<CC1OF_FLAG),timerRegs.dier);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}


void test_Timer_timerDisableInterrupt_input_NULL(void){
    Try{
        timerDisableInterrupt(NULL,UIF_FLAG);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerDisableInterrupt_with_one(void){
    Try{
        timerEnableInterrupt(&timerRegs,CC1IF_FLAG);
        TEST_ASSERT_EQUAL((1<<CC1IF_FLAG),timerRegs.dier);
        timerDisableInterrupt(&timerRegs,CC1IF_FLAG);
        TEST_ASSERT_EQUAL(0,timerRegs.dier);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerDisableInterrupt_with_two(void){
    Try{
        timerEnableInterrupt(&timerRegs,CC1IF_FLAG);
        timerEnableInterrupt(&timerRegs,CC1OF_FLAG);
        TEST_ASSERT_EQUAL((1<<CC1IF_FLAG)|(1<<CC1OF_FLAG),timerRegs.dier);
        timerDisableInterrupt(&timerRegs,CC1IF_FLAG);
        TEST_ASSERT_EQUAL((1<<CC1OF_FLAG),timerRegs.dier);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerEventGeneration_input_NULL(void){
    Try{
        timerEventGeneration(NULL,CC1G_EGR);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerEventGeneration_with_one(void){
    Try{
        timerEventGeneration(&timerRegs,CC2G_EGR);
        TEST_ASSERT_EQUAL((1<<CC2G_EGR),timerRegs.egr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerEventGeneration_with_two(void){
    Try{
      timerEventGeneration(&timerRegs,CC2G_EGR);
      TEST_ASSERT_EQUAL((1<<CC2G_EGR),timerRegs.egr);
      timerEventGeneration(&timerRegs,CC4G_EGR);
      TEST_ASSERT_EQUAL((1<<CC2G_EGR)|(1<<CC4G_EGR),timerRegs.egr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerResetFlags_input_NULL(void){
    Try{
        timerResetFlags(NULL,CC1IF_FLAG);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerResetFlags_with_one(void){
    Try{
        timerRegs.sr = (1<<CC1IF_FLAG);
        timerResetFlags(&timerRegs,CC1IF_FLAG);
        TEST_ASSERT_EQUAL(0,timerRegs.sr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerResetFlags_with_two(void){
    Try{
      timerRegs.sr = (1<<CC1IF_FLAG)|(1<<CC1OF_FLAG);
      timerResetFlags(&timerRegs,CC1IF_FLAG);
      TEST_ASSERT_EQUAL((1<<CC1OF_FLAG),timerRegs.sr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadCounter_input_NULL(void){
    Try{
        timerReadCounter(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadCounter_with_one(void){
    Try{
        timerRegs.cnt = 0x1234;
        TEST_ASSERT_EQUAL(0x1234,timerReadCounter(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWritePrescaler_input_NULL(void){
    Try{
        timerWritePrescaler(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWritePrescaler_with_one(void){
    Try{
        timerWritePrescaler(&timerRegs,0x1234);
        TEST_ASSERT_EQUAL(0x1234,timerRegs.psc);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadPrescaler_input_NULL(void){
    Try{
        timerReadPrescaler(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadPrescaler_with_one(void){
    Try{
        timerRegs.psc = 0x1134;
        TEST_ASSERT_EQUAL(0x1134,timerReadPrescaler(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteAutoReloadReg_input_NULL(void){
    Try{
        timerWriteAutoReloadReg(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteAutoReloadReg_with_one(void){
    Try{
        timerWriteAutoReloadReg(&timerRegs,0xAAA1);
        TEST_ASSERT_EQUAL(0xAAA1,timerRegs.arr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadAutoReloadReg_input_NULL(void){
    Try{
        timerReadAutoReloadReg(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadAutoReloadReg_with_one(void){
    Try{
        timerRegs.arr = 0x1A34;
        TEST_ASSERT_EQUAL(0x1A34,timerReadAutoReloadReg(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteRepetitionCounter_input_NULL(void){
    Try{
        timerWriteRepetitionCounter(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteRepetitionCounter_with_one(void){
    Try{
        timerWriteRepetitionCounter(&timerRegs,0x12);
        TEST_ASSERT_EQUAL(0x12,timerRegs.rcr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadRepetitionCounter_input_NULL(void){
    Try{
        timerReadPrescaler(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadRepetitionCounter_with_one(void){
    Try{
        timerRegs.rcr = 0x12;
        TEST_ASSERT_EQUAL(0x12,timerReadRepetitionCounter(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteCapComReg1_input_NULL(void){
    Try{
        timerWriteCapComReg1(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteCapComReg1_with_one(void){
    Try{
        timerWriteCapComReg1(&timerRegs,0x1332);
        TEST_ASSERT_EQUAL(0x1332,timerRegs.ccr1);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadCapComReg1_input_NULL(void){
    Try{
        timerReadCapComReg1(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadCapComReg1_with_one(void){
    Try{
        timerRegs.ccr1 = 0xAA2;
        TEST_ASSERT_EQUAL(0xAA2,timerReadCapComReg1(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteCapComReg2_input_NULL(void){
    Try{
        timerWriteCapComReg2(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteCapComReg2_with_one(void){
    Try{
        timerWriteCapComReg2(&timerRegs,0x1112);
        TEST_ASSERT_EQUAL(0x1112,timerRegs.ccr2);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadCapComReg2_input_NULL(void){
    Try{
        timerReadCapComReg2(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadCapComReg2_with_one(void){
    Try{
        timerRegs.ccr2 = 0xA1A2;
        TEST_ASSERT_EQUAL(0xA1A2,timerReadCapComReg2(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteCapComReg3_input_NULL(void){
    Try{
        timerWriteCapComReg3(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteCapComReg3_with_one(void){
    Try{
        timerWriteCapComReg3(&timerRegs,0x1332);
        TEST_ASSERT_EQUAL(0x1332,timerRegs.ccr3);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadCapComReg3_input_NULL(void){
    Try{
        timerReadCapComReg3(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadCapComReg3_with_one(void){
    Try{
        timerRegs.ccr3 = 0xAA2;
        TEST_ASSERT_EQUAL(0xAA2,timerReadCapComReg3(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerWriteCapComReg4_input_NULL(void){
    Try{
        timerWriteCapComReg4(NULL,0x1234);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerWriteCapComReg4_with_one(void){
    Try{
        timerWriteCapComReg4(&timerRegs,0x1332);
        TEST_ASSERT_EQUAL(0x1332,timerRegs.ccr4);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerReadCapComReg4_input_NULL(void){
    Try{
        timerReadCapComReg4(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerReadCapComReg4_with_one(void){
    Try{
        timerRegs.ccr4 = 0xA1A2;
        TEST_ASSERT_EQUAL(0xA1A2,timerReadCapComReg4(&timerRegs));
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerMainOutputEnable_input_NULL(void){
    Try{
        timerMainOutputEnable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerMainOutputEnable_with_one(void){
    Try{
        timerMainOutputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<15,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerMainOutputDisable_input_NULL(void){
    Try{
        timerMainOutputDisable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerMainOutputDisable_with_one(void){
    Try{
        timerMainOutputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<15,timerRegs.bdtr);
        timerMainOutputDisable(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerAutomaticOutputEnable_input_NULL(void){
    Try{
        timerAutomaticOutputEnable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerAutomaticOutputEnable_with_one(void){
    Try{
        timerAutomaticOutputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<14,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerAutomaticOutputDisable_input_NULL(void){
    Try{
        timerAutomaticOutputDisable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerAutomaticOutputDisable_with_one(void){
    Try{
        timerAutomaticOutputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<14,timerRegs.bdtr);
        timerAutomaticOutputDisable(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerBreakInputEnable_input_NULL(void){
    Try{
        timerBreakInputEnable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerBreakInputEnable_with_one(void){
    Try{
        timerBreakInputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<12,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerBreakInputDisable_input_NULL(void){
    Try{
        timerBreakInputDisable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerBreakInputDisable_with_one(void){
    Try{
        timerBreakInputEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<12,timerRegs.bdtr);
        timerBreakInputDisable(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerBreakInputSetActiveHigh_input_NULL(void){
    Try{
        timerBreakInputSetActiveHigh(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerBreakInputSetActiveHigh_with_one(void){
    Try{
        timerBreakInputSetActiveHigh(&timerRegs);
        TEST_ASSERT_EQUAL(1<<13,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerBreakInputSetActiveLow_input_NULL(void){
    Try{
        timerBreakInputSetActiveLow(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerBreakInputSetActiveLow_with_one(void){
    Try{
        timerBreakInputSetActiveHigh(&timerRegs);
        TEST_ASSERT_EQUAL(1<<13,timerRegs.bdtr);
        timerBreakInputSetActiveLow(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerOSSIdleEnable_input_NULL(void){
    Try{
        timerOSSIdleEnable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerOSSIdleEnable_with_one(void){
    Try{
        timerOSSIdleEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<10,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerOSSIdleDisable_input_NULL(void){
    Try{
        timerOSSIdleDisable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerOSSIdleDisable_with_one(void){
    Try{
        timerOSSIdleEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<10,timerRegs.bdtr);
        timerOSSIdleDisable(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerOSSRunEnable_input_NULL(void){
    Try{
        timerOSSRunEnable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerOSSRunEnable_with_one(void){
    Try{
        timerOSSRunEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<11,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_timerOSSRunDisable_input_NULL(void){
    Try{
        timerOSSRunDisable(NULL);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_timerOSSRunDisable_with_one(void){
    Try{
        timerOSSRunEnable(&timerRegs);
        TEST_ASSERT_EQUAL(1<<11,timerRegs.bdtr);
        timerOSSRunDisable(&timerRegs);
        TEST_ASSERT_EQUAL(0,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_TimerLockConfiguration_input_NULL(void){
    Try{
        TimerLockConfiguration(NULL,TIMER_LOCK_OFF);
        TEST_FAIL_MESSAGE("Expect exception to be thrown");

    }
    Catch(ex){
        dumpException(ex);
        TEST_ASSERT_EQUAL(TIMER_REG_INPUT_NULL,ex->errorCode);
    }
}

void test_Timer_TimerLockConfiguration_with_one(void){
    Try{
        TimerLockConfiguration(&timerRegs,TIMER_LOCK_L1);
        TEST_ASSERT_EQUAL(1<<8,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}

void test_Timer_TimerLockConfiguration_with_L3(void){
    Try{
        TimerLockConfiguration(&timerRegs,TIMER_LOCK_L3);
        TEST_ASSERT_EQUAL(3<<8,timerRegs.bdtr);
    }
    Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Expect exception not to be thrown");
    }
}
