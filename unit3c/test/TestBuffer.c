
#include "unity.h"
#include "Buffer.h"
#include "MK20DX256.h"

void setUp()
{
    bufferReset();
}

void tearDown()
{
    bufferReset();
}


void test_bufferWrite_insertOperation_should_allowTobufferReadSuccessfully()
{
    uint16_t vals[] ={0,0xffff,0xABCD,0x1234} ;
    uint16_t retVal;
    for(int i = 0 ; i < 4 ; i++)
    {
    TEST_ASSERT_EQUAL_HEX16(0,bufferWrite(vals[i]));
    TEST_ASSERT_EQUAL_HEX16(0,bufferRead(&retVal));
    TEST_ASSERT_EQUAL_HEX16(vals[i],retVal);

    }
    
}

void test_bufferRead_should_not_allow_readUnwritedIndx()
{
    uint16_t retVal;
    TEST_ASSERT_NOT_EQUAL(0,bufferRead(&retVal));
}

void test_bufferWrite_shouldnt_allowWriteIfBufferIsFull()
{
    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));

    TEST_ASSERT_NOT_EQUAL(0,bufferWrite(1000));
}

void test_BufferRead_should_readAllDataCorrectly_after_insertThemUsingBufferWrite()
{
    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));

    TEST_ASSERT_NOT_EQUAL(0,bufferWrite(1000));

    uint16_t retVal;
    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(0,bufferRead(&retVal));
        TEST_ASSERT_EQUAL_UINT16(i,retVal);
    }

        TEST_ASSERT_NOT_EQUAL(0,bufferRead(&retVal));
}

void BufferWriteThenReadArray(uint16_t * ar,uint16_t size)
{

    for(int i = 0 ; i < size ; i++)
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));


    uint16_t retVal;
    for(int i = 0 ; i < size ; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(0,bufferRead(&retVal));
        TEST_ASSERT_EQUAL_UINT16(i,retVal);
    }

    TEST_ASSERT_NOT_EQUAL(0,bufferRead(&retVal));
}

void test_BufferRead_should_allowReadAfter_BufferWrite_multiValue()
{
    uint16_t arr10[10] = {0xffff,0x0000,0x0f0f0,0xff00,0x00ff,0xabcd,0xbcde,0xcdef,0x1111,0x02020};
    BufferWriteThenReadArray(arr10,10);

    uint16_t arr2[2]   = {0xBEEF,0xFEEB};
    BufferWriteThenReadArray(arr2,10); 

    test_BufferRead_should_readAllDataCorrectly_after_insertThemUsingBufferWrite();

    BufferWriteThenReadArray(arr10,10);
    BufferWriteThenReadArray(arr2,10); 

}
/*********************************Buffer_IsFull*****************************************/

void bufferFill()
{
    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));
}

void bufferEmpty()
{
    uint16_t retVal;
    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(0,bufferRead(&retVal));
        TEST_ASSERT_EQUAL_UINT16(i,retVal);
    }
}
void test_Buffer_IsFull_should_returnOne_when_circluarBufferIsFullOnly()
{
    bufferFill();
    TEST_ASSERT_EQUAL(1,Buffer_IsFull());
}

void test_Buffer_IsFull_should_returnZero_when_circluarBufferIsNotFall()
{
    TEST_ASSERT_EQUAL(0,Buffer_IsFull());

    for(int i = 0 ; i < BUFFER_ELEMENTS-1 ; i++)
    {
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));
     TEST_ASSERT_EQUAL(0,Buffer_IsFull());
    }
}

void test_Buffer_IsFull_should_returnZeroAfterCircluarBufferIsFillAndReadOneElement()
{
    uint16_t retVal; 
    bufferFill();
    TEST_ASSERT_EQUAL(1,Buffer_IsFull());
    
    TEST_ASSERT_EQUAL_UINT16(0,bufferRead(&retVal));

    TEST_ASSERT_EQUAL(0,Buffer_IsFull());
}

void test_Buffer_IsFull_should_workProbarlyThroughMultipleFillEmptyCycle()
{
    for(int i = 0 ; i < 5 ; i++)
    {
        uint16_t retVal; 
        bufferFill();
        TEST_ASSERT_EQUAL(1,Buffer_IsFull());
        bufferEmpty();
        TEST_ASSERT_EQUAL(0,Buffer_IsFull());
    }
    

}

/*********************************Buffer_IsEmpty*****************************************/
void test_Buffer_IsEmpty_should_returnOne_when_circluarBufferIsEmptyOnly()
{
    //setup already reset buffer
    TEST_ASSERT_EQUAL(1,Buffer_IsEmpty());
}

void test_Buffer_IsEmpty_should_returnZero_when_circluarBufferIsNotEmpty()
{
    TEST_ASSERT_EQUAL(1,Buffer_IsEmpty());

    for(int i = 0 ; i < BUFFER_ELEMENTS ; i++)
    {
     TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(i));
     TEST_ASSERT_EQUAL(0,Buffer_IsEmpty());
    }
    
}

void test_Buffer_IsEmpty_should_returnZeroAfterCircluarBufferIsOneElementSizeAndReadOneElement()
{
    uint16_t retVal; 
    TEST_ASSERT_EQUAL_UINT16(0,bufferWrite(10));
    TEST_ASSERT_EQUAL(0,Buffer_IsEmpty());
    TEST_ASSERT_EQUAL_UINT16(0,bufferRead(&retVal));
    TEST_ASSERT_EQUAL(1,Buffer_IsEmpty());
}

void test_Buffer_IsEmpty_should_workProbarlyThroughMultipleFillEmptyCycle()
{
    for(int i = 0 ; i < 5 ; i++)
    {
        uint16_t retVal; 
        TEST_ASSERT_EQUAL(1,Buffer_IsEmpty());   
        bufferFill();
        TEST_ASSERT_EQUAL(0,Buffer_IsEmpty());
        bufferEmpty();
        TEST_ASSERT_EQUAL(1,Buffer_IsEmpty());
    }
    

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_bufferWrite_insertOperation_should_allowTobufferReadSuccessfully);
    RUN_TEST(test_bufferRead_should_not_allow_readUnwritedIndx);
    RUN_TEST(test_bufferWrite_shouldnt_allowWriteIfBufferIsFull);
    RUN_TEST(test_BufferRead_should_readAllDataCorrectly_after_insertThemUsingBufferWrite);
    RUN_TEST(test_BufferRead_should_allowReadAfter_BufferWrite_multiValue);
    RUN_TEST(test_Buffer_IsFull_should_returnOne_when_circluarBufferIsFullOnly);
    RUN_TEST(test_Buffer_IsFull_should_returnZero_when_circluarBufferIsNotFall);
    RUN_TEST(test_Buffer_IsFull_should_returnZeroAfterCircluarBufferIsFillAndReadOneElement);
    RUN_TEST(test_Buffer_IsFull_should_workProbarlyThroughMultipleFillEmptyCycle);
    RUN_TEST(test_Buffer_IsEmpty_should_returnOne_when_circluarBufferIsEmptyOnly);
    RUN_TEST(test_Buffer_IsEmpty_should_returnZero_when_circluarBufferIsNotEmpty);
    RUN_TEST(test_Buffer_IsEmpty_should_returnZeroAfterCircluarBufferIsOneElementSizeAndReadOneElement);
    RUN_TEST(test_Buffer_IsEmpty_should_workProbarlyThroughMultipleFillEmptyCycle);
    return UNITY_END();
}
