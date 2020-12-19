#include "unity.h"
#include "GPIO.h"
#include "MK20DX256.h"

void setUp(void)
{
    GPIO_init();
}

void tearDown(void)
{

}
/*=====================================SetPinDirectionAsOutput==========================*/
void test_GPIO_SetPinDirectionAsOutput_should_setPinDirectionToOutput()
{
    //init state as all pins are input
    PORTC.PDDR = 0;

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsOutput(0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PDDR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsOutput(20));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(20), PORTC.PDDR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsOutput(31));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(20) | BIT_TO_MASK(31), PORTC.PDDR);
}
void test_GPIO_SetPinDirectionAsOutput_should_return_NOK_when_outOfRangePinPassedAsInput()
{
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsOutput(-1));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsOutput(32));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsOutput(-127));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsOutput(128));
}

/*=====================================GPIO_SetPinDirectionAsInput==========================*/
void test_GPIO_SetPinDirectionAsInput_should_setPinDirectionToInput()
{
    
    //init state as all pins are input
    PORTC.PDDR = 0xFFFFFFFF;

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsInput(0));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)), PORTC.PDDR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsInput(20));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(20)), PORTC.PDDR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPinDirectionAsInput(31));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(20) | BIT_TO_MASK(31)), PORTC.PDDR);
}

void test_GPIO_SetPinDirectionAsInput_should_return_NOK_when_outOfRangePinPassedAsInput()
{
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsInput(-1));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsInput(32));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsInput(-127));
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPinDirectionAsInput(128));
}

/*=====================================GPIO_ReadPin==========================*/
void test_GPIO_ReadPin_should_readPinValue()
{
    PORTC.PDIR = 0xffffffff;
    BOOL state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(0,&state));
    TEST_ASSERT_TRUE(state);

    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(20,&state));
    TEST_ASSERT_TRUE(state);

    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(31,&state));
    TEST_ASSERT_TRUE(state);


    PORTC.PDIR = 0x00000000;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(0,&state));
    TEST_ASSERT_FALSE(state);

    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(20,&state));
    TEST_ASSERT_FALSE(state);

    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPin(31,&state));
    TEST_ASSERT_FALSE(state);
}

void test_GPIO_ReadPin_should_return_NOK_when_outOfRangePinPassedAsInput()
{
    PORTC.PDIR = 0xf0f0f0f0;
    BOOL state = 0;

    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_ReadPin(32,&state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDIR);

    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_ReadPin(-1,&state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDIR);
}


void test_GPIO_ReadPin_should_return_NOK_when_statePointerIsNULL()
{
    PORTC.PDIR = 0xf0f0f0f0;

    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_ReadPin(3,NULL));
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDIR);

}
/*=====================================GPIO_SetPin==========================*/
void test_GPIO_ReadPin_should_SetPinToGivenValue()
{
    PORTC.PDOR = 0xFFFFFFFF;
    BOOL state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(0,state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(~BIT_TO_MASK(0),PORTC.PDOR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(20,state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)|BIT_TO_MASK(20)),PORTC.PDOR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(31,state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)|BIT_TO_MASK(20)|BIT_TO_MASK(31)),PORTC.PDOR);

    PORTC.PDOR = 0x00000000;
    state = 1;
    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(0,state));
    TEST_ASSERT_TRUE(state);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0),PORTC.PDOR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(20,state));
    TEST_ASSERT_TRUE(state);
    TEST_ASSERT_EQUAL_HEX32((BIT_TO_MASK(0)|BIT_TO_MASK(20)),PORTC.PDOR);

    TEST_ASSERT_EQUAL_INT(0,GPIO_SetPin(31,state));
    TEST_ASSERT_TRUE(state);
    TEST_ASSERT_EQUAL_HEX32((BIT_TO_MASK(0)|BIT_TO_MASK(20)|BIT_TO_MASK(31)),PORTC.PDOR);
}


void test_GPIO_SetPin_should_return_NOK_when_outOfRangePinPassedAsInput()
{
    PORTC.PDOR = 0xf0f0f0f0;
    BOOL state = 0;

    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPin(32,state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDOR);

    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_SetPin(-1,state));
    TEST_ASSERT_FALSE(state);
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDOR);
}


/*=====================================GPIO_ReadPort==========================*/
void test_GPIO_ReadPort_should_ReturnPortValue()
{
    PORTC.PDIR = 0xffffffff;
    BOOL state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTC.PDIR = 0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTC.PDIR = 0xf0f0f0f0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

     PORTA.PDIR = 0xffffffff;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTA.PDIR = 0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTA.PDIR = 0xf0f0f0f0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);


    PORTB.PDIR = 0xffffffff;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTB.PDIR = 0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);

    PORTB.PDIR = 0xf0f0f0f0;
    state = 0;
    TEST_ASSERT_EQUAL_INT(0,GPIO_ReadPort(PORTC,&state));
    TEST_ASSERT_EQUAL_HEX32(PORTC.PDIR,state);
}

void test_GPIO_ReadPort_should_return_NOK_when_outputValueIsNull()
{
    TEST_ASSERT_EQUAL_INT(GPIO_NOK,GPIO_ReadPort(PORTC,NULL));
}


void test_GPIO_init_should_setRegistersToInitialConfigration()
{
    PORTC.PDDR = 0;
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;

    GPIO_init();
    TEST_ASSERT_EQUAL_HEX32(0xf0f0f0f0,PORTC.PDDR);
    TEST_ASSERT_EQUAL_HEX32(0x0f0f0f0f,PORTC.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0x0000ffff,PORTC.PCOR);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_GPIO_init_should_setRegistersToInitialConfigration);
    RUN_TEST(test_GPIO_SetPinDirectionAsOutput_should_setPinDirectionToOutput);
    RUN_TEST(test_GPIO_SetPinDirectionAsOutput_should_return_NOK_when_outOfRangePinPassedAsInput);
    RUN_TEST(test_GPIO_SetPinDirectionAsInput_should_setPinDirectionToInput);
    RUN_TEST(test_GPIO_SetPinDirectionAsInput_should_return_NOK_when_outOfRangePinPassedAsInput);
    RUN_TEST(test_GPIO_ReadPin_should_readPinValue);
    RUN_TEST(test_GPIO_ReadPin_should_return_NOK_when_outOfRangePinPassedAsInput);
    RUN_TEST(test_GPIO_ReadPin_should_SetPinToGivenValue);
    RUN_TEST(test_GPIO_ReadPin_should_return_NOK_when_statePointerIsNULL);
    RUN_TEST(test_GPIO_SetPin_should_return_NOK_when_outOfRangePinPassedAsInput);
    RUN_TEST(test_GPIO_ReadPort_should_ReturnPortValue);
    RUN_TEST(test_GPIO_ReadPort_should_return_NOK_when_outputValueIsNull);
    return UNITY_END();
}
