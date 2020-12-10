#ifndef BUFFER_H
#define BUFFER_H

#define uint16 unsigned short int
#define BUFFER_ELEMENTS 1000
#define BUFFER_SIZE     (BUFFER_ELEMENTS+1)

void bufferReset();
int bufferWrite(uint16 val);
int bufferRead(uint16 * val);
char Buffer_IsFull();
char Buffer_IsEmpty();
#endif //BUFFER_H
