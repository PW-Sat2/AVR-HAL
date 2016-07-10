#ifndef HAL_MCU_ATMEGA2560_PINS_H_
#define HAL_MCU_ATMEGA2560_PINS_H_

#include "periph/GPIOPinDescriptor.h"
#include <avr/io.h>

constexpr static GPIOPinDescriptor GPIOPinMap[] = {
{0, 0, 0, 0},                //   0 -- artificial pin
{&DDRG, &PORTG, &PING, 5},    //   1 -- PG5 ( OC0B )
{&DDRE, &PORTE, &PINE, 0},    //   2 -- PE0 ( RXD0/PCINT8 )
{&DDRE, &PORTE, &PINE, 1},    //   3 -- PE1 ( TXD0 )
{&DDRE, &PORTE, &PINE, 2},    //   4 -- PE2 ( XCK0/AIN0 )
{&DDRE, &PORTE, &PINE, 3},    //   5 -- PE3 ( OC3A/AIN1 )
{&DDRE, &PORTE, &PINE, 4},    //   6 -- PE4 ( OC3B/INT4 )
{&DDRE, &PORTE, &PINE, 5},    //   7 -- PE5 ( OC3C/INT5 )
{&DDRE, &PORTE, &PINE, 6},    //   8 -- PE6 ( T3/INT6 )
{&DDRE, &PORTE, &PINE, 7},    //   9 -- PE7 ( CLKO/ICP3/INT7 )
{0, 0, 0, 0},                 //  10 -- VCC
{0, 0, 0, 0},                 //  11 -- GND
{&DDRH, &PORTH, &PINH, 0},    //  12 -- PH0 ( RXD2 )
{&DDRH, &PORTH, &PINH, 1},    //  13 -- PH1 ( TXD2 )
{&DDRH, &PORTH, &PINH, 2},    //  14 -- PH2 ( XCK2 )
{&DDRH, &PORTH, &PINH, 3},    //  15 -- PH3 ( OC4A )
{&DDRH, &PORTH, &PINH, 4},    //  16 -- PH4 ( OC4B )
{&DDRH, &PORTH, &PINH, 5},    //  17 -- PH5 ( OC4C )
{&DDRH, &PORTH, &PINH, 6},    //  18 -- PH6 ( OC2B )
{&DDRB, &PORTB, &PINB, 0},    //  19 -- PB0 ( SS/PCINT0 )
{&DDRB, &PORTB, &PINB, 1},    //  20 -- PB1 ( SCK/PCINT1 )
{&DDRB, &PORTB, &PINB, 2},    //  21 -- PB2 ( MOSI/PCINT2 )
{&DDRB, &PORTB, &PINB, 3},    //  22 -- PB3 ( MISO/PCINT3 )
{&DDRB, &PORTB, &PINB, 4},    //  23 -- PB4 ( OC2A/PCINT4 )
{&DDRB, &PORTB, &PINB, 5},    //  24 -- PB5 ( OC1A/PCINT5 )
{&DDRB, &PORTB, &PINB, 6},    //  25 -- PB6 ( OC1B/PCINT6 )
{&DDRB, &PORTB, &PINB, 7},    //  26 -- PB7 ( OC0A/OC1C/PCINT7 )
{&DDRH, &PORTH, &PINH, 7},    //  27 -- PH7 ( T4 )
{&DDRG, &PORTG, &PING, 3},    //  28 -- PG3 ( TOSC2 )
{&DDRG, &PORTG, &PING, 4},    //  29 -- PG4 ( TOSC1 )
{0, 0, 0, 0},                 //  30 -- RESET
{0, 0, 0, 0},                 //  31 -- VCC
{0, 0, 0, 0},                 //  32 -- GND
{0, 0, 0, 0},                 //  33 -- XTAL2
{0, 0, 0, 0},                 //  34 -- XTAL1
{&DDRL, &PORTL, &PINL, 0},    //  35 -- PL0 ( ICP4 )
{&DDRL, &PORTL, &PINL, 1},    //  36 -- PL1 ( ICP5 )
{&DDRL, &PORTL, &PINL, 2},    //  37 -- PL2 ( T5 )
{&DDRL, &PORTL, &PINL, 3},    //  38 -- PL3 ( OC5A )
{&DDRL, &PORTL, &PINL, 4},    //  39 -- PL4 ( OC5B )
{&DDRL, &PORTL, &PINL, 5},    //  40 -- PL5 ( OC5C )
{&DDRL, &PORTL, &PINL, 6},    //  41 -- PL6
{&DDRL, &PORTL, &PINL, 7},    //  42 -- PL7
{&DDRD, &PORTD, &PIND, 0},    //  43 -- PD0 ( SCL/INT0 )
{&DDRD, &PORTD, &PIND, 1},    //  44 -- PD1 ( SDA/INT1 )
{&DDRD, &PORTD, &PIND, 2},    //  45 -- PD2 ( RXDI/INT2 )
{&DDRD, &PORTD, &PIND, 3},    //  46 -- PD3 ( TXD1/INT3 )
{&DDRD, &PORTD, &PIND, 4},    //  47 -- PD4 ( ICP1 )
{&DDRD, &PORTD, &PIND, 5},    //  48 -- PD5 ( XCK1 )
{&DDRD, &PORTD, &PIND, 6},    //  49 -- PD6 ( T1 )
{&DDRD, &PORTD, &PIND, 7},    //  50 -- PD7 ( T0 )
{&DDRG, &PORTG, &PING, 0},    //  51 -- PG0 ( WR )
{&DDRG, &PORTG, &PING, 1},    //  52 -- PG1 ( RD )
{&DDRC, &PORTC, &PINC, 0},    //  53 -- PC0 ( A8 )
{&DDRC, &PORTC, &PINC, 1},    //  54 -- PC1 ( A9 )
{&DDRC, &PORTC, &PINC, 2},    //  55 -- PC2 ( A10 )
{&DDRC, &PORTC, &PINC, 3},    //  56 -- PC3 ( A11 )
{&DDRC, &PORTC, &PINC, 4},    //  57 -- PC4 ( A12 )
{&DDRC, &PORTC, &PINC, 5},    //  58 -- PC5 ( A13 )
{&DDRC, &PORTC, &PINC, 6},    //  59 -- PC6 ( A14 )
{&DDRC, &PORTC, &PINC, 7},    //  60 -- PC7 ( A15 )
{0, 0, 0, 0},                 //  61 -- VCC
{0, 0, 0, 0},                 //  62 -- GND
{&DDRJ, &PORTJ, &PINJ, 0},    //  63 -- PJ0 ( RXD3/PCINT9 )
{&DDRJ, &PORTJ, &PINJ, 1},    //  64 -- PJ1 ( TXD3/PCINT10 )
{&DDRJ, &PORTJ, &PINJ, 2},    //  65 -- PJ2 ( XCK3/PCINT11 )
{&DDRJ, &PORTJ, &PINJ, 3},    //  66 -- PJ3 ( PCINT12 )
{&DDRJ, &PORTJ, &PINJ, 4},    //  67 -- PJ4 ( PCINT13 )
{&DDRJ, &PORTJ, &PINJ, 5},    //  68 -- PJ5 ( PCINT14 )
{&DDRJ, &PORTJ, &PINJ, 6},    //  69 -- PJ6 ( PCINT 15 )
{&DDRG, &PORTG, &PING, 2},    //  70 -- PG2 ( ALE )
{&DDRA, &PORTA, &PINA, 7},    //  71 -- PA7 ( AD7 )
{&DDRA, &PORTA, &PINA, 6},    //  72 -- PA6 ( AD6 )
{&DDRA, &PORTA, &PINA, 5},    //  73 -- PA5 ( AD5 )
{&DDRA, &PORTA, &PINA, 4},    //  74 -- PA4 ( AD4 )
{&DDRA, &PORTA, &PINA, 3},    //  75 -- PA3 ( AD3 )
{&DDRA, &PORTA, &PINA, 2},    //  76 -- PA2 ( AD2 )
{&DDRA, &PORTA, &PINA, 1},    //  77 -- PA1 ( AD1 )
{&DDRA, &PORTA, &PINA, 0},    //  78 -- PA0 ( AD0 )
{&DDRJ, &PORTJ, &PINJ, 7},    //  79 -- PJ7
{0, 0, 0, 0},                 //  80 -- VCC
{0, 0, 0, 0},                 //  81 -- GND
{&DDRK, &PORTK, &PINK, 7},    //  82 -- PK7 ( ADC15/PCINT23 )
{&DDRK, &PORTK, &PINK, 6},    //  83 -- PK6 ( ADC14/PCINT22 )
{&DDRK, &PORTK, &PINK, 5},    //  84 -- PK5 ( ADC13/PCINT21 )
{&DDRK, &PORTK, &PINK, 4},    //  85 -- PK4 ( ADC12/PCINT20 )
{&DDRK, &PORTK, &PINK, 3},    //  86 -- PK3 ( ADC11/PCINT19 )
{&DDRK, &PORTK, &PINK, 2},    //  87 -- PK2 ( ADC10/PCINT18 )
{&DDRK, &PORTK, &PINK, 1},    //  88 -- PK1 ( ADC9/PCINT17 )
{&DDRK, &PORTK, &PINK, 0},    //  89 -- PK0 ( ADC8/PCINT16 )
{&DDRF, &PORTF, &PINF, 7},    //  90 -- PF7 ( ADC7 )
{&DDRF, &PORTF, &PINF, 6},    //  91 -- PF6 ( ADC6 )
{&DDRF, &PORTF, &PINF, 5},    //  92 -- PF5 ( ADC5/TMS )
{&DDRF, &PORTF, &PINF, 4},    //  93 -- PF4 ( ADC4/TMK )
{&DDRF, &PORTF, &PINF, 3},    //  94 -- PF3 ( ADC3 )
{&DDRF, &PORTF, &PINF, 2},    //  95 -- PF2 ( ADC2 )
{&DDRF, &PORTF, &PINF, 1},    //  96 -- PF1 ( ADC1 )
{&DDRF, &PORTF, &PINF, 0},    //  97 -- PF0 ( ADC0 )
{0, 0, 0, 0},                 //  98 -- AREF
{0, 0, 0, 0},                 //  99 -- GND
{0, 0, 0, 0},                 // 100 -- AVCC
};

#endif  // HAL_MCU_ATMEGA2560_PINS_H_
