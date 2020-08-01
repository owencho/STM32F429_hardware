#include "unity.h"
#include "BaseAddress.h"
#include "Common.h"
#include "Scb.h"
#include "ExceptionTestSupport.h"
ScbReg fakeScb;
void setUp(void){
    int i;
    char * ptr =(char*)&fakeScb;
    for(i =0; i< sizeof(ScbReg);i++)
        ptr[i] = 0;
}

void tearDown(void){}

uintptr_t getScbBaseAddress(){
    return (uintptr_t)&fakeScb;
}

void test_Scb_scbSetPendSV(void){
    scbSetPendSV();
    TEST_ASSERT_EQUAL(1<<28,fakeScb.icsr);
}

void test_Scb_scbClearPendSV(void){
    scbClearPendSV();
    TEST_ASSERT_EQUAL(0<<28,fakeScb.icsr);
}
