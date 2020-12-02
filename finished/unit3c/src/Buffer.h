#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define STATUS_OK              (0)
#define STATUS_NOT_INITIALIZED (-1)
#define STATUS_NULL_POINTER    (-2)
#define STATUS_TOO_HIGH        (-3)
#define STATUS_OVERFLOW        (-4)
#define STATUS_NONE_YET        (-5)


int  Buffer_Init(void);
int  Buffer_Put(uint16_t Val);
int  Buffer_Get(uint16_t* Val);
int  Buffer_IsFull(void);
int  Buffer_IsEmpty(void);
void Buffer_Clear(void);

#endif //BUFFER_H
