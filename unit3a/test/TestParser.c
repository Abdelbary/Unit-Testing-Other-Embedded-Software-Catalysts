
#include "unity.h"
#include "Parser.h"
#include "MK20DX256.h"

extern Parser_state_t ge_parser_state;
void test_addChar_should_chageStateTo_LOOKING_FOR_CMD_when_recivieStartPracket()
{
    ge_parser_state = LOOKING_FOR_START_PRACKET;
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
}
void test_addCher_should_notChangeState_when_notRecieveOpenPracket()
{
    ge_parser_state = LOOKING_FOR_START_PRACKET;
    TEST_ASSERT_NULL(addChar('{'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar(']'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
}
void test_addChar_should_changeStateTo_LOOLING_FOR_LEN_when_in_state_LOOKING_FOR_CMD_and_recieveVaalidChar()
{
    //vaild cmd A-to-Z only
    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('A'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('Z'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('X'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
}

void test_addChar_should_changeState_toLookingForStartPracket_when_StateIsLookingForCmd_and_invalidInputChar()
{
    //vaild cmd A-to-Z only and 
    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar(']'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('z'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('a'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

     ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('9'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(addChar('\\'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
}


void test_addchar_should_changeStateToLookingForData_when_statIsLookingForLen_and_recivieRightLen()
{
    ge_parser_state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(addChar('1'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    ge_parser_state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(addChar('5'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    ge_parser_state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(addChar('9'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
}

void test_addChar_should_changeStateToLookingForEndPracket_when_RecivieMinimalPacketLen()
{
    ge_parser_state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(addChar('0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_END_PRACKET,ge_parser_state);
}

void send_data_and_assert_state_till_lookingForEndPracket(char cmd, char * string,int len)
{
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar(cmd));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(len+'0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    for(int i = 0 ; i < len*2 ; i++)
    {
     TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
     TEST_ASSERT_NULL(addChar(string[i]));
    }
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_END_PRACKET,ge_parser_state);

}



void test_addChar_should_changeStateToLookingForEndPracket_when_ReciveAllPacketChar()
{
    send_data_and_assert_state_till_lookingForEndPracket('A',"aabbccddeeff",6);
    send_data_and_assert_state_till_lookingForEndPracket('B',"AA",1);
    send_data_and_assert_state_till_lookingForEndPracket('Z',"0f0f0f0f0f0f0f0f0f",9);
}

void test_addChar_should_changeStateToLookingForCmd_when_ReciveStartPracketInLookingForDataState()
{
    ge_parser_state = LOOKING_FOR_START_PRACKET;
    char * string = "aabbccddeefff";
    int len = 7;
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar('A'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(len + '0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    for(int i = 0 ; i < len*2 -1 ; i++)
    {
     TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
     TEST_ASSERT_NULL(addChar(string[i]));
    }

    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
}

void test_addChar_should_changeStateToLookingForStartPacket_when_ReciveInvalidDataInLookingForDataState()
{
    char  string[] = "aabbccddeefff";
    int len = 7;
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar('A'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(len + '0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    for(int i = 0 ; i < len*2 -1 ; i++)
    {
     TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
     TEST_ASSERT_NULL(addChar(string[i]));
    }

    TEST_ASSERT_NULL(addChar('X'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
}

void send_data_and_assert_state(char cmd, int len ,char * string, char* full)
{
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar(cmd));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(len+'0'));
    if(len != 0)
    {
        TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

        for(int i = 0 ; i < len*2 ; i++)
        {
        TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
        TEST_ASSERT_NULL(addChar(string[i]));
        }
    }
    
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_END_PRACKET,ge_parser_state);
    TEST_ASSERT_EQUAL_STRING(full,addChar(']'));
}
void test_addChar_should_returnStringOfFullCmdIfPassedRight()
{
    send_data_and_assert_state('A',0,"","[A0]");
    send_data_and_assert_state('B',1,"aa","[B1aa]");
    send_data_and_assert_state('Z',2,"abab","[Z2abab]");
    send_data_and_assert_state('X',9,"aBbFf12BD2345681ab","[X9aBbFf12BD2345681ab]");
    send_data_and_assert_state('Y',0,"","[Y0]");

}

void test_addChar_should_workFineAfterInvalidCharInput()
{
    char  string[] = "aabbccddeefff";
    int len = 7;
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar('A'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(len + '0'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);

    for(int i = 0 ; i < len*2 -1 ; i++)
    {
     TEST_ASSERT_EQUAL_INT(LOOKING_FOR_DATA,ge_parser_state);
     TEST_ASSERT_NULL(addChar(string[i]));
    }

    TEST_ASSERT_NULL(addChar('X'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    send_data_and_assert_state('X',9,"aBbFf12BD2345681ab","[X9aBbFf12BD2345681ab]");

/******************************************************************************************/
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar('a'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    send_data_and_assert_state('Z',2,"abab","[Z2abab]");

/******************************************************************************************/
    TEST_ASSERT_NULL(addChar('['));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_CMD,ge_parser_state);
    TEST_ASSERT_NULL(addChar('A'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_LEN,ge_parser_state);
    TEST_ASSERT_NULL(addChar(0));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    send_data_and_assert_state('B',1,"aa","[B1aa]");
}

void test_addChar_should_chageStateTo_LOOKING_FOR_START_PRAKET_when_recivieWrongCharSeqAfterReciviengStartPacket()
{


    ge_parser_state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(addChar('|'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('/'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('o'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_DATA;
    TEST_ASSERT_NULL(addChar('\\'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('g'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('z'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('G'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

    ge_parser_state = LOOKING_FOR_END_PRACKET;
    TEST_ASSERT_NULL(addChar('|'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('/'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);
    TEST_ASSERT_NULL(addChar('o'));
    TEST_ASSERT_EQUAL_INT(LOOKING_FOR_START_PRACKET,ge_parser_state);

}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addChar_should_chageStateTo_LOOKING_FOR_CMD_when_recivieStartPracket);
    RUN_TEST(test_addChar_should_changeStateTo_LOOLING_FOR_LEN_when_in_state_LOOKING_FOR_CMD_and_recieveVaalidChar);
    RUN_TEST(test_addChar_should_changeState_toLookingForStartPracket_when_StateIsLookingForCmd_and_invalidInputChar);
    RUN_TEST(test_addchar_should_changeStateToLookingForData_when_statIsLookingForLen_and_recivieRightLen);
    RUN_TEST(test_addChar_should_changeStateToLookingForEndPracket_when_RecivieMinimalPacketLen);
    RUN_TEST(test_addChar_should_changeStateToLookingForEndPracket_when_ReciveAllPacketChar);
    RUN_TEST(test_addChar_should_changeStateToLookingForCmd_when_ReciveStartPracketInLookingForDataState);
    RUN_TEST(test_addChar_should_changeStateToLookingForStartPacket_when_ReciveInvalidDataInLookingForDataState);
    RUN_TEST(test_addChar_should_chageStateTo_LOOKING_FOR_START_PRAKET_when_recivieWrongCharSeqAfterReciviengStartPacket);
    RUN_TEST(test_addChar_should_returnStringOfFullCmdIfPassedRight);
    RUN_TEST(test_addChar_should_workFineAfterInvalidCharInput);
    return UNITY_END();
}
