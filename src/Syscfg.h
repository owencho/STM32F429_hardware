#ifndef SYSCFG_H
#define SYSCFG_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
typedef struct SyscfgRegs SyscfgRegs;
struct SyscfgRegs {
    IoRegister memrmp;
    IoRegister pmc;
    IoRegister exticr[4];
    IoRegister cmpcr;
};
#define syscfg ((SyscfgRegs*)(SYSCFG_BASEADDRESS))
void syscfgExternalInterruptConfig(SyscfgRegs *syscfgLoc,ExternalPortInterruptName extiPort,int portName);
#endif // SYSCFG_H
