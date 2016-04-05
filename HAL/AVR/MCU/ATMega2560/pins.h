#ifndef HAL_AVR_MCU_ATMEGA2560_PINS_H_
#define HAL_AVR_MCU_ATMEGA2560_PINS_H_

#include <avr/pgmspace.h>
#include "SPI.h"

/* MCU pin map */
const GPIOPinDescr_t GPIOPin_t_descr[] PROGMEM = {
{ 0, 0, 0, 0},                  // 0 -- artificial pin
{&DDRG, &PORTG, &PING, 5},    // 1 -- PG5 ( OC0B )             -- Arduino Mega2560: Digital pin 4 (PWM)
{&DDRE, &PORTE, &PINE, 0},    // 2 -- PE0 ( RXD0/PCINT8 )      -- Arduino Mega2560: Digital pin 0 (RX0)
{&DDRE, &PORTE, &PINE, 1},    // 3 -- PE1 ( TXD0 )             -- Arduino Mega2560: Digital pin 1 (TX0)
{&DDRE, &PORTE, &PINE, 2},    // 4 -- PE2 ( XCK0/AIN0 )        -- Arduino Mega2560:  
{&DDRE, &PORTE, &PINE, 3},    // 5 -- PE3 ( OC3A/AIN1 )        -- Arduino Mega2560: Digital pin 5 (PWM)
{&DDRE, &PORTE, &PINE, 4},    // 6 -- PE4 ( OC3B/INT4 )        -- Arduino Mega2560: Digital pin 2 (PWM)
{&DDRE, &PORTE, &PINE, 5},    // 7 -- PE5 ( OC3C/INT5 )        -- Arduino Mega2560: Digital pin 3 (PWM)
{&DDRE, &PORTE, &PINE, 6},    // 8 -- PE6 ( T3/INT6 )          -- Arduino Mega2560:  
{&DDRE, &PORTE, &PINE, 7},    // 9 -- PE7 ( CLKO/ICP3/INT7 )   -- Arduino Mega2560:  
{ 0, 0, 0, 0},                // 10 -- VCC                     -- Arduino Mega2560: VCC
{ 0, 0, 0, 0},                // 11 -- GND                     -- Arduino Mega2560: GND
{&DDRH, &PORTH, &PINH, 0},    // 12 -- PH0 ( RXD2 )            -- Arduino Mega2560: Digital pin 17 (RX2)
{&DDRH, &PORTH, &PINH, 1},    // 13 -- PH1 ( TXD2 )            -- Arduino Mega2560: Digital pin 16 (TX2)
{&DDRH, &PORTH, &PINH, 2},    // 14 -- PH2 ( XCK2 )            -- Arduino Mega2560:  
{&DDRH, &PORTH, &PINH, 3},    // 15 -- PH3 ( OC4A )            -- Arduino Mega2560: Digital pin 6 (PWM)
{&DDRH, &PORTH, &PINH, 4},    // 16 -- PH4 ( OC4B )            -- Arduino Mega2560: Digital pin 7 (PWM)
{&DDRH, &PORTH, &PINH, 5},    // 17 -- PH5 ( OC4C )            -- Arduino Mega2560: Digital pin 8 (PWM)
{&DDRH, &PORTH, &PINH, 6},    // 18 -- PH6 ( OC2B )            -- Arduino Mega2560: Digital pin 9 (PWM)
{&DDRB, &PORTB, &PINB, 0},    // 19 -- PB0 ( SS/PCINT0 )       -- Arduino Mega2560: Digital pin 53 (SS)
{&DDRB, &PORTB, &PINB, 1},    // 20 -- PB1 ( SCK/PCINT1 )      -- Arduino Mega2560: Digital pin 52 (SCK)
{&DDRB, &PORTB, &PINB, 2},    // 21 -- PB2 ( MOSI/PCINT2 )     -- Arduino Mega2560: Digital pin 51 (MOSI)
{&DDRB, &PORTB, &PINB, 3},    // 22 -- PB3 ( MISO/PCINT3 )     -- Arduino Mega2560: Digital pin 50 (MISO)
{&DDRB, &PORTB, &PINB, 4},    // 23 -- PB4 ( OC2A/PCINT4 )     -- Arduino Mega2560: Digital pin 10 (PWM)
{&DDRB, &PORTB, &PINB, 5},    // 24 -- PB5 ( OC1A/PCINT5 )     -- Arduino Mega2560: Digital pin 11 (PWM)
{&DDRB, &PORTB, &PINB, 6},    // 25 -- PB6 ( OC1B/PCINT6 )     -- Arduino Mega2560: Digital pin 12 (PWM)
{&DDRB, &PORTB, &PINB, 7},    // 26 -- PB7 ( OC0A/OC1C/PCINT7 )-- Arduino Mega2560: Digital pin 13 (PWM)
{&DDRH, &PORTH, &PINH, 7},    // 27 -- PH7 ( T4 )              -- Arduino Mega2560:  
{&DDRG, &PORTG, &PING, 3},    // 28 -- PG3 ( TOSC2 )           -- Arduino Mega2560:  
{&DDRG, &PORTG, &PING, 4},    // 29 -- PG4 ( TOSC1 )           -- Arduino Mega2560:  
{ 0, 0, 0, 0},                // 30 -- RESET                   -- Arduino Mega2560: RESET
{ 0, 0, 0, 0},                // 31 -- VCC                     -- Arduino Mega2560: VCC
{ 0, 0, 0, 0},                // 32 -- GND                     -- Arduino Mega2560: GND
{ 0, 0, 0, 0},                // 33 -- XTAL2                   -- Arduino Mega2560: XTAL2
{ 0, 0, 0, 0},                // 34 -- XTAL1                   -- Arduino Mega2560: XTAL1
{&DDRL, &PORTL, &PINL, 0},    // 35 -- PL0 ( ICP4 )            -- Arduino Mega2560: Digital pin 49
{&DDRL, &PORTL, &PINL, 1},    // 36 -- PL1 ( ICP5 )            -- Arduino Mega2560: Digital pin 48
{&DDRL, &PORTL, &PINL, 2},    // 37 -- PL2 ( T5 )              -- Arduino Mega2560: Digital pin 47
{&DDRL, &PORTL, &PINL, 3},    // 38 -- PL3 ( OC5A )            -- Arduino Mega2560: Digital pin 46 (PWM)
{&DDRL, &PORTL, &PINL, 4},    // 39 -- PL4 ( OC5B )            -- Arduino Mega2560: Digital pin 45 (PWM)
{&DDRL, &PORTL, &PINL, 5},    // 40 -- PL5 ( OC5C )            -- Arduino Mega2560: Digital pin 44 (PWM)
{&DDRL, &PORTL, &PINL, 6},    // 41 -- PL6                     -- Arduino Mega2560: Digital pin 43
{&DDRL, &PORTL, &PINL, 7},    // 42 -- PL7                     -- Arduino Mega2560: Digital pin 42
{&DDRD, &PORTD, &PIND, 0},    // 43 -- PD0 ( SCL/INT0 )        -- Arduino Mega2560: Digital pin 21 (SCL)
{&DDRD, &PORTD, &PIND, 1},    // 44 -- PD1 ( SDA/INT1 )        -- Arduino Mega2560: Digital pin 20 (SDA)
{&DDRD, &PORTD, &PIND, 2},    // 45 -- PD2 ( RXDI/INT2 )       -- Arduino Mega2560: Digital pin 19 (RX1)
{&DDRD, &PORTD, &PIND, 3},    // 46 -- PD3 ( TXD1/INT3 )       -- Arduino Mega2560: Digital pin 18 (TX1)
{&DDRD, &PORTD, &PIND, 4},    // 47 -- PD4 ( ICP1 )            -- Arduino Mega2560:  
{&DDRD, &PORTD, &PIND, 5},    // 48 -- PD5 ( XCK1 )            -- Arduino Mega2560:  
{&DDRD, &PORTD, &PIND, 6},    // 49 -- PD6 ( T1 )              -- Arduino Mega2560:  
{&DDRD, &PORTD, &PIND, 7},    // 50 -- PD7 ( T0 )              -- Arduino Mega2560: Digital pin 38
{&DDRG, &PORTG, &PING, 0},    // 51 -- PG0 ( WR )              -- Arduino Mega2560: Digital pin 41
{&DDRG, &PORTG, &PING, 1},    // 52 -- PG1 ( RD )              -- Arduino Mega2560: Digital pin 40
{&DDRC, &PORTC, &PINC, 0},    // 53 -- PC0 ( A8 )              -- Arduino Mega2560: Digital pin 37
{&DDRC, &PORTC, &PINC, 1},    // 54 -- PC1 ( A9 )              -- Arduino Mega2560: Digital pin 36
{&DDRC, &PORTC, &PINC, 2},    // 55 -- PC2 ( A10 )             -- Arduino Mega2560: Digital pin 35
{&DDRC, &PORTC, &PINC, 3},    // 56 -- PC3 ( A11 )             -- Arduino Mega2560: Digital pin 34
{&DDRC, &PORTC, &PINC, 4},    // 57 -- PC4 ( A12 )             -- Arduino Mega2560: Digital pin 33
{&DDRC, &PORTC, &PINC, 5},    // 58 -- PC5 ( A13 )             -- Arduino Mega2560: Digital pin 32
{&DDRC, &PORTC, &PINC, 6},    // 59 -- PC6 ( A14 )             -- Arduino Mega2560: Digital pin 31
{&DDRC, &PORTC, &PINC, 7},    // 60 -- PC7 ( A15 )             -- Arduino Mega2560: Digital pin 30
{ 0, 0, 0, 0},                // 61 -- VCC                     -- Arduino Mega2560: VCC
{ 0, 0, 0, 0},                // 62 -- GND                     -- Arduino Mega2560: GND
{&DDRJ, &PORTJ, &PINJ, 0},    // 63 -- PJ0 ( RXD3/PCINT9 )     -- Arduino Mega2560: Digital pin 15 (RX3)
{&DDRJ, &PORTJ, &PINJ, 1},    // 64 -- PJ1 ( TXD3/PCINT10 )    -- Arduino Mega2560: Digital pin 14 (TX3)
{&DDRJ, &PORTJ, &PINJ, 2},    // 65 -- PJ2 ( XCK3/PCINT11 )    -- Arduino Mega2560:  
{&DDRJ, &PORTJ, &PINJ, 3},    // 66 -- PJ3 ( PCINT12 )         -- Arduino Mega2560:  
{&DDRJ, &PORTJ, &PINJ, 4},    // 67 -- PJ4 ( PCINT13 )         -- Arduino Mega2560:  
{&DDRJ, &PORTJ, &PINJ, 5},    // 68 -- PJ5 ( PCINT14 )         -- Arduino Mega2560:  
{&DDRJ, &PORTJ, &PINJ, 6},    // 69 -- PJ6 ( PCINT 15 )        -- Arduino Mega2560:  
{&DDRG, &PORTG, &PING, 2},    // 70 -- PG2 ( ALE )             -- Arduino Mega2560: Digital pin 39
{&DDRA, &PORTA, &PINA, 7},    // 71 -- PA7 ( AD7 )             -- Arduino Mega2560: Digital pin 29
{&DDRA, &PORTA, &PINA, 6},    // 72 -- PA6 ( AD6 )             -- Arduino Mega2560: Digital pin 28
{&DDRA, &PORTA, &PINA, 5},    // 73 -- PA5 ( AD5 )             -- Arduino Mega2560: Digital pin 27
{&DDRA, &PORTA, &PINA, 4},    // 74 -- PA4 ( AD4 )             -- Arduino Mega2560: Digital pin 26
{&DDRA, &PORTA, &PINA, 3},    // 75 -- PA3 ( AD3 )             -- Arduino Mega2560: Digital pin 25
{&DDRA, &PORTA, &PINA, 2},    // 76 -- PA2 ( AD2 )             -- Arduino Mega2560: Digital pin 24
{&DDRA, &PORTA, &PINA, 1},    // 77 -- PA1 ( AD1 )             -- Arduino Mega2560: Digital pin 23
{&DDRA, &PORTA, &PINA, 0},    // 78 -- PA0 ( AD0 )             -- Arduino Mega2560: Digital pin 22
{&DDRJ, &PORTJ, &PINJ, 7},    // 79 -- PJ7                     -- Arduino Mega2560:
{ 0, 0, 0, 0},                // 80 -- VCC                     -- Arduino Mega2560: VCC
{ 0, 0, 0, 0},                // 81 -- GND                     -- Arduino Mega2560: GND
{&DDRK, &PORTK, &PINK, 7},    // 82 -- PK7 ( ADC15/PCINT23 )   -- Arduino Mega2560: Analog pin 15
{&DDRK, &PORTK, &PINK, 6},    // 83 -- PK6 ( ADC14/PCINT22 )   -- Arduino Mega2560: Analog pin 14
{&DDRK, &PORTK, &PINK, 5},    // 84 -- PK5 ( ADC13/PCINT21 )   -- Arduino Mega2560: Analog pin 13
{&DDRK, &PORTK, &PINK, 4},    // 85 -- PK4 ( ADC12/PCINT20 )   -- Arduino Mega2560: Analog pin 12
{&DDRK, &PORTK, &PINK, 3},    // 86 -- PK3 ( ADC11/PCINT19 )   -- Arduino Mega2560: Analog pin 11
{&DDRK, &PORTK, &PINK, 2},    // 87 -- PK2 ( ADC10/PCINT18 )   -- Arduino Mega2560: Analog pin 10
{&DDRK, &PORTK, &PINK, 1},    // 88 -- PK1 ( ADC9/PCINT17 )    -- Arduino Mega2560: Analog pin 9
{&DDRK, &PORTK, &PINK, 0},    // 89 -- PK0 ( ADC8/PCINT16 )    -- Arduino Mega2560: Analog pin 8
{&DDRF, &PORTF, &PINF, 7},    // 90 -- PF7 ( ADC7 )            -- Arduino Mega2560: Analog pin 7
{&DDRF, &PORTF, &PINF, 6},    // 91 -- PF6 ( ADC6 )            -- Arduino Mega2560: Analog pin 6
{&DDRF, &PORTF, &PINF, 5},    // 92 -- PF5 ( ADC5/TMS )        -- Arduino Mega2560: Analog pin 5
{&DDRF, &PORTF, &PINF, 4},    // 93 -- PF4 ( ADC4/TMK )        -- Arduino Mega2560: Analog pin 4
{&DDRF, &PORTF, &PINF, 3},    // 94 -- PF3 ( ADC3 )            -- Arduino Mega2560: Analog pin 3
{&DDRF, &PORTF, &PINF, 2},    // 95 -- PF2 ( ADC2 )            -- Arduino Mega2560: Analog pin 2
{&DDRF, &PORTF, &PINF, 1},    // 96 -- PF1 ( ADC1 )            -- Arduino Mega2560: Analog pin 1
{&DDRF, &PORTF, &PINF, 0},    // 97 -- PF0 ( ADC0 )            -- Arduino Mega2560: Analog pin 0
{ 0, 0, 0, 0},                // 98 -- AREF                    -- Arduino Mega2560: Analog Reference
{ 0, 0, 0, 0},                // 99 -- GND                     -- Arduino Mega2560: GND
{ 0, 0, 0, 0},                // 100 -- AVCC                   -- Arduino Mega2560: VCC
};

/* SPI pin map */
const SPIPinDescr_t SPIPin_t_descr = {
    21, 20, 19
};

#endif  // HAL_AVR_MCU_ATMEGA2560_PINS_H_
