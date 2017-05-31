#ifndef HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_DIGITALIO_H_
#define HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "hal/periph/DigitalIO/PeriphDescriptors.h"

namespace hal {
namespace mcu {

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},   //  0 -- artificial pin
    {0, 0, 0, 0},   //  1 -- NC
    PIN_DEF(E, 0),  //  2 -- PE0 (RXD0 / PDI)
    PIN_DEF(E, 1),  //  3 -- PE1 (TXD0 / PDO)
    PIN_DEF(E, 2),  //  4 -- PE2 (XCK0 / AIN0)
    PIN_DEF(E, 3),  //  5 -- PE3 (OC3A / AIN1)
    PIN_DEF(E, 4),  //  6 -- PE4 (OC3B / INT4)
    PIN_DEF(E, 5),  //  7 -- PE5 (OC3C / INT5)
    PIN_DEF(E, 6),  //  8 -- PE6 (T3 / INT6)
    PIN_DEF(E, 7),  //  9 -- PE7 (ICP3 / INT7)
    PIN_DEF(B, 0),  // 10 -- PB0 (SS)
    PIN_DEF(B, 1),  // 11 -- PB1 (SCK)
    PIN_DEF(B, 2),  // 12 -- PB2 (MOSI)
    PIN_DEF(B, 3),  // 13 -- PB3 (MISO)
    PIN_DEF(B, 4),  // 14 -- PB4 (OC2A)
    PIN_DEF(B, 5),  // 15 -- PB5 (OC1A)
    PIN_DEF(B, 6),  // 16 -- PB6 (OC1B)
    PIN_DEF(B, 7),  // 17 -- PB7 (OC0A / OC1C)
    PIN_DEF(G, 3),  // 18 -- PG3 (TOSC2)
    PIN_DEF(G, 4),  // 19 -- PG4 (TOSC1)
    {0, 0, 0, 0},   // 20 -- RESET
    {0, 0, 0, 0},   // 21 -- VCC
    {0, 0, 0, 0},   // 22 -- GND
    {0, 0, 0, 0},   // 23 -- XTAL2
    {0, 0, 0, 0},   // 24 -- XTAL1
    PIN_DEF(D, 0),  // 25 -- PD0 (SCL / INT0)
    PIN_DEF(D, 1),  // 26 -- PD1 (SDA / INT1)
    PIN_DEF(D, 2),  // 27 -- PD2 (RXD1 / INT2)
    PIN_DEF(D, 3),  // 28 -- PD3 (TXD1 / INT3)
    PIN_DEF(D, 4),  // 29 -- PD4 (ICP1)
    PIN_DEF(D, 5),  // 30 -- PD5 (TXCAN / XCK1)
    PIN_DEF(D, 6),  // 31 -- PD6 (RXCAN / T1)
    PIN_DEF(D, 7),  // 32 -- PD7 (T0)
    PIN_DEF(G, 0),  // 33 -- PG0 (WR)
    PIN_DEF(G, 1),  // 34 -- PG1 (RD)
    PIN_DEF(C, 0),  // 35 -- PC0 (A8)
    PIN_DEF(C, 1),  // 36 -- PC1 (A9)
    PIN_DEF(C, 2),  // 37 -- PC2 (A10)
    PIN_DEF(C, 3),  // 38 -- PC3 (A11)
    PIN_DEF(C, 4),  // 39 -- PC4 (A12)
    PIN_DEF(C, 5),  // 40 -- PC5 (A13)
    PIN_DEF(C, 6),  // 41 -- PC6 (A14)
    PIN_DEF(C, 7),  // 42 -- PC7 (A15 / CLKO)
    PIN_DEF(G, 2),  // 43 -- PG2 (ALE)
    PIN_DEF(A, 7),  // 44 -- PA7 (AD7)
    PIN_DEF(A, 6),  // 45 -- PA6 (AD6)
    PIN_DEF(A, 5),  // 46 -- PA5 (AD5)
    PIN_DEF(A, 4),  // 47 -- PA4 (AD4)
    PIN_DEF(A, 3),  // 48 -- PA3 (AD3)
    PIN_DEF(A, 2),  // 49 -- PA2 (AD2)
    PIN_DEF(A, 1),  // 50 -- PA1 (AD1)
    PIN_DEF(A, 0),  // 51 -- PA0 (AD0)
    {0, 0, 0, 0},   // 52 -- VCC
    {0, 0, 0, 0},   // 53 -- GND
    PIN_DEF(F, 7),  // 54 -- PF7 (ADC7 / TDI)
    PIN_DEF(F, 6),  // 55 -- PF6 (ADC6 / TDO)
    PIN_DEF(F, 5),  // 56 -- PF5 (ADC5 / TMS)
    PIN_DEF(F, 4),  // 57 -- PF4 (ADC4 / TCK)
    PIN_DEF(F, 3),  // 58 -- PF3 (ADC3)
    PIN_DEF(F, 2),  // 59 -- PF2 (ADC2)
    PIN_DEF(F, 1),  // 60 -- PF1 (ADC1)
    PIN_DEF(F, 0),  // 61 -- PF0 (ADC0)
    {0, 0, 0, 0},   // 62 -- AREF
    {0, 0, 0, 0},   // 63 -- GND
    {0, 0, 0, 0}    // 64 -- AVCC
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_DIGITALIO_H_
