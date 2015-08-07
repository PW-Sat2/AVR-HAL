/*
 * pins.h
 *
 * Created: 2015-07-29 00:07:24
 *  Author: begreen
 */ 


#ifndef HAL_AVR_MCU_ATMEGA128A_PINS_H_
#define HAL_AVR_MCU_ATMEGA128A_PINS_H_

#include <avr/pgmspace.h>

/* MCU pin map */
const GPIOPinDescr_t GPIOPin_t_descr[] PROGMEM = {
    { 0, 0, 0, 0},  // 0 -- artificial pin
    { 0, 0, 0, 0},  // 1 -- ~PEN
    {&DDRE, &PORTE, &PINE, 0},  // 2 -- RXD0/(PDI) PE0
    {&DDRE, &PORTE, &PINE, 1},  // 3 -- (TXD0/PDO) PE1
    {&DDRE, &PORTE, &PINE, 2},  // 4 -- (XCK0/AIN0) PE2
    {&DDRE, &PORTE, &PINE, 3},  // 5 -- (OC3A/AIN1) PE3
    {&DDRE, &PORTE, &PINE, 4},  // 6 -- (OC3B/INT4) PE4
    {&DDRE, &PORTE, &PINE, 5},  // 7 -- (OC3C/INT5) PE5
    {&DDRE, &PORTE, &PINE, 6},  // 8 -- (T3/INT6) PE6
    {&DDRE, &PORTE, &PINE, 7},  // 9 -- (ICP3/INT7) PE7
    {&DDRB, &PORTB, &PINB, 0},  // 10 -- (SS) PB0
    {&DDRB, &PORTB, &PINB, 1},  // 11 -- (SCK) PB1
    {&DDRB, &PORTB, &PINB, 2},  // 12 -- (MOSI) PB2
    {&DDRB, &PORTB, &PINB, 3},  // 13 -- (MISO) PB3
    {&DDRB, &PORTB, &PINB, 4},  // 14 -- (OC0) PB4
    {&DDRB, &PORTB, &PINB, 5},  // 15 -- (OC1A) PB5
    {&DDRB, &PORTB, &PINB, 6},  // 16 -- (OC1B) PB6
    {&DDRB, &PORTB, &PINB, 7},  // 17 -- (OC2/OC1C) PB7
    {&DDRG, &PORTG, &PING, 3},  // 18 -- TOSC2/PG3
    {&DDRG, &PORTG, &PING, 4},  // 19 -- TOSC1/PG4
    { 0, 0, 0, 0},  // 20 -- ~RESET
    { 0, 0, 0, 0},  // 21 -- VCC
    { 0, 0, 0, 0},  // 22 -- GND
    { 0, 0, 0, 0},  // 23 -- XTAL2
    { 0, 0, 0, 0},  // 24 -- XTAL1
    {&DDRD, &PORTD, &PIND, 0},  // 25 -- (SCL/INT0) PD0
    {&DDRD, &PORTD, &PIND, 1},  // 26 -- (SDA/INT1) PD1
    {&DDRD, &PORTD, &PIND, 2},  // 27 -- (RXD1/INT2) PD2
    {&DDRD, &PORTD, &PIND, 3},  // 28 -- (TXD1/INT3) PD3
    {&DDRD, &PORTD, &PIND, 4},  // 29 -- (ICP1) PD4
    {&DDRD, &PORTD, &PIND, 5},  // 30 -- (XCK1) PD5
    {&DDRD, &PORTD, &PIND, 6},  // 31 -- (T1) PD6
    {&DDRD, &PORTD, &PIND, 7},  // 32 -- (T2) PD7
    {&DDRG, &PORTG, &PING, 0},  // 33 -- PG0(WR)
    {&DDRG, &PORTG, &PING, 1},  // 34 -- PG1(RD)
    {&DDRC, &PORTC, &PINC, 0},  // 35 -- PC0 (A8)
    {&DDRC, &PORTC, &PINC, 1},  // 36 -- PC1 (A9)
    {&DDRC, &PORTC, &PINC, 2},  // 37 -- PC2 (A10)
    {&DDRC, &PORTC, &PINC, 3},  // 38 -- PC3 (A11)
    {&DDRC, &PORTC, &PINC, 4},  // 39 -- PC4 (A12)
    {&DDRC, &PORTC, &PINC, 5},  // 40 -- PC5 (A13)
    {&DDRC, &PORTC, &PINC, 6},  // 41 -- PC6 (A14)
    {&DDRC, &PORTC, &PINC, 7},  // 42 -- PC7 (A15)
    {&DDRG, &PORTG, &PING, 2},  // 43 -- PG2(ALE)
    {&DDRA, &PORTA, &PINA, 7},  // 44 -- PA7 (AD7)
    {&DDRA, &PORTA, &PINA, 6},  // 45 -- PA6 (AD6)
    {&DDRA, &PORTA, &PINA, 5},  // 46 -- PA5 (AD5)
    {&DDRA, &PORTA, &PINA, 4},  // 47 -- PA4 (AD4)
    {&DDRA, &PORTA, &PINA, 3},  // 48 -- PA3 (AD3)
    {&DDRA, &PORTA, &PINA, 2},  // 49 -- PA2 (AD2)
    {&DDRA, &PORTA, &PINA, 1},  // 50 -- PA1 (AD1)
    {&DDRA, &PORTA, &PINA, 0},  // 51 -- PA0 (AD0)
    { 0, 0, 0, 0},  // 52 -- VCC
    { 0, 0, 0, 0},  // 53 -- GND
    {&DDRF, &PORTF, &PINF, 7},  // 54 -- PF7 (ADC7/TDI)
    {&DDRF, &PORTF, &PINF, 6},  // 55 -- PF6 (ADC6/TDO)
    {&DDRF, &PORTF, &PINF, 5},  // 56 -- PF5 (ADC5/TMS)
    {&DDRF, &PORTF, &PINF, 4},  // 57 -- PF4 (ADC4/TCK)
    {&DDRF, &PORTF, &PINF, 3},  // 58 -- PF3 (ADC3)
    {&DDRF, &PORTF, &PINF, 2},  // 59 -- PF2 (ADC2)
    {&DDRF, &PORTF, &PINF, 1},  // 60 -- PF1 (ADC1)
    {&DDRF, &PORTF, &PINF, 0},  // 61 -- PF0 (ADC0)
    { 0, 0, 0, 0},  // 62 -- AREF
    { 0, 0, 0, 0},  // 63 -- GND
    { 0, 0, 0, 0}  // 64 -- AVCC
};

const SPIPinDescr_t SPIPin_t_descr = {
        12, 13, 11, 10};

#endif  // HAL_AVR_MCU_ATMEGA128A_PINS_H_
