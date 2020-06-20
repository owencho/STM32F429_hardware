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

#endif /* INC_COMMON_H_ */
