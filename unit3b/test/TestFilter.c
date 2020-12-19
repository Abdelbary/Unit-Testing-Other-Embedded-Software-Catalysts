
#include "unity.h"
#include "Filter.h"
#include "MK20DX256.h"



void test_FilterAddValue_should_returnTheSameValueIfThePrevValueEqualTheNewVal()
{
    TEST_ASSERT_EQUAL_HEX16(0xFFFF,FilterAddValue(0xFFFF,0xFFFF));
    TEST_ASSERT_EQUAL_HEX16(0x0000,FilterAddValue(0x0000,0x0000));
    TEST_ASSERT_EQUAL_HEX16(0x00FF,FilterAddValue(0x00FF,0x00FF));
    TEST_ASSERT_EQUAL_HEX16(0xFF00,FilterAddValue(0xFF00,0xFF00));
    TEST_ASSERT_EQUAL_HEX16(0xABCD,FilterAddValue(0xABCD,0xABCD));
}

void test_FilterAddValue_should_handleSimpleMidRangeValues()
{
    TEST_ASSERT_EQUAL_UINT16(775,FilterAddValue(1000,100));
    TEST_ASSERT_EQUAL_UINT16(325,FilterAddValue(100,1000));
}

void test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 3, FilterAddValue(4, 0) );
    TEST_ASSERT_EQUAL_HEX16( 1, FilterAddValue(0, 4) );
}

void test_Filter_AddVal_should_HandleCalculationsNearTopOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 0xFFFE, FilterAddValue(0xFFFF, 0xFFFE) );
    TEST_ASSERT_EQUAL_HEX16( 0xFFF9, FilterAddValue(0xFFF8, 0xFFFF) );
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_FilterAddValue_should_returnTheSameValueIfThePrevValueEqualTheNewVal);
    RUN_TEST(test_FilterAddValue_should_handleSimpleMidRangeValues);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearTopOfRange);
    return UNITY_END();
}
