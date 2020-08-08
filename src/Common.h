/*
 * Common.h
 *
 *  Created on: Jun 11, 2020
 *      Author: Owen
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

typedef volatile uint32_t IoRegister;
typedef enum{
	PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7,
	PIN_8,PIN_9,PIN_10,PIN_11,PIN_12,PIN_13,PIN_14,PIN_15,
} PinNumber;

typedef enum{
	 PORT_A,PORT_B,PORT_C,PORT_D,PORT_E,PORT_F,PORT_G,PORT_H,
   PORT_I,PORT_J,PORT_K,
} PortName;

typedef enum{
	EXTI_0,EXTI_1,EXTI_2,EXTI_3,EXTI_4,EXTI_5,EXTI_6,EXTI_7,
	EXTI_8,EXTI_9,EXTI_10,EXTI_11,EXTI_12,EXTI_13,EXTI_14,EXTI_15,
}ExternalPortInterruptName;

typedef enum{
	DISABLE_MODE , ENABLE_MODE
}EnableDisable;

typedef enum{
	 CHANNEL_0,CHANNEL_1,CHANNEL_2,CHANNEL_3,CHANNEL_4,CHANNEL_5,
	 CHANNEL_6,CHANNEL_7,CHANNEL_8,CHANNEL_9,CHANNEL_10,CHANNEL_11,
	 CHANNEL_12,CHANNEL_13,CHANNEL_14,CHANNEL_15,CHANNEL_16,CHANNEL_17,
	 CHANNEL_18 ,END_OF_CHANNEL_SEQ
} ChannelName;

typedef enum{
	 T_DETECTION_DISABLED,T_DETECTION_RISING,T_DETECTION_FALLING,
   T_DETECTION_BOTH_EDGE,
} TriggerDetection;

typedef enum{
	 SPI1,SPI2,SPI3,SPI4,SPI5,SPI6
} SpiName;
#endif /* INC_COMMON_H_ */
