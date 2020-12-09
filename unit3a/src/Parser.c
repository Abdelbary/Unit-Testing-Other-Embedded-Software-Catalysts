#include "Parser.h"
#include "MK20DX256.h"
#include <stdio.h>
#include <string.h>

STATIC Parser_state_t ge_parser_state = LOOKING_FOR_START_PRACKET;
STATIC char  gs_parsedString[MAX_PARSED_STRING];
char * addChar(char c)
{
    static int counter = 0 ;
    if(c == '[')
    {
        //reset state reset all paramters
        ge_parser_state = LOOKING_FOR_CMD;
        counter = 0;
        memset(gs_parsedString,0,sizeof(gs_parsedString));
        gs_parsedString[0] = '[';
        return 0;
    }
    switch (ge_parser_state)
    {    
    case LOOKING_FOR_CMD:
        if(c >= 'A' && c <= 'Z')
        {
         ge_parser_state = LOOKING_FOR_LEN;
         gs_parsedString[1] = c;
        }  
        else 
            ge_parser_state = LOOKING_FOR_START_PRACKET;
        break;
    case LOOKING_FOR_LEN:
        if(c >= '0' && c <= '9')
        {
            gs_parsedString[2] = c;

            if( c == '0')
                ge_parser_state = LOOKING_FOR_END_PRACKET;
            else
                ge_parser_state = LOOKING_FOR_DATA;
        }
        else
            ge_parser_state = LOOKING_FOR_START_PRACKET;
        break;
    case LOOKING_FOR_DATA:
        if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
        {   
            gs_parsedString[counter+3] = c;
            counter++;
            if(counter == ((gs_parsedString[2]-'0') * 2) )
            {
                ge_parser_state = LOOKING_FOR_END_PRACKET;
            }
               
        }
        else 
        {
            ge_parser_state = LOOKING_FOR_START_PRACKET;
            counter = 0;
        }
        break;
    case LOOKING_FOR_END_PRACKET:
        if(c == ']')
        {
         gs_parsedString[counter+3] = c;
         gs_parsedString[counter+3+1] = '\0';
         counter = 0;
         ge_parser_state = LOOKING_FOR_START_PRACKET;
         return (char *)gs_parsedString;
        }
        else
            ge_parser_state = LOOKING_FOR_START_PRACKET;
    break;
        
    default:
            ge_parser_state = LOOKING_FOR_START_PRACKET;
        break;
    }
    return 0;
}