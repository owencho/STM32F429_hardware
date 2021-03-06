#include "Exception.h"
#include "CException.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdarg.h>


void freeException(Exception *ex){
    if(ex)
        free(ex);
}

void throwException(uint32_t errorCode,char *errorMessage,...){
    int actualLength;
    char* buffer;
    Exception *exceptionPtr;

    va_list arg;
    va_start(arg, errorMessage);

    actualLength = vsnprintf(NULL,0, errorMessage, arg);
    buffer =malloc(actualLength + 1);
    vsnprintf(buffer,actualLength + 1, errorMessage, arg);
    va_end(arg);

    exceptionPtr = malloc(sizeof(Exception));
    exceptionPtr -> errorCode = errorCode;
    exceptionPtr -> errorMessage = buffer;
    Throw(exceptionPtr);
}
