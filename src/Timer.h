#ifndef TIMER_H
#define TIMER_H

typedef enum{
  	UIF_FLAG,CC1IF_FLAG,CC2IF_FLAG,CC3IF_FLAG,CC4IF_FLAG,COMIF_FLAG,TIF_FLAG,
    BIF_FLAG,TIMER_RESERVED_FLAG,CC1OF_FLAG,CC2OF_FLAG,CC3OF_FLAG,CC4OF_FLAG,
} TimerFlag;

typedef enum{
    UG_EGR,CC1G_EGR,CC2G_EGR,CC3G_EGR,CC4G_EGR,COMG_EGR,TG_EGR,BG_EGR
} TimerEventGeneration;

typedef struct TimerRegs TimerRegs;
struct TimerRegs {
    IoRegister cr1;
    IoRegister cr2;
    IoRegister smcr;
    IoRegister dier;
    IoRegister sr;
    IoRegister egr;
    IoRegister ccmr1;
    IoRegister ccmr2;
    IoRegister ccer;
    IoRegister cnt;
    IoRegister psc;
    IoRegister arr;
    IoRegister rcr;
    IoRegister ccr1;
    IoRegister ccr2;
    IoRegister ccr3;
    IoRegister ccr4;
    IoRegister bdtr;
    IoRegister dcr;
    IoRegister dmar;
};
//CR1
#define TIMER_CLK_DIV_1 (0ULL<<8)
#define TIMER_CLK_DIV_2 (1ULL<<8)
#define TIMER_CLK_DIV_4 (2ULL<<8)

#define APRE_ENABLE (1ULL<<7)
#define APRE_DISABLE (0ULL<<7)

#define TIMER_EDGE_ALIGNED (0ULL<<5)
#define TIMER_CENTER_ALIGNED_1 (1ULL<<5)
#define TIMER_CENTER_ALIGNED_2 (2ULL<<5)
#define TIMER_CENTER_ALIGNED_3 (3ULL<<5)

#define TIMER_UP_COUNT (0ULL<<4)
#define TIMER_DOWN_COUNT (1ULL<<4)

#define TIMER_ONE_PULSE_ENABLE (1ULL<<3)
#define TIMER_ONE_PULSE_DISABLE (0ULL<<3)

#define TIMER_URS_ENABLE (1ULL<<2)
#define TIMER_URS_DISABLE (0ULL<<2)

#define TIMER_UEV_ENABLE (0ULL<<1)
#define TIMER_UEV_DISABLE (1ULL<<1)

#define TIMER_COUNTER_ENABLE (1ULL<<0)
#define TIMER_COUNTER_DISABLE (1ULL<<0)

//CR2
#define OC4_OUT_HIGH (1ULL<<14)
#define OC4_OUT_LOW (0ULL<<14)

#define OC3N_OUT_HIGH (1ULL<<13)
#define OC3N_OUT_LOW (0ULL<<13)

#define OC3_OUT_HIGH (1ULL<<12)
#define OC3_OUT_LOW (0ULL<<12)

#define OC2N_OUT_HIGH (1ULL<<11)
#define OC2N_OUT_LOW (0ULL<<11)

#define OC2_OUT_HIGH (1ULL<<10)
#define OC2_OUT_LOW (0ULL<<10)

#define OC1N_OUT_HIGH (1ULL<<9)
#define OC1N_OUT_LOW (0ULL<<9)

#define OC1_OUT_HIGH (1ULL<<8)
#define OC1_OUT_LOW (0ULL<<8)

#define T1_CH1_SELECT (0ULL<<7)
#define T1_XOR_SELECT (1ULL<<7)

#define MASTER_MODE_RESET (0ULL<<4)
#define MASTER_MODE_ENABLE (1ULL<<4)
#define MASTER_MODE_UPDATE (2ULL<<4)
#define MASTER_MODE_COMP_PULSE (3ULL<<4)
#define MASTER_MODE_COMP_OC1REF (4ULL<<4)
#define MASTER_MODE_COMP_OC2REF (5ULL<<4)
#define MASTER_MODE_COMP_OC3REF (6ULL<<4)
#define MASTER_MODE_COMP_OC4REF (7ULL<<4)

#define TIMER_CC_EVT_OCCUR (0ULL<<3)
#define TIMER_CC_DMA_UPDATE_EVT (1ULL<<3)

#define CCUS_ENABLE (0ULL<<2)
#define CCUS_ENABLE (1ULL<<2)

#define TIMER_CC_PRELOADED_DISABLE (1ULL<<0)
#define TIMER_CC_PRELOADED_ENABLE (0ULL<<0)

//SMCR
#define SMS_DISABLED (0<<0)
#define SMS_ENCODER_M1 (1<<0)
#define SMS_ENCODER_M2 (2<<0)
#define SMS_ENCODER_M3 (3<<0)
#define SMS_RESET_M (4<<0)
#define SMS_GATED_M (5<<0)
#define SMS_TRIGGER_M (6<<0)
#define SMS_EXT_CLK_M1 (7<<0)

