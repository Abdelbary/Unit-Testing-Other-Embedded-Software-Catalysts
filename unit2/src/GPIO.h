#ifndef GPIO_H
#define GPIO_H
#include "MK20DX256.h"
#define uint8  char
#define uint32  unsigned  int

#define GPIO_OK   0
#define GPIO_NOK -1
typedef enum
{
    False,
    True
}BOOL;

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}gpio_pin_t;



/**********************************
function prototype: uint8 GPIO_SetPinDirectionAsOutput(gpio_pin_t ,REGISTERS_GPIO_T)
@ret    :   uint8 [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin_t pin number from 0 to 32
        [in] gpio_port_t port num 
Discrip :  function should set given pin to output
**********************************/
uint8 GPIO_SetPinDirectionAsOutput(gpio_pin_t);

/**********************************
function prototype: uint8 GPIO_SetPinDirectionAsInput(gpio_pin_t ,gpio_port_t)
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin_t pin number from 0 to 32
        [in] gpio_port_t port num 
Discrip : function should set given pin to input
**********************************/
uint8 GPIO_SetPinDirectionAsInput(gpio_pin_t);

/**********************************
function prototype: uint8 GPIO_ReadPin(gpio_pin_t ,gpio_port_t, BOOL * state)
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin_t pin number from 0 to 32
        [in] gpio_port_t port num 
        [out] BOOL state
Discrip : function should read givin pin number state
**********************************/
 uint8 GPIO_ReadPin(gpio_pin_t  , BOOL * state);

/**********************************
function prototype: uint8 GPIO_SetPin(gpio_pin_t ,gpio_port_t, BOOL state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin_t pin number from 0 to 32
        [in] gpio_port_t port num 
        [in] BOOL value to set
Discrip : function should set given pin value to high
**********************************/
uint8 GPIO_SetPin(gpio_pin_t  , BOOL state);

/**********************************
function prototype: uint8 GPIO_ReadPort(gpio_port_t, uint32 * state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_port_t port num 
        [in] uint32 current state of the port
Discrip : function should read the port as a whole word
**********************************/
uint8 GPIO_ReadPort(REGISTERS_GPIO_T, uint32 * state );

/**********************************
function prototype: uint8 GPIO_init()
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  
Discrip : function should initalize the pins to default state
**********************************/
void GPIO_init();

/**********************************
function prototype: uint8 GPIO_reversePolarity(gpio_port_t, uint32 * state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_port_t port num 
        [in] uint32 current state of the port
Discrip : function should reverse the polarity of the givien pin
**********************************/
uint8 GPIO_reversePolarity(REGISTERS_GPIO_T, uint32 * state );
#endif //GPIO_H
