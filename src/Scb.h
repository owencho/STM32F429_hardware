#ifndef SCB_H
#define SCB_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
typedef struct ScbReg ScbReg;
struct ScbReg {
    IoRegister cpuid;
    IoRegister icsr;
    IoRegister vtor;
    IoRegister aircr;
    IoRegister scr;
    IoRegister ccr;
    IoRegister shpr1;
    IoRegister shpr2;
    IoRegister shpr3;
    IoRegister shcsr;
    IoRegister cfsr;
    IoRegister hfsr;
    IoRegister mmar;
    IoRegister bfar;
    IoRegister afsr;
};

#define scb ((ScbReg*)(SCB_BASEADDRESS))

void scbSetPendSV();
void scbClearPendSV();


#endif // SCB_H
