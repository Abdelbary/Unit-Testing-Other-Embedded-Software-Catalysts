
#include "unity.h"
#include "Fib.h"
#include <limits.h>
#define DIMENTION(a) (sizeof(a)/sizeof(a[0]))

/*==================================test_Fibonacci_GetElement==========================================*/
void test_element0_should_return_1(void)
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_GetElement(0));
}

void test_element1_should_return_1(void)
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_GetElement(1));
}

void test_element2_should_return_2(void)
{
    TEST_ASSERT_EQUAL_INT(2,Fibonacci_GetElement(2));   
}

void test_first_10_element(void)
{
    int expected[] = {1,1,2,3,5,8,13,21,34,55};

    for(int i = 0 ; i < DIMENTION(expected) ; i++)
    {
        TEST_ASSERT_EQUAL_INT(expected[i],Fibonacci_GetElement(i));
    }
}

void test_negaitve_number_should_return_negative_1()
{
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(-1));
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(-2));
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(-500));
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(INT_MIN));
}

void test_max_number_allowed_should_return_negative_1()
{
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(46));
    TEST_ASSERT_EQUAL_INT(-1,Fibonacci_GetElement(47));
    ///max interger allowed to be hold from fib series is number 45 on 32 bit int machine
    TEST_ASSERT_EQUAL_INT(1836311903,Fibonacci_GetElement(45));
}

void test_Fibonacci_GetElement()
{
    RUN_TEST(test_element0_should_return_1);
    RUN_TEST(test_element1_should_return_1);
    RUN_TEST(test_element2_should_return_2);
    RUN_TEST(test_first_10_element);
    RUN_TEST(test_negaitve_number_should_return_negative_1);
    RUN_TEST(test_max_number_allowed_should_return_negative_1);
}

/*==================================test_Fibonacci_IsInSequence=========================================*/


void test_1_in_sequence_should_return_1()
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(1));
}

void test_2_in_sequence_should_return_1()
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(2));
}

void test_max_int_in_sequence_should_return_1()
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(1836311903));
}

void test_limit_int_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MAX));
}


void test_first_ten_values_exsist()
{
      int vaules_to_find[] = {1,1,2,3,5,8,13,21,34,55};

        for(int i =0  ; i < DIMENTION(vaules_to_find); i++)
           TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(vaules_to_find[i]));
}


void test_negative_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-1),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-100),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-500),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-15000),0);
}

void test_negative_limit_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MIN));
}

void test_unavailable_firt_ten_values()
{
    int vaules_not_inseq[] = {4,6,7,9,10,11,12,14,15,16};

        for(int i =0  ; i < DIMENTION(vaules_not_inseq); i++)
           TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(vaules_not_inseq[i]));
}
void test_Fibonacci_IsInSequence()
{
    RUN_TEST(test_1_in_sequence_should_return_1);
    RUN_TEST(test_2_in_sequence_should_return_1);
    RUN_TEST(test_first_ten_values_exsist);
    RUN_TEST(test_max_int_in_sequence_should_return_1);
    RUN_TEST(test_negative_in_sequence_should_return_0);
    RUN_TEST(test_negative_limit_in_sequence_should_return_0);
    RUN_TEST(test_limit_int_in_sequence_should_return_0);
    RUN_TEST(test_unavailable_firt_ten_values);

}


int main(void) {
    UNITY_BEGIN();
    test_Fibonacci_GetElement();
    test_Fibonacci_IsInSequence();
    return UNITY_END();
}
