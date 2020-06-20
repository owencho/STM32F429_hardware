#include "Syscfg.h"

int arrayNumber;

void syscfgExternalInterruptConfig(SyscfgRegs *syscfgLoc,int pin,int portName){
		if(syscfgLoc==NULL)
				return 0;
		arrayNumber = portName >> 2 ;
		syscfgLoc->EXTICR[arrayNumber] |= portName << (pin - (arrayNumber << 2));
}
