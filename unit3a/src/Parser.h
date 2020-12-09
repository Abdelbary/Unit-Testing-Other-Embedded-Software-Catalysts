#ifndef PARSER_H
#define PARSER_H

#define MAX_PARSED_STRING (23)


#ifdef TEST
#define STATIC 
#else
#define STATIC static
#endif



typedef enum
{
    LOOKING_FOR_START_PRACKET,
    LOOKING_FOR_CMD,
    LOOKING_FOR_LEN,
    LOOKING_FOR_DATA,
    LOOKING_FOR_END_PRACKET
}Parser_state_t;


char * addChar(char c);

#endif //PARSER_H
