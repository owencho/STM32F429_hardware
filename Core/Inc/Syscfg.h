#ifndef SYSCFG_H
#define SYSCFG_H
#include <stdint.h>
#include "BaseAddress.h"
#include "Common.h"
typedef struct SyscfgRegs SyscfgRegs;
struct SyscfgRegs {
    IoRegister MEMRMP;
    IoRegister PMC;
    IoRegister EXTICR[4];
    IoRegister CMPCR;
};
#define syscfg ((SyscfgRegs*)(SYSCFG_BASEADDRESS))
void syscfgExternalInterruptConfig(SyscfgRegs *syscfgLoc,int pin,int portName);

#endif // SYSCFG_H
