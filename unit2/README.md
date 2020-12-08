### GPIO Project Requirements
* Each pin can be set as input/output
* Each pin can be set high or low
* Each pin can be read
* Each port can be read in one word
* Has init function to config defaults by pin
* Each pin can be configured for gpio
* Each pin can have its active polarity reversed
* We will support 32bits on port C.
* We will ignore other features for now (pulldown, pullup, interrupts, lock, etc)
__________________________________________________________________________


### Detailed Design:
/**********************************
function prototype: uint8 GPIO_SetPinDirectionAsOutput(gpio_pin ,gpio_port_t)
@ret    :   uint8 [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin pin number from 0 to 32
        [in] gpio_port_t port num 
Discrip :  function should set given pin to output
**********************************/

/**********************************
function prototype: uint8 GPIO_SetPinDirectionAsInput(gpio_pin ,gpio_port_t)
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin pin number from 0 to 32
        [in] gpio_port_t port num 
Discrip : function should set given pin to input
**********************************/

/**********************************
function prototype: uint8 GPIO_ReadPin(gpio_pin ,gpio_port_t, BOOL * state)
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin pin number from 0 to 32
        [in] gpio_port_t port num 
        [out] BOOL state
Discrip : function should read givin pin number state
**********************************/

/**********************************
function prototype: uint8 GPIO_SetPin(gpio_pin ,gpio_port_t, BOOL state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_pin pin number from 0 to 32
        [in] gpio_port_t port num 
        [in] BOOL value to set
Discrip : function should set given pin value to high
**********************************/

/**********************************
function prototype: uint8 GPIO_ReadPort(gpio_port_t, uint16 * state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_port_t port num 
        [in] uint16 current state of the port
Discrip : function should read the port as a whole word
**********************************/

/**********************************
function prototype: uint8 GPIO_init()
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  
Discrip : function should initalize the pins to default state
**********************************/

/**********************************
function prototype: uint8 GPIO_reversePolarity(gpio_port_t, uint16 * state )
@ret    :    int [0->GPIO_OK , -1->GPIO_NOK]
@param  [in] gpio_port_t port num 
        [in] uint16 current state of the port
Discrip : function should reverse the polarity of the givien pin
**********************************/