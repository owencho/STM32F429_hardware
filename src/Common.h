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
	PIN_16,PIN_17,PIN_18,PIN_19,PIN_20,PIN_21,PIN_22,PIN_23,
	PIN_24,PIN_25,PIN_26,PIN_27,PIN_28,PIN_29,PIN_30,PIN_31,
} PinNumber;

typedef enum{
	 PORT_A,PORT_B,PORT_C,PORT_D,PORT_E,PORT_F,PORT_G,PORT_H,
   PORT_I,PORT_J,PORT_K,
} PortName;

typedef enum{
	EXTI_0,EXTI_1,EXTI_2,EXTI_3,EXTI_4,EXTI_5,EXTI_6,EXTI_7,
	EXTI_8,EXTI_9,EXTI_10,EXTI_11,EXTI_12,EXTI_13,EXTI_14,EXTI_15,
}ExternalPortInterruptName;

#endif /* INC_COMMON_H_ */
