#ifndef HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "hal/periph/GPIO/PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define PIN_DEF(port, pin) {reinterpret_cast<int>(&DDR ## port),      \
                            reinterpret_cast<int>(&PORT ## port),     \
                            reinterpret_cast<int>(&PIN ## port), pin}

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},     // 0 -- artificial pin
    {0, 0, 0, 0},     // 1 -- ~PEN
    PIN_DEF(E, 0),    // 2 -- RXD0/(PDI) PE0
    PIN_DEF(E, 1),    // 3 -- (TXD0/PDO) PE1
    PIN_DEF(E, 2),    // 4 -- (XCK0/AIN0) PE2
    PIN_DEF(E, 3),    // 5 -- (OC3A/AIN1) PE3
    PIN_DEF(E, 4),    // 6 -- (OC3B/INT4) PE4
    PIN_DEF(E, 5),    // 7 -- (OC3C/INT5) PE5
    PIN_DEF(E, 6),    // 8 -- (T3/INT6) PE6
    PIN_DEF(E, 7),    // 9 -- (ICP3/INT7) PE7
    PIN_DEF(B, 0),    // 10 -- (SS) PB0
    PIN_DEF(B, 1),    // 11 -- (SCK) PB1
    PIN_DEF(B, 2),    // 12 -- (MOSI) PB2
    PIN_DEF(B, 3),    // 13 -- (MISO) PB3
    PIN_DEF(B, 4),    // 14 -- (OC0) PB4
    PIN_DEF(B, 5),    // 15 -- (OC1A) PB5
    PIN_DEF(B, 6),    // 16 -- (OC1B) PB6
    PIN_DEF(B, 7),    // 17 -- (OC2/OC1C) PB7
    PIN_DEF(G, 3),    // 18 -- TOSC2/PG3
    PIN_DEF(G, 4),    // 19 -- TOSC1/PG4
    {0, 0, 0, 0},     // 20 -- ~RESET
    {0, 0, 0, 0},     // 21 -- VCC
    {0, 0, 0, 0},     // 22 -- GND
    {0, 0, 0, 0},     // 23 -- XTAL2
    {0, 0, 0, 0},     // 24 -- XTAL1
    PIN_DEF(D, 0),    // 25 -- (SCL/INT0) PD0
    PIN_DEF(D, 1),    // 26 -- (SDA/INT1) PD1
    PIN_DEF(D, 2),    // 27 -- (RXD1/INT2) PD2
    PIN_DEF(D, 3),    // 28 -- (TXD1/INT3) PD3
    PIN_DEF(D, 4),    // 29 -- (ICP1) PD4
    PIN_DEF(D, 5),    // 30 -- (XCK1) PD5
    PIN_DEF(D, 6),    // 31 -- (T1) PD6
    PIN_DEF(D, 7),    // 32 -- (T2) PD7
    PIN_DEF(G, 0),    // 33 -- PG0(WR)
    PIN_DEF(G, 1),    // 34 -- PG1(RD)
    PIN_DEF(C, 0),    // 35 -- PC0 (A8)
    PIN_DEF(C, 1),    // 36 -- PC1 (A9)
    PIN_DEF(C, 2),    // 37 -- PC2 (A10)
    PIN_DEF(C, 3),    // 38 -- PC3 (A11)
    PIN_DEF(C, 4),    // 39 -- PC4 (A12)
    PIN_DEF(C, 5),    // 40 -- PC5 (A13)
    PIN_DEF(C, 6),    // 41 -- PC6 (A14)
    PIN_DEF(C, 7),    // 42 -- PC7 (A15)
    PIN_DEF(G, 2),    // 43 -- PG2(ALE)
    PIN_DEF(A, 7),    // 44 -- PA7 (AD7)
    PIN_DEF(A, 6),    // 45 -- PA6 (AD6)
    PIN_DEF(A, 5),    // 46 -- PA5 (AD5)
    PIN_DEF(A, 4),    // 47 -- PA4 (AD4)
    PIN_DEF(A, 3),    // 48 -- PA3 (AD3)
    PIN_DEF(A, 2),    // 49 -- PA2 (AD2)
    PIN_DEF(A, 1),    // 50 -- PA1 (AD1)
    PIN_DEF(A, 0),    // 51 -- PA0 (AD0)
    {0, 0, 0, 0},     // 52 -- VCC
    {0, 0, 0, 0},     // 53 -- GND
    PIN_DEF(F, 7),    // 54 -- PF7 (ADC7/TDI)
    PIN_DEF(F, 6),    // 55 -- PF6 (ADC6/TDO)
    PIN_DEF(F, 5),    // 56 -- PF5 (ADC5/TMS)
    PIN_DEF(F, 4),    // 57 -- PF4 (ADC4/TCK)
    PIN_DEF(F, 3),    // 58 -- PF3 (ADC3)
    PIN_DEF(F, 2),    // 59 -- PF2 (ADC2)
    PIN_DEF(F, 1),    // 60 -- PF1 (ADC1)
    PIN_DEF(F, 0),    // 61 -- PF0 (ADC0)
    {0, 0, 0, 0},     // 62 -- AREF
    {0, 0, 0, 0},     // 63 -- GND
    {0, 0, 0, 0}      // 64 -- AVCC
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_DIGITALIO_H_
