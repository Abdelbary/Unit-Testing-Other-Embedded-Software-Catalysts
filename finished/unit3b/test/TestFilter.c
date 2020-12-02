
#include "unity.h"
#include "Filter.h"

void test_Filter_AddVal_should_OutputPrevVal_if_PreValAndNewValMatch(void)
{
    TEST_ASSERT_EQUAL_HEX16( 0, Filter_AddVal(0, 0) );
    TEST_ASSERT_EQUAL_HEX16( 0xFFFF, Filter_AddVal(0xFFFF, 0xFFFF) );
    TEST_ASSERT_EQUAL_HEX16( 0x8000, Filter_AddVal(0x8000, 0x8000) );
    TEST_ASSERT_EQUAL_HEX16( 0x7FFF, Filter_AddVal(0x7FFF, 0x7FFF) );
}

void test_Filter_AddVal_should_HandleSimpleMiddleRangeCalculations(void)
{
    TEST_ASSERT_EQUAL_HEX16( 775, Filter_AddVal(1000, 100) );
    TEST_ASSERT_EQUAL_HEX16( 325, Filter_AddVal(100, 1000) );
}

void test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 3, Filter_AddVal(4, 0) );
    TEST_ASSERT_EQUAL_HEX16( 1, Filter_AddVal(0, 4) );
}

void test_Filter_AddVal_should_HandleCalculationsNearTopOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 0xFFFE, Filter_AddVal(0xFFFF, 0xFFFE) );
    TEST_ASSERT_EQUAL_HEX16( 0xFFF9, Filter_AddVal(0xFFF8, 0xFFFF) );
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Filter_AddVal_should_OutputPrevVal_if_PreValAndNewValMatch);
    RUN_TEST(test_Filter_AddVal_should_HandleSimpleMiddleRangeCalculations);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearTopOfRange);
    return UNITY_END();
}
