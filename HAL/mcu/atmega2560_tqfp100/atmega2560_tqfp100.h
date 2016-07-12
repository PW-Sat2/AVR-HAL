#ifndef HAL_MCU_ATMEGA2560_PINS_H_
#define HAL_MCU_ATMEGA2560_PINS_H_

#include "periph/GPIOPinDescriptor.h"
#include <avr/io.h>

constexpr static GPIOPinDescriptor GPIOPinMap[] = {
{0, 0, 0, 0},                                //   0 -- artificial pin
{(int)&DDRG, (int)&PORTG, (int)&PING, 5},    //   1 -- PG5 ( OC0B )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 0},    //   2 -- PE0 ( RXD0/PCINT8 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 1},    //   3 -- PE1 ( TXD0 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 2},    //   4 -- PE2 ( XCK0/AIN0 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 3},    //   5 -- PE3 ( OC3A/AIN1 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 4},    //   6 -- PE4 ( OC3B/INT4 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 5},    //   7 -- PE5 ( OC3C/INT5 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 6},    //   8 -- PE6 ( T3/INT6 )
{(int)&DDRE, (int)&PORTE, (int)&PINE, 7},    //   9 -- PE7 ( CLKO/ICP3/INT7 )
{0, 0, 0, 0},                                //  10 -- VCC
{0, 0, 0, 0},                                //  11 -- GND
{(int)&DDRH, (int)&PORTH, (int)&PINH, 0},    //  12 -- PH0 ( RXD2 )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 1},    //  13 -- PH1 ( TXD2 )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 2},    //  14 -- PH2 ( XCK2 )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 3},    //  15 -- PH3 ( OC4A )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 4},    //  16 -- PH4 ( OC4B )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 5},    //  17 -- PH5 ( OC4C )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 6},    //  18 -- PH6 ( OC2B )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 0},    //  19 -- PB0 ( SS/PCINT0 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 1},    //  20 -- PB1 ( SCK/PCINT1 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 2},    //  21 -- PB2 ( MOSI/PCINT2 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 3},    //  22 -- PB3 ( MISO/PCINT3 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 4},    //  23 -- PB4 ( OC2A/PCINT4 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 5},    //  24 -- PB5 ( OC1A/PCINT5 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 6},    //  25 -- PB6 ( OC1B/PCINT6 )
{(int)&DDRB, (int)&PORTB, (int)&PINB, 7},    //  26 -- PB7 ( OC0A/OC1C/PCINT7 )
{(int)&DDRH, (int)&PORTH, (int)&PINH, 7},    //  27 -- PH7 ( T4 )
{(int)&DDRG, (int)&PORTG, (int)&PING, 3},    //  28 -- PG3 ( TOSC2 )
{(int)&DDRG, (int)&PORTG, (int)&PING, 4},    //  29 -- PG4 ( TOSC1 )
{0, 0, 0, 0},                                //  30 -- RESET
{0, 0, 0, 0},                                //  31 -- VCC
{0, 0, 0, 0},                                //  32 -- GND
{0, 0, 0, 0},                                //  33 -- XTAL2
{0, 0, 0, 0},                                //  34 -- XTAL1
{(int)&DDRL, (int)&PORTL, (int)&PINL, 0},    //  35 -- PL0 ( ICP4 )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 1},    //  36 -- PL1 ( ICP5 )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 2},    //  37 -- PL2 ( T5 )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 3},    //  38 -- PL3 ( OC5A )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 4},    //  39 -- PL4 ( OC5B )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 5},    //  40 -- PL5 ( OC5C )
{(int)&DDRL, (int)&PORTL, (int)&PINL, 6},    //  41 -- PL6
{(int)&DDRL, (int)&PORTL, (int)&PINL, 7},    //  42 -- PL7
{(int)&DDRD, (int)&PORTD, (int)&PIND, 0},    //  43 -- PD0 ( SCL/INT0 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 1},    //  44 -- PD1 ( SDA/INT1 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 2},    //  45 -- PD2 ( RXDI/INT2 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 3},    //  46 -- PD3 ( TXD1/INT3 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 4},    //  47 -- PD4 ( ICP1 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 5},    //  48 -- PD5 ( XCK1 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 6},    //  49 -- PD6 ( T1 )
{(int)&DDRD, (int)&PORTD, (int)&PIND, 7},    //  50 -- PD7 ( T0 )
{(int)&DDRG, (int)&PORTG, (int)&PING, 0},    //  51 -- PG0 ( WR )
{(int)&DDRG, (int)&PORTG, (int)&PING, 1},    //  52 -- PG1 ( RD )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 0},    //  53 -- PC0 ( A8 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 1},    //  54 -- PC1 ( A9 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 2},    //  55 -- PC2 ( A10 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 3},    //  56 -- PC3 ( A11 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 4},    //  57 -- PC4 ( A12 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 5},    //  58 -- PC5 ( A13 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 6},    //  59 -- PC6 ( A14 )
{(int)&DDRC, (int)&PORTC, (int)&PINC, 7},    //  60 -- PC7 ( A15 )
{0, 0, 0, 0},                                //  61 -- VCC
{0, 0, 0, 0},                                //  62 -- GND
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 0},    //  63 -- PJ0 ( RXD3/PCINT9 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 1},    //  64 -- PJ1 ( TXD3/PCINT10 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 2},    //  65 -- PJ2 ( XCK3/PCINT11 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 3},    //  66 -- PJ3 ( PCINT12 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 4},    //  67 -- PJ4 ( PCINT13 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 5},    //  68 -- PJ5 ( PCINT14 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 6},    //  69 -- PJ6 ( PCINT 15 )
{(int)&DDRG, (int)&PORTG, (int)&PING, 2},    //  70 -- PG2 ( ALE )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 7},    //  71 -- PA7 ( AD7 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 6},    //  72 -- PA6 ( AD6 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 5},    //  73 -- PA5 ( AD5 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 4},    //  74 -- PA4 ( AD4 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 3},    //  75 -- PA3 ( AD3 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 2},    //  76 -- PA2 ( AD2 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 1},    //  77 -- PA1 ( AD1 )
{(int)&DDRA, (int)&PORTA, (int)&PINA, 0},    //  78 -- PA0 ( AD0 )
{(int)&DDRJ, (int)&PORTJ, (int)&PINJ, 7},    //  79 -- PJ7
{0, 0, 0, 0},                                //  80 -- VCC
{0, 0, 0, 0},                                //  81 -- GND
{(int)&DDRK, (int)&PORTK, (int)&PINK, 7},    //  82 -- PK7 ( ADC15/PCINT23 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 6},    //  83 -- PK6 ( ADC14/PCINT22 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 5},    //  84 -- PK5 ( ADC13/PCINT21 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 4},    //  85 -- PK4 ( ADC12/PCINT20 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 3},    //  86 -- PK3 ( ADC11/PCINT19 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 2},    //  87 -- PK2 ( ADC10/PCINT18 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 1},    //  88 -- PK1 ( ADC9/PCINT17 )
{(int)&DDRK, (int)&PORTK, (int)&PINK, 0},    //  89 -- PK0 ( ADC8/PCINT16 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 7},    //  90 -- PF7 ( ADC7 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 6},    //  91 -- PF6 ( ADC6 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 5},    //  92 -- PF5 ( ADC5/TMS )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 4},    //  93 -- PF4 ( ADC4/TMK )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 3},    //  94 -- PF3 ( ADC3 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 2},    //  95 -- PF2 ( ADC2 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 1},    //  96 -- PF1 ( ADC1 )
{(int)&DDRF, (int)&PORTF, (int)&PINF, 0},    //  97 -- PF0 ( ADC0 )
{0, 0, 0, 0},                                //  98 -- AREF
{0, 0, 0, 0},                                //  99 -- GND
{0, 0, 0, 0},                                // 100 -- AVCC
};

#endif  // HAL_MCU_ATMEGA2560_PINS_H_
