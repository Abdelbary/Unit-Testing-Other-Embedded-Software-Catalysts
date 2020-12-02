
#include "unity.h"
#include "Buffer.h"
#include "MK20DX256.h"

#define BUFFER_SIZE (1000)
#define DIMENSION_OF(a) (sizeof(a) / sizeof(a[0]))

void setUp(void)
{
    Buffer_Init();
}

void test_Buffer_Put_and_Get_should_WorkTogetherToInsertAndExtractAValue(void)
{
    const uint16_t data[ ] = { 0, 1, 0x5A, 0x7FFF, 0xFFFF };
    uint16_t fetched;
    int i;

    for (i = 0; i < DIMENSION_OF(data); i++)  {
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put( data[i] ));
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Get( &fetched ));
        TEST_ASSERT_EQUAL_HEX16(data[i], fetched);
    }
}

void test_Buffer_Get_should_ReturnErrorIfCalledWhenEmpty(void)
{
    uint16_t fetched;

    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Get( &fetched ));
}

void test_Buffer_Put_should_ReturnErrorIfCalledWhenFull(void)
{
    int i;

    for (i = 0; i < BUFFER_SIZE; i++)
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));

    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Put(1));
}

void test_Buffer_Put_should_ReturnErrorIfCalledWhenFull_Method2(void)
{
    int i;
    int Expected[ BUFFER_SIZE ];
    int Actual[ BUFFER_SIZE ];

    for (i = 0; i < BUFFER_SIZE; i++)  {
        Expected[ i ] = 0;
        Actual[ i ] = Buffer_Put(i);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(Expected, Actual, BUFFER_SIZE);
    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Put(1));
}

void test_Buffer_Get_should_ProperlyGrabEveryItemFromFullToEmpty(void)
{
    int i;
    uint16_t fetched;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));
    }

    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Put(1));

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Get( &fetched ));
        TEST_ASSERT_EQUAL_UINT16(i, fetched);
    }

    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Get( &fetched ));
}

void test_Buffer_IsFull_should_ReturnTrueWhenFullOtherwiseFalse(void)
{
    int i;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        TEST_ASSERT_FALSE(Buffer_IsFull());
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));
    }

    TEST_ASSERT_TRUE(Buffer_IsFull());
    TEST_ASSERT_NOT_EQUAL(STATUS_OK, Buffer_Put(1));
}

void test_Buffer_IsEmpty_should_ReturnTrueWhenEmptyOtherwiseFalse(void)
{
    int i;
    uint16_t fetched;

    TEST_ASSERT_TRUE(Buffer_IsEmpty());

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));
        TEST_ASSERT_FALSE(Buffer_IsEmpty());
    }

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        TEST_ASSERT_FALSE(Buffer_IsEmpty());
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Get( &fetched ));
    }

    TEST_ASSERT_TRUE(Buffer_IsEmpty());
}

void test_Buffer_Clear_should_ClearItIfCleared(void)
{
    int i;

    TEST_ASSERT_TRUE(Buffer_IsEmpty());
    Buffer_Clear();
    TEST_ASSERT_TRUE(Buffer_IsEmpty());
}

void test_Buffer_Clear_should_ClearItIfSomeElementsInIt(void)
{
    int i;

    TEST_ASSERT_TRUE(Buffer_IsEmpty());
    Buffer_Clear();
    TEST_ASSERT_TRUE(Buffer_IsEmpty());

    for (i = 0; i < 3; i++)
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));
    TEST_ASSERT_FALSE(Buffer_IsEmpty());

    Buffer_Clear();
    TEST_ASSERT_TRUE(Buffer_IsEmpty());
}

void test_Buffer_Clear_should_ClearItIfFull(void)
{
    int i;

    TEST_ASSERT_TRUE(Buffer_IsEmpty());
    Buffer_Clear();
    TEST_ASSERT_TRUE(Buffer_IsEmpty());

    for (i = 0; i < BUFFER_SIZE; i++)
        TEST_ASSERT_EQUAL(STATUS_OK, Buffer_Put(i));
    TEST_ASSERT_FALSE(Buffer_IsEmpty());

    Buffer_Clear();
    TEST_ASSERT_TRUE(Buffer_IsEmpty());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Buffer_Put_and_Get_should_WorkTogetherToInsertAndExtractAValue);
    RUN_TEST(test_Buffer_Get_should_ReturnErrorIfCalledWhenEmpty);
    RUN_TEST(test_Buffer_Put_should_ReturnErrorIfCalledWhenFull);
    RUN_TEST(test_Buffer_Put_should_ReturnErrorIfCalledWhenFull_Method2);
    RUN_TEST(test_Buffer_Put_and_Get_should_WorkTogetherToInsertAndExtractAValue);
    RUN_TEST(test_Buffer_Get_should_ProperlyGrabEveryItemFromFullToEmpty);
    RUN_TEST(test_Buffer_IsFull_should_ReturnTrueWhenFullOtherwiseFalse);
    RUN_TEST(test_Buffer_IsEmpty_should_ReturnTrueWhenEmptyOtherwiseFalse);
    RUN_TEST(test_Buffer_Clear_should_ClearItIfCleared);
    RUN_TEST(test_Buffer_Clear_should_ClearItIfSomeElementsInIt);
    RUN_TEST(test_Buffer_Clear_should_ClearItIfFull);
    return UNITY_END();
}
