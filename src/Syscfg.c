#include "Syscfg.h"
#include <stddef.h>

int arrayNumber;
int shiftLocation;
void syscfgExternalInterruptConfig(SyscfgRegs *syscfgLoc,ExternalPortInterruptName extiPort,int portName){
		if(syscfgLoc==NULL){
				return ;
		}
		arrayNumber = extiPort >> 2 ;
		shiftLocation = ((extiPort - (arrayNumber <<2 )) <<2);
		syscfgLoc->exticr[arrayNumber] |= portName << shiftLocation ;
}
