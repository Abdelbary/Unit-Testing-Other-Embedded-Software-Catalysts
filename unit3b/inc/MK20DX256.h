//===================================================
// Microprocessor Register File for MK20DX256
//
// Started by Mark VanderVoord 2014
// Free for any use by anyone
// Provided as-is without guarantees that anything works
//===================================================

#ifndef MK20DX256_H
#define MK20DX256_H

//Convenience definitions for creating register sets
#define REGISTER volatile unsigned int
#define BIT_TO_MASK(a) (1u << (a))

#ifdef TEST
#define INSTANCE(name, address, template) PORT_##address; template PORT_##address;
#else
#define INSTANCE(name, address, template) const template* name = (*(template*)(address))
#endif

//===================================================
// GPIO
//===================================================

typedef volatile struct _REGISTERS_GPIO_T
{
    REGISTER PDOR;     //Port Data Output Register
    REGISTER PSOR;     //Port Set Output Register
    REGISTER PCOR;     //Port Clear Output Register
    REGISTER PTOR;     //Port Toggle Output Register
    REGISTER PDIR;     //Port Data Input Register
    REGISTER PDDR;     //Port Data Direction Register
} REGISTERS_GPIO_T;

#ifdef TEST
REGISTERS_GPIO_T PORTA;
REGISTERS_GPIO_T PORTB;
REGISTERS_GPIO_T PORTC;
REGISTERS_GPIO_T PORTD;
REGISTERS_GPIO_T PORTE;
#else
#define PORTA (*(REGISTERS_GPIO_T*)(0x400FF000))
#define PORTB (*(REGISTERS_GPIO_T*)(0x400FF040))
#define PORTC (*(REGISTERS_GPIO_T*)(0x400FF080))
#define PORTD (*(REGISTERS_GPIO_T*)(0x400FF0C0))
#define PORTE (*(REGISTERS_GPIO_T*)(0x400FF100))
#endif

//===================================================
// GPIO  CONFIG
//===================================================

typedef volatile struct _REGISTERS_GPIO_CFG_T
{
    REGISTER PCR[32];      //Pin Control Register
    REGISTER GPCLR;        //Global Pin Control Low Register
    REGISTER GPCHR;        //Global Pin Control High Register
    REGISTER unusedA[2];
    REGISTER ISFR;         //Interrupt Status Flag Register
} REGISTERS_GPIO_CFG_T;

#ifdef TEST
REGISTERS_GPIO_CFG_T PORTA_CFG;
REGISTERS_GPIO_CFG_T PORTB_CFG;
REGISTERS_GPIO_CFG_T PORTC_CFG;
REGISTERS_GPIO_CFG_T PORTD_CFG;
REGISTERS_GPIO_CFG_T PORTE_CFG;
#else
#define PORTA_CFG (*(REGISTERS_GPIO_CFG_T*)(0x40049000))
#define PORTB_CFG (*(REGISTERS_GPIO_CFG_T*)(0x4004A000))
#define PORTC_CFG (*(REGISTERS_GPIO_CFG_T*)(0x4004B000))
#define PORTD_CFG (*(REGISTERS_GPIO_CFG_T*)(0x4004C000))
#define PORTE_CFG (*(REGISTERS_GPIO_CFG_T*)(0x4004D000))
#endif

//===================================================

#endif //MK20DX256_H
