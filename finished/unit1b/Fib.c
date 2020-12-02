#include "Fib.h"

#define FIB_MAX_ELEMENT  (45)

int Fibonacci_GetElement(int num)
{
   int i;
   int first  = 1;
   int second = 1;
   int next   = 1;

   if ((num < 0) || (num > FIB_MAX_ELEMENT))
     return 0;
   for (i = 2; i <= num; i++)
   {
     next = first + second;
     first = second;
     second = next;
   }

   return next;
}


int Fibonacci_IsInSequence(int num)
{
   int i;
   int first  = 1;
   int second = 2;
   int next   = 1;

   if (num <= 0)
     return 0;
   if (num < 3)
     return 1;
   for (i = 2; ((next > num) || (i <= FIB_MAX_ELEMENT)); i++)
   {
     next = first + second;
     if (next == num)
         return 1;
     first = second;
     second = next;
   }

   return 0;
}
