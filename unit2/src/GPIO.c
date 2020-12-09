#include "GPIO.h"
#include "MK20DX256.h"
#include <stdio.h>

uint8 GPIO_SetPinDirectionAsOutput(gpio_pin_t pin)
{
    if(pin < 0 || pin > 31)
        return GPIO_NOK;

    PORTC.PDDR |= BIT_TO_MASK(pin);
    return GPIO_OK;
}

uint8 GPIO_SetPinDirectionAsInput(gpio_pin_t pin)
{
    if(pin < 0 || pin > 31)
        return GPIO_NOK;

    PORTC.PDDR &= ~(BIT_TO_MASK(pin));

    return GPIO_OK;
}

 uint8 GPIO_ReadPin(gpio_pin_t pin  , BOOL * state)
 {
    if(pin < 0 || pin > 31 || state == NULL)
        return GPIO_NOK;
     *state = ((PORTC.PDIR & BIT_TO_MASK(pin)) != 0) ;

     return GPIO_OK;
 }


 uint8 GPIO_SetPin(gpio_pin_t  pin, BOOL state)
 {
    if(pin < 0 || pin > 31)
        return GPIO_NOK;


    if(state == 1)
        PORTC.PDOR |= BIT_TO_MASK(pin);
    else
        PORTC.PDOR &= ~BIT_TO_MASK(pin);
    
     
    return GPIO_OK;
 }

 uint8 GPIO_ReadPort(REGISTERS_GPIO_T port, uint32 * state )
 {
     if(state == NULL)
        return GPIO_NOK;
     *state = PORTC.PDIR ;
     return GPIO_OK;
 }

 void GPIO_init()
 {
     PORTC.PDDR =  0xf0f0f0f0;
     PORTC.PSOR =  0x0f0f0f0f;
     PORTC.PCOR =  0x0000ffff;
 }