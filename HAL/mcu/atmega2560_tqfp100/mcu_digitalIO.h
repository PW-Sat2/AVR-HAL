#ifndef HAL_MCU_ATMEGA2560_TQFP100_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA2560_TQFP100_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define PIN_DEF(port, pin) {(int)&DDR ## port, (int)&PORT ## port, (int)&PIN ## port, pin}

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
{0, 0, 0, 0},    //   0 -- artificial pin
PIN_DEF(G,5),    //   1 -- PG5 (OC0B)
PIN_DEF(E,0),    //   2 -- PE0 (RXD0/PCINT8)
PIN_DEF(E,1),    //   3 -- PE1 (TXD0)
PIN_DEF(E,2),    //   4 -- PE2 (XCK0/AIN0)
PIN_DEF(E,3),    //   5 -- PE3 (OC3A/AIN1)
PIN_DEF(E,4),    //   6 -- PE4 (OC3B/INT4)
PIN_DEF(E,5),    //   7 -- PE5 (OC3C/INT5)
PIN_DEF(E,6),    //   8 -- PE6 (T3/INT6)
PIN_DEF(E,7),    //   9 -- PE7 (CLKO/ICP3/INT7)
{0, 0, 0, 0},    //  10 -- VCC
{0, 0, 0, 0},    //  11 -- GND
PIN_DEF(H,0),    //  12 -- PH0 (RXD2)
PIN_DEF(H,1),    //  13 -- PH1 (TXD2)
PIN_DEF(H,2),    //  14 -- PH2 (XCK2)
PIN_DEF(H,3),    //  15 -- PH3 (OC4A)
PIN_DEF(H,4),    //  16 -- PH4 (OC4B)
PIN_DEF(H,5),    //  17 -- PH5 (OC4C)
PIN_DEF(H,6),    //  18 -- PH6 (OC2B)
PIN_DEF(B,0),    //  19 -- PB0 (SS/PCINT0)
PIN_DEF(B,1),    //  20 -- PB1 (SCK/PCINT1)
PIN_DEF(B,2),    //  21 -- PB2 (MOSI/PCINT2)
PIN_DEF(B,3),    //  22 -- PB3 (MISO/PCINT3)
PIN_DEF(B,4),    //  23 -- PB4 (OC2A/PCINT4)
PIN_DEF(B,5),    //  24 -- PB5 (OC1A/PCINT5)
PIN_DEF(B,6),    //  25 -- PB6 (OC1B/PCINT6)
PIN_DEF(B,7),    //  26 -- PB7 (OC0A/OC1C/PCINT7)
PIN_DEF(H,7),    //  27 -- PH7 (T4)
PIN_DEF(G,3),    //  28 -- PG3 (TOSC2)
PIN_DEF(G,4),    //  29 -- PG4 (TOSC1)
{0, 0, 0, 0},    //  30 -- RESET
{0, 0, 0, 0},    //  31 -- VCC
{0, 0, 0, 0},    //  32 -- GND
{0, 0, 0, 0},    //  33 -- XTAL2
{0, 0, 0, 0},    //  34 -- XTAL1
PIN_DEF(L,0),    //  35 -- PL0 (ICP4)
PIN_DEF(L,1),    //  36 -- PL1 (ICP5)
PIN_DEF(L,2),    //  37 -- PL2 (T5)
PIN_DEF(L,3),    //  38 -- PL3 (OC5A)
PIN_DEF(L,4),    //  39 -- PL4 (OC5B)
PIN_DEF(L,5),    //  40 -- PL5 (OC5C)
PIN_DEF(L,6),    //  41 -- PL6
PIN_DEF(L,7),    //  42 -- PL7
PIN_DEF(D,0),    //  43 -- PD0 (SCL/INT0)
PIN_DEF(D,1),    //  44 -- PD1 (SDA/INT1)
PIN_DEF(D,2),    //  45 -- PD2 (RXDI/INT2)
PIN_DEF(D,3),    //  46 -- PD3 (TXD1/INT3)
PIN_DEF(D,4),    //  47 -- PD4 (ICP1)
PIN_DEF(D,5),    //  48 -- PD5 (XCK1)
PIN_DEF(D,6),    //  49 -- PD6 (T1)
PIN_DEF(D,7),    //  50 -- PD7 (T0)
PIN_DEF(G,0),    //  51 -- PG0 (WR)
PIN_DEF(G,1),    //  52 -- PG1 (RD)
PIN_DEF(C,0),    //  53 -- PC0 (A8)
PIN_DEF(C,1),    //  54 -- PC1 (A9)
PIN_DEF(C,2),    //  55 -- PC2 (A10)
PIN_DEF(C,3),    //  56 -- PC3 (A11)
PIN_DEF(C,4),    //  57 -- PC4 (A12)
PIN_DEF(C,5),    //  58 -- PC5 (A13)
PIN_DEF(C,6),    //  59 -- PC6 (A14)
PIN_DEF(C,7),    //  60 -- PC7 (A15)
{0, 0, 0, 0},    //  61 -- VCC
{0, 0, 0, 0},    //  62 -- GND
PIN_DEF(J,0),    //  63 -- PJ0 (RXD3/PCINT9)
PIN_DEF(J,1),    //  64 -- PJ1 (TXD3/PCINT10)
PIN_DEF(J,2),    //  65 -- PJ2 (XCK3/PCINT11)
PIN_DEF(J,3),    //  66 -- PJ3 (PCINT12)
PIN_DEF(J,4),    //  67 -- PJ4 (PCINT13)
PIN_DEF(J,5),    //  68 -- PJ5 (PCINT14)
PIN_DEF(J,6),    //  69 -- PJ6 (PCINT 15)
PIN_DEF(G,2),    //  70 -- PG2 (ALE)
PIN_DEF(A,7),    //  71 -- PA7 (AD7)
PIN_DEF(A,6),    //  72 -- PA6 (AD6)
PIN_DEF(A,5),    //  73 -- PA5 (AD5)
PIN_DEF(A,4),    //  74 -- PA4 (AD4)
PIN_DEF(A,3),    //  75 -- PA3 (AD3)
PIN_DEF(A,2),    //  76 -- PA2 (AD2)
PIN_DEF(A,1),    //  77 -- PA1 (AD1)
PIN_DEF(A,0),    //  78 -- PA0 (AD0)
PIN_DEF(J,7),    //  79 -- PJ7
{0, 0, 0, 0},    //  80 -- VCC
{0, 0, 0, 0},    //  81 -- GND
PIN_DEF(K,7),    //  82 -- PK7 (ADC15/PCINT23)
PIN_DEF(K,6),    //  83 -- PK6 (ADC14/PCINT22)
PIN_DEF(K,5),    //  84 -- PK5 (ADC13/PCINT21)
PIN_DEF(K,4),    //  85 -- PK4 (ADC12/PCINT20)
PIN_DEF(K,3),    //  86 -- PK3 (ADC11/PCINT19)
PIN_DEF(K,2),    //  87 -- PK2 (ADC10/PCINT18)
PIN_DEF(K,1),    //  88 -- PK1 (ADC9/PCINT17)
PIN_DEF(K,0),    //  89 -- PK0 (ADC8/PCINT16)
PIN_DEF(F,7),    //  90 -- PF7 (ADC7)
PIN_DEF(F,6),    //  91 -- PF6 (ADC6)
PIN_DEF(F,5),    //  92 -- PF5 (ADC5/TMS)
PIN_DEF(F,4),    //  93 -- PF4 (ADC4/TMK)
PIN_DEF(F,3),    //  94 -- PF3 (ADC3)
PIN_DEF(F,2),    //  95 -- PF2 (ADC2)
PIN_DEF(F,1),    //  96 -- PF1 (ADC1)
PIN_DEF(F,0),    //  97 -- PF0 (ADC0)
{0, 0, 0, 0},    //  98 -- AREF
{0, 0, 0, 0},    //  99 -- GND
{0, 0, 0, 0},    // 100 -- AVCC
};

#undef PIN_DEF

}
}

#endif  // HAL_MCU_ATMEGA2560_TQFP100_MCU_DIGITALIO_H_
