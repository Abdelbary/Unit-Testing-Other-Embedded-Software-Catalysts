#include "Buffer.h"
#include "MK20DX256.h"



uint16 crcilarBuffer[BUFFER_SIZE];
uint16 readIndx  = 0;
uint16 wirteIndx = 0;


void bufferReset()
{
    readIndx  = 0;
    wirteIndx = 0;
}

int bufferWrite(uint16 val)
{
    uint16 nextIndx = (wirteIndx+1)% BUFFER_SIZE;
    if(nextIndx == readIndx)
        return -1;
    crcilarBuffer[wirteIndx] = val;
    wirteIndx = nextIndx;

    return 0;
}

char Buffer_IsFull()
{
    uint16 nextIndx = (wirteIndx+1)% BUFFER_SIZE;

    return (nextIndx == readIndx);
}

char Buffer_IsEmpty()
{
    return (readIndx == wirteIndx );
}
int bufferRead(uint16 * val)
{
    if(readIndx == wirteIndx)
        return -1;

    *val = crcilarBuffer[readIndx];
    readIndx = (readIndx+1)% BUFFER_SIZE;

    return 0;
}