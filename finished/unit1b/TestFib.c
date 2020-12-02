
#include "unity.h"
#include "Fib.h"

#include <limits.h>

#define DIMENSION_OF(a) ( sizeof(a) / sizeof(a[0]) )

void test_element0_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(0) );
}

void test_element1_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(1) );
}

void test_element2_should_return2(void)
{
    TEST_ASSERT_EQUAL_INT(2, Fibonacci_GetElement(2) );
}

void test_part_of_the_sequence(void)
{
    int expected[ ] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
    int i;

    for (i=0; i < DIMENSION_OF(expected); i++) {
        TEST_ASSERT_EQUAL_INT( expected[ i ], Fibonacci_GetElement(i) );
    }
}

void test_that_negative_elements_return_0(void)
{
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( -1 ) );
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( -3 ) );
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( -555 ) );
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( INT_MIN ) );
}

void test_that_overrun_values_return_0(void)
{
    const int first_bad_element = 46;
    const int last_good_element = first_bad_element - 1;
    int last_good_value = Fibonacci_GetElement( last_good_element );

    TEST_ASSERT_EQUAL_INT_MESSAGE( 4, sizeof(int), "Constants first_bad_element and FIB_MAX_ELEMENT Must Be Changed");
    TEST_ASSERT_MESSAGE( last_good_value > 1 , "This value should not have been a rollover");
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( first_bad_element ) );
    TEST_ASSERT_EQUAL_INT( 0, Fibonacci_GetElement( INT_MAX ) );
}

void test_value0_should_not_be_in_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(0) );
}

void test_value1_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(1) );
}

void test_value2_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(2) );
}

void test_value3_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(3) );
}

void test_value4_should_not_be_in_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(4) );
}

void test_value5_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(5) );
}

void test_values_in_sequence_should_report_as_such_otherwise_not(void)
{
    int expected[ ] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
    int e = 0;
    int i;

    for (i=0; i <= 144; i++) {
        if (expected[e] == i)
        {
            TEST_ASSERT_TRUE( Fibonacci_IsInSequence(i) );
            e++;
        }
        else
        {
            TEST_ASSERT_FALSE( Fibonacci_IsInSequence(i) );
        }
    }
}

void test_negative_values_should_always_say_not_in_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(-1) );
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(-18) );
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(-999) );
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(INT_MIN) );
}

void test_largest_value_should_be_in_sequence_but_not_larger_values_out_of_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(1836311902) );
    TEST_ASSERT_TRUE(  Fibonacci_IsInSequence(1836311903) );
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(1836311904) );
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_element0_should_return1);
    RUN_TEST(test_element1_should_return1);
    RUN_TEST(test_element2_should_return2);
    RUN_TEST(test_part_of_the_sequence);
    RUN_TEST(test_that_negative_elements_return_0);
    RUN_TEST(test_that_overrun_values_return_0);
    RUN_TEST(test_value0_should_not_be_in_sequence);
    RUN_TEST(test_value1_should_be_in_sequence);
    RUN_TEST(test_value2_should_be_in_sequence);
    RUN_TEST(test_value3_should_be_in_sequence);
    RUN_TEST(test_value4_should_not_be_in_sequence);
    RUN_TEST(test_value5_should_be_in_sequence);
    RUN_TEST(test_values_in_sequence_should_report_as_such_otherwise_not);
    RUN_TEST(test_negative_values_should_always_say_not_in_sequence);
    RUN_TEST(test_largest_value_should_be_in_sequence_but_not_larger_values_out_of_sequence);
    return UNITY_END();
}