#define TRIGGER_INT_0 (0<<4)
#define TRIGGER_INT_1 (1<<4)
#define TRIGGER_INT_2 (2<<4)
#define TRIGGER_INT_3 (3<<4)
#define TRIGGER_EDGE_T1 (4<<4)
#define TRIGGER_FIL_T1 (5<<4)
#define TRIGGER_FIL_T2 (6<<4)
#define TRIGGER_EXT_INT (7<<4)

#define MASTER_MODE (1<<7)
#define SLAVE_MODE (0<<7)

#define EXT_NO_FILER (0<<8)
#define EXT_TRIG_FILTER_FCK_2N (1<<8)
#define EXT_TRIG_FILTER_FCK_4N (2<<8)
#define EXT_TRIG_FILTER_FCK_8N (3<<8)
#define EXT_TRIG_FILTER_FDTS_2_6N (4<<8)
#define EXT_TRIG_FILTER_FDTS_2_8N (5<<8)
#define EXT_TRIG_FILTER_FDTS_4_6N (6<<8)
#define EXT_TRIG_FILTER_FDTS_4_8N (7<<8)
#define EXT_TRIG_FILTER_FDTS_8_6N (8<<8)
#define EXT_TRIG_FILTER_FDTS_8_8N (9<<8)
#define EXT_TRIG_FILTER_FDTS_16_5N (10<<8)
#define EXT_TRIG_FILTER_FDTS_16_6N (11<<8)
#define EXT_TRIG_FILTER_FDTS_16_8N (12<<8)
#define EXT_TRIG_FILTER_FDTS_32_5N (13<<8)
#define EXT_TRIG_FILTER_FDTS_32_6N (14<<8)
#define EXT_TRIG_FILTER_FDTS_32_8N (15<<8)

#define EXT_TRIG_PRESCALE_OFF (0<<12)
#define EXT_TRIG_PRESCALE_DIV2 (1<<12)
#define EXT_TRIG_PRESCALE_DIV4 (2<<12)
#define EXT_TRIG_PRESCALE_DIV8 (3<<12)

#define ENABLE_EXT_CLK (1<<14)
#define DISABLE_EXT_CLK (0<<14)

#define FALLING_EXT_TRIG_POLARITY (1<<15)
#define RISING_EXT_TRIG_POLARITY (0<<15)

// interrupt enable
#define TRIG_DMA_REQ_ENABLE (1<<14)
#define TRIG_DMA_REQ_DISABLE (0<<14)

#define COM_DMA_REQ_ENABLE (1<<13)
#define COM_DMA_REQ_DISABLE (0<<13)

#define CC4_DMA_REQ_ENABLE (1<<12)
#define CC4_DMA_REQ_DISABLE (0<<12)

#define CC3_DMA_REQ_ENABLE (1<<11)
#define CC3_DMA_REQ_DISABLE (0<<11)

#define CC2_DMA_REQ_ENABLE (1<<10)
#define CC2_DMA_REQ_DISABLE (0<<10)

#define CC1_DMA_REQ_ENABLE (1<<9)
#define CC1_DMA_REQ_DISABLE (0<<9)

#define UPDATE_DMA_REQ_ENABLE (1<<8)
#define UPDATE_DMA_REQ_DISABLE (0<<8)

#define BREAK_INT_ENABLE (1<<7)
#define BREAK_INT_DISABLE (0<<7)

#define TRIG_INT_ENABLE (1<<6)
#define TRIG_INT_DISABLE (0<<6)

#define COM_INT_ENABLE (1<<5)
#define COM_INT_DISABLE (0<<5)

#define CC4_INT_ENABLE (1<<4)
#define CC4_INT_DISABLE (0<<4)

#define CC3_INT_ENABLE (1<<3)
#define CC3_INT_DISABLE (0<<3)

#define CC2_INT_ENABLE (1<<2)
#define CC2_INT_DISABLE (0<<2)

#define CC1_INT_ENABLE (1<<1)
#define CC1_INT_DISABLE (0<<1)

#define UIE_INT_ENABLE (1<<0)
#define UIE_INT_DISABLE (0<<0)

//function
void resetFlag(TimerRegs * regs , TimerFlag flag);
//void timerWriteCounter(TimerRegs * regs , int count);
int timerReadCounter(TimerRegs * regs);

void timerWritePrescaler(TimerRegs * regs , int prescaler);
int timerReadPrescaler(TimerRegs * regs);

void timerWriteAutoReloadReg(TimerRegs * regs , int aReloadValue);
int timerReadAutoReloadReg(TimerRegs * regs);

void timerWriteRepetitionCounter(TimerRegs * regs , int counter);
int timerReadRepetitionCounter(TimerRegs * regs);

void timerWriteCapComReg1(TimerRegs * regs , int count);
int timerReadCapComReg1(TimerRegs * regs );

void timerWriteCapComReg2(TimerRegs * regs , int count);
int timerReadCapComReg2(TimerRegs * regs);

void timerWriteCapComReg3(TimerRegs * regs , int count);
int timerReadCapComReg3(TimerRegs * regs);

void timerWriteCapComReg4(TimerRegs * regs , int count);
int timerReadCapComReg4(TimerRegs * regs );
#endif // TIMER_H
