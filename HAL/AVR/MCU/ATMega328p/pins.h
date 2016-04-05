#ifndef HAL_AVR_MCU_ATMEGA328P_PINS_H_
#define HAL_AVR_MCU_ATMEGA328P_PINS_H_

#include <avr/pgmspace.h>
#include "SPI.h"

/* MCU pin map */
const GPIOPinDescr_t GPIOPin_t_descr[] PROGMEM = {
    { 0, 0, 0, 0},  // 0 -- artificial pin
    {&DDRC, &PORTC, &PINC, 6},  // 1 -- (PCINT14/~RESET) PC6
    {&DDRD, &PORTD, &PIND, 0},  // 2 -- (PCINT16/RXD) PD0
    {&DDRD, &PORTD, &PIND, 1},  // 3 -- (PCINT17/TXD) PD1
    {&DDRD, &PORTD, &PIND, 2},  // 4 -- (PCINT18/INT0) PD2
    {&DDRD, &PORTD, &PIND, 3},  // 5 -- (PCINT19/OC2B/INT1) PD3
    {&DDRD, &PORTD, &PIND, 4},  // 6 -- (PCINT20/XCK/T0) PD4
    { 0, 0, 0, 0},  // 7 -- VCC
    { 0, 0, 0, 0},  // 8 -- GND
    {&DDRB, &PORTB, &PINB, 6},  // 9 -- (PCINT6/XTAL1/TOSC1) PB6
    {&DDRB, &PORTB, &PINB, 7},  // 10 -- (PCINT7/XTAL2/TOSC2) PB7
    {&DDRD, &PORTD, &PIND, 5},  // 11 -- (PCINT21/OC0B/T1) PD5
    {&DDRD, &PORTD, &PIND, 6},  // 12 -- (PCINT22/OC0A/AIN0) PD6
    {&DDRD, &PORTD, &PIND, 7},  // 13 -- (PCINT23/AIN1) PD7
    {&DDRB, &PORTB, &PINB, 0},  // 14 -- (PCINT0/CLKO/ICP1) PB0
    {&DDRB, &PORTB, &PINB, 1},  // 15 -- PB1 (OC1A/PCINT1)
    {&DDRB, &PORTB, &PINB, 2},  // 16 -- PB2 (SS/OC1B/PCINT2)
    {&DDRB, &PORTB, &PINB, 3},  // 17 -- PB3 (MOSI/OC2A/PCINT3)
    {&DDRB, &PORTB, &PINB, 4},  // 18 -- PB4 (MISO/PCINT4)
    {&DDRB, &PORTB, &PINB, 5},  // 19 -- PB5 (SCK/PCINT5)
    { 0, 0, 0, 0},  // 20 -- AVCC
    { 0, 0, 0, 0},  // 21 -- AREF
    { 0, 0, 0, 0},  // 22 -- GND
    {&DDRC, &PORTC, &PINC, 0},  // 23 -- PC0 (ADC0/PCINT8)
    {&DDRC, &PORTC, &PINC, 1},  // 24 -- PC1 (ADC1/PCINT9)
    {&DDRC, &PORTC, &PINC, 2},  // 25 -- PC2 (ADC2/PCINT10)
    {&DDRC, &PORTC, &PINC, 3},  // 26 -- PC3 (ADC3/PCINT11)
    {&DDRC, &PORTC, &PINC, 4},  // 27 -- PC4 (ADC4/SDA/PCINT12)
    {&DDRC, &PORTC, &PINC, 5}    // 28 -- PC5 (ADC5/SCL/PCINT13)
};

/* SPI pin map */
const SPIPinDescr_t SPIPin_t_descr = {
	17, 18, 19, 16
};

#endif  // HAL_AVR_MCU_ATMEGA328P_PINS_H_
