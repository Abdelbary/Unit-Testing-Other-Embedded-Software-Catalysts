#include "Filter.h"
#include "MK20DX256.h"


uint16 FilterAddValue(uint16 prevVal , uint16 newVal )
{
    return (uint16)(((uint32)(3*prevVal)+newVal)/4);
}