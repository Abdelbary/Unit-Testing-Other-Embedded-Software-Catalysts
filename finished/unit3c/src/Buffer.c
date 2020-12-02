#include "Buffer.h"

#define BUFFER_SIZE (1000 + 1)

uint16_t Buffer[BUFFER_SIZE];
uint16_t BufferRead = 0;
uint16_t BufferWrite = 0;

int Buffer_Init(void)
{
    BufferWrite = 0;
    BufferRead  = 0;

    return STATUS_OK;
}

int Buffer_Put(uint16_t Val)
{
    uint16_t NextWrite = (BufferWrite + 1) % BUFFER_SIZE;
    if (0 == Buffer)
        return STATUS_NOT_INITIALIZED;
    if (NextWrite == BufferRead)
        return STATUS_OVERFLOW;
    Buffer[ BufferWrite ] = Val;
    BufferWrite = NextWrite;
    return STATUS_OK;
}

int Buffer_Get(uint16_t* Val)
{
    if (0 == Buffer)
        return STATUS_NOT_INITIALIZED;
    if (BufferRead == BufferWrite)
        return STATUS_NONE_YET;
    *Val = Buffer[ BufferRead ];
    BufferRead = (BufferRead + 1) % BUFFER_SIZE;
    return STATUS_OK;
}

int Buffer_IsFull(void)
{
    uint16_t NextWrite = (BufferWrite + 1) % BUFFER_SIZE;
    return (NextWrite == BufferRead);
}

int Buffer_IsEmpty(void)
{
    return (BufferRead == BufferWrite);
}

void Buffer_Clear(void)
{
    BufferRead = BufferWrite;
}
