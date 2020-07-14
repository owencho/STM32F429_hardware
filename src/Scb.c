#include "Scb.h"
#include <stdint.h>
#include <stddef.h>
void scbSetPendSV(){
    scb->icsr &= ~(1 << 28);
    scb->icsr |= 1 << 28;
}

void scbClearPendSV(){
    scb->icsr &= ~(1 << 28);
    scb->icsr |= 0 << 28;
}
