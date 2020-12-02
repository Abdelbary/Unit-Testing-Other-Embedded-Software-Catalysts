#include "Parser.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef TEST
#define STATIC static
#else
#define STATIC
#endif

#define PARSER_BUFFER_LENGTH_MAX   (23)


STATIC PARSER_STATE_T state = PARSER_LOOKING_FOR_START;
static int  nibbles_needed;
static int  len;
static char buffer[PARSER_BUFFER_LENGTH_MAX];

char* Parser_AddChar(char NewChar)
{
    if (NewChar == '[') {
        buffer[0] = NewChar;
        state = PARSER_LOOKING_FOR_CMD;
        return NULL;
    }

    switch(state)
    {
        case PARSER_LOOKING_FOR_CMD:
            if ((NewChar >= 'A') && (NewChar <= 'Z'))  {
                buffer[1] = NewChar;
                state += 1;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;

        case PARSER_LOOKING_FOR_LEN:
            if ((NewChar >= '0') && (NewChar <= '9'))  {
                buffer[2] = NewChar;
                nibbles_needed = 2 * ((int)(NewChar) - (int)('0'));
                len = 3;
                if (nibbles_needed)
                    state = PARSER_LOOKING_FOR_DAT;
                else
                    state = PARSER_LOOKING_FOR_END;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;

        case PARSER_LOOKING_FOR_DAT:
            if (((NewChar >= '0') && (NewChar <= '9')) ||
                ((NewChar >= 'A') && (NewChar <= 'F'))) {
                buffer[len++] = NewChar;
                if (--nibbles_needed == 0)
                    state = PARSER_LOOKING_FOR_END;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;

        case PARSER_LOOKING_FOR_END:
            if (NewChar == ']')  {
                buffer[len] = NewChar;
                buffer[len+1] = 0;
                state = PARSER_LOOKING_FOR_START;
                return buffer;
            }
            else
                state = PARSER_LOOKING_FOR_START;
            break;

        default:
            state = PARSER_LOOKING_FOR_START;
    }

    return NULL;
}
