/*
 * Gpio.h
 *
 *  Created on: Jun 10, 2020
 *      Author: owen
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"

typedef enum{
	LOW_SPEED,MEDIUM_SPEED,HIGH_SPEED,VERY_HI_SPEED,
} PinSpeed;

typedef enum{
	OPEN_DRAIN,PUSH_PULL,
} PinOutputType;

typedef enum{
	GPIO_IN,GPIO_OUT,GPIO_ALT,GPIO_ANALOG,
} PinMode;

typedef enum{
	NONE,PULL_UP,PULL_DOWN,
} PinPullUpDown;

typedef enum{
	AF0,AF1,AF2,AF3,AF4,AF5,AF6,AF7,
	AF8,AF9,AF10,AF11,AF12,AF13,AF14,AF15
} AlternateFunction;

typedef struct GpioRegs GpioRegs;
struct GpioRegs {
	IoRegister moder;
	IoRegister otyper;
	IoRegister ospeedr;
	IoRegister pupdr;
	IoRegister idr;
	IoRegister odr;
	IoRegister bsrr;
	IoRegister lckr;
	IoRegister afrl;
	IoRegister afrh;
};
#define gpioK (GpioRegs*)(GPIO_K)
#define gpioJ (GpioRegs*)(GPIO_J)
#define gpioI (GpioRegs*)(GPIO_I)
#define gpioH (GpioRegs*)(GPIO_H)
#define gpioG (GpioRegs*)(GPIO_G)
#define gpioF (GpioRegs*)(GPIO_F)
#define gpioE (GpioRegs*)(GPIO_E)
#define gpioD (GpioRegs*)(GPIO_D)
#define gpioC (GpioRegs*)(GPIO_C)
#define gpioB (GpioRegs*)(GPIO_B)
#define gpioA (GpioRegs*)(GPIO_A)

void gpioSetMode(GpioRegs *gpio , int pin , PinMode mode);
void gpioSetOutputType(GpioRegs *gpio , int pin ,PinOutputType type);
void gpioSetPinSpeed(GpioRegs *gpio , int pin , PinSpeed speed);
void gpioWriteBit(GpioRegs *gpio , int bitNumber , int value);
void gpioWrite(GpioRegs *gpio , int value);
int gpioReadBit(GpioRegs *gpio , int bitNumber );
void gpioToggleBit(GpioRegs *gpio , int bitNumber );
void gpioSetAlternateFunction(GpioRegs *gpio ,PinNumber pin ,AlternateFunction altFunction);
#endif /* INC_GPIO_H_ */
