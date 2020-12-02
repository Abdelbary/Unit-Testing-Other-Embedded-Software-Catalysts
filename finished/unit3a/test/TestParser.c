
#include "unity.h"
#include "Parser.h"
#include "MK20DX256.h"

extern PARSER_STATE_T state;

//===============================================================WHITE BOX TESTING

void test_Parser_AddChar_should_StartLookingForCmdOnLeftBracket(void)
{
    state = PARSER_LOOKING_FOR_START;

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );

    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_CMD, state);
}

void test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart(void)
{
    state = PARSER_LOOKING_FOR_START;
    TEST_ASSERT_NULL( Parser_AddChar( '|' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);

    TEST_ASSERT_NULL( Parser_AddChar( '9' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);

    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}

void test_Parser_AddChar_should_AcceptAValidCommandCharacter(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( 'M' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( 'Z' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);
}

void test_Parser_AddChar_should_RejectInvalidCommandCharacter(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( '@' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( '\\' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL( Parser_AddChar( 'a' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}

void test_Parser_AddChar_should_AcceptALengthOfZero(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL( Parser_AddChar( '0' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_END, state);
}

void test_Parser_AddChar_should_RejectInvalidLengths(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL( Parser_AddChar( ':' ) );
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}

//============================================================HELPERS

void insert_valid_minimal_packet(char cmd, const char* full);
void insert_valid_standard_packet(char cmd, int len, const char* full);

void insert_valid_minimal_packet(char cmd, const char* full)
{
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( cmd ) );
    TEST_ASSERT_NULL( Parser_AddChar( '0' ) );
    TEST_ASSERT_EQUAL_STRING( full, Parser_AddChar( ']' ) );
}

void insert_valid_standard_packet(char cmd, int len, const char* full)
{
    int i;
    char Filler[] = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( cmd ) );
    TEST_ASSERT_NULL( Parser_AddChar( (char)('0' + len) ) );

    for (i=0; i < len*2; i++)
    {
        TEST_ASSERT_NULL( Parser_AddChar( Filler[i%16] ) );
    }

    TEST_ASSERT_EQUAL_STRING( full, Parser_AddChar( ']' ) );
}

//============================================================BLACK BOX TESTING

void test_Parser_AddChar_should_HandleValidPacketWithNoData(void)
{
    insert_valid_minimal_packet('A',"[A0]");
}

void test_Parser_AddChar_should_HandleBackToBackValidPackets(void)
{
    insert_valid_minimal_packet('A',"[A0]");
    insert_valid_minimal_packet('Z',"[Z0]");
    insert_valid_minimal_packet('C',"[C0]");
}

void test_Parser_AddChar_should_HandlePacketsWithLength1(void)
{
    insert_valid_standard_packet('A', 1, "[A1AB]");
}

void test_Parser_AddChar_should_HandlePacketsWithLength9(void)
{
    insert_valid_standard_packet('A', 9, "[A9ABCDEF0123456789AB]");
}

void test_Parser_AddChar_should_HandleDifferentLengthPacketsBackToBack(void)
{
    insert_valid_standard_packet('A', 9, "[A9ABCDEF0123456789AB]");
    insert_valid_standard_packet('B', 0, "[B0]");
    insert_valid_standard_packet('C', 7, "[C7ABCDEF01234567]");
    insert_valid_standard_packet('D', 2, "[D2ABCD]");
    insert_valid_standard_packet('E', 0, "[E0]");
}

void test_Parser_AddChar_should_IgnoreBadStartCharacters(void)
{
    TEST_ASSERT_NULL( Parser_AddChar( '?' ) );
    insert_valid_minimal_packet('D',"[D0]");

    TEST_ASSERT_NULL( Parser_AddChar( 'a' ) );
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_minimal_packet('X',"[X0]");
}

void test_Parser_AddChar_should_IgnoreBadCommandCharacters(void)
{
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'a' ) );
    insert_valid_minimal_packet('R',"[R0]");

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'z' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '0' ) );
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_minimal_packet('S',"[S0]");
}

void test_Parser_AddChar_should_IgnoreBadLengthCharacters(void)
{
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '@' ) );
    insert_valid_minimal_packet('R',"[R0]");

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'Z' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_minimal_packet('S',"[S0]");
}

void test_Parser_AddChar_should_IgnoreBadHexCharacters(void)
{
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '1' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'G' ) );
    insert_valid_minimal_packet('R',"[R0]");

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '1' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'G' ) );
    insert_valid_minimal_packet('R',"[R0]");

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'Z' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '1' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'G' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '0' ) );
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_minimal_packet('S',"[S0]");

    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'Z' ) );
    TEST_ASSERT_NULL( Parser_AddChar( '1' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'G' ) );
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_minimal_packet('S',"[S0]");
}

void test_Parser_AddChar_should_IgnoreJunkBetweenValidPackets(void)
{
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    insert_valid_standard_packet('A', 9, "[A9ABCDEF0123456789AB]");
    TEST_ASSERT_NULL( Parser_AddChar( ']' ) );
    insert_valid_standard_packet('B', 0, "[B0]");
    TEST_ASSERT_NULL( Parser_AddChar( '#' ) );
    insert_valid_standard_packet('C', 7, "[C7ABCDEF01234567]");
    TEST_ASSERT_NULL( Parser_AddChar( '2' ) );
    insert_valid_standard_packet('D', 2, "[D2ABCD]");
    TEST_ASSERT_NULL( Parser_AddChar( '[' ) );
    TEST_ASSERT_NULL( Parser_AddChar( 'A' ) );
    insert_valid_standard_packet('E', 0, "[E0]");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Parser_AddChar_should_StartLookingForCmdOnLeftBracket);
    RUN_TEST(test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart);
    RUN_TEST(test_Parser_AddChar_should_AcceptAValidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_AcceptALengthOfZero);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidLengths);
    RUN_TEST(test_Parser_AddChar_should_HandleValidPacketWithNoData);
    RUN_TEST(test_Parser_AddChar_should_HandleBackToBackValidPackets);
    RUN_TEST(test_Parser_AddChar_should_HandlePacketsWithLength1);
    RUN_TEST(test_Parser_AddChar_should_HandlePacketsWithLength9);
    RUN_TEST(test_Parser_AddChar_should_HandleDifferentLengthPacketsBackToBack);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadStartCharacters);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadCommandCharacters);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadLengthCharacters);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadHexCharacters);
    RUN_TEST(test_Parser_AddChar_should_IgnoreJunkBetweenValidPackets);
    return UNITY_END();
}
