#include "Syscfg.h"
#include <stddef.h>
#include "Exception.h"
#include "CException.h"
#include "CExceptionConfig.h"
#include "STM32Error.h"

int arrayNumber;
int shiftLocation;
void syscfgExternalInterruptConfig(SyscfgRegs *syscfgLoc,ExternalPortInterruptName extiPort,int portName){
		if(syscfgLoc==NULL){
				throwException(SYSCFG_REG_INPUT_NULL,"SYSCFG register input is NULL");
		}
		else if(extiPort < EXTI_0 || extiPort > EXTI_15 ){
				throwException(SYSCFG_INVALID_EXTI_PORT,"SYSCFG register input is NULL");
		}
		else if(portName < PORT_A || portName > PORT_I ){
				throwException(SYSCFG_INVALID_PORT,"Invalid input exti port");
		}
		else if(extiPort > EXTI_11 || extiPort == PORT_I  ){
				throwException(SYSCFG_ERROR_CONFIG, "PORT I is not available on EXTI 12-15");
		}

		arrayNumber = extiPort >> 2 ;
		shiftLocation = ((extiPort - (arrayNumber <<2 )) <<2);
		syscfgLoc->exticr[arrayNumber] |= portName << shiftLocation ;
}
