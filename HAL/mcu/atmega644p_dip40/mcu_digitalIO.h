#ifndef HAL_MCU_ATMEGA328P_TQFP32_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA328P_TQFP32_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define PIN_DEF(port, pin) {reinterpret_cast<int>(&DDR ## port),      \
                            reinterpret_cast<int>(&PORT ## port),     \
                            reinterpret_cast<int>(&PIN ## port), pin}

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},     //  0 -- artificial pin
    PIN_DEF(B, 0),    //  1 -- (PCINT8/XCK0/T0) PB0
    PIN_DEF(B, 1),    //  2 -- (PCINT9/CLKO/T1) PB1
    PIN_DEF(B, 2),    //  3 -- (PCINT10/INT2/AIN0) PB2
    PIN_DEF(B, 3),    //  4 -- (PCINT11/OC0A/AIN1) PB3
    PIN_DEF(B, 4),    //  5 -- (PCINT12/OC0B/SS) PB4
    PIN_DEF(B, 5),    //  6 -- (PCINT13/MOSI) PB5
    PIN_DEF(B, 6),    //  7 -- (PCINT14/MISO) PB6
    PIN_DEF(B, 7),    //  8 -- (PCINT15/SCK) PB7
    {0, 0, 0, 0},     //  9 -- RESET
    {0, 0, 0, 0},     // 10 -- VCC
    {0, 0, 0, 0},     // 11 -- GND
    {0, 0, 0, 0},     // 12 -- XTAL2
    {0, 0, 0, 0},     // 13 -- XTAL1
    PIN_DEF(D, 0),    // 14 -- (PCINT24/RXD0) PD0
    PIN_DEF(D, 1),    // 15 -- (PCINT25/TXD0) PD1
    PIN_DEF(D, 2),    // 16 -- (PCINT26/INT0) PD2
    PIN_DEF(D, 3),    // 17 -- (PCINT27/INT1) PD3
    PIN_DEF(D, 4),    // 18 -- (PCINT28/OC1B) PD4
    PIN_DEF(D, 5),    // 19 -- (PCINT29/OC1A) PD5
    PIN_DEF(D, 6),    // 20 -- (PCINT30/OC2B/ICP) PD6
    PIN_DEF(D, 7),    // 21 -- PD7 (OC2A/PCINT31)
    PIN_DEF(C, 0),    // 22 -- PC0 (SCL/PCINT16)
    PIN_DEF(C, 1),    // 23 -- PC1 (SDA/PCINT17)
    PIN_DEF(C, 2),    // 24 -- PC2 (TCK/PCINT18)
    PIN_DEF(C, 3),    // 25 -- PC3 (TMS/PCINT19)
    PIN_DEF(C, 4),    // 26 -- PC4 (TDO/PCINT20)
    PIN_DEF(C, 5),    // 27 -- PC5 (TDI/PCINT21)
    PIN_DEF(C, 6),    // 28 -- PC6 (TOSC1/PCINT22)
    PIN_DEF(C, 7),    // 29 -- PC7 (TOSC2/PCINT23)
    {0, 0, 0, 0},     // 30 -- AVCC
    {0, 0, 0, 0},     // 31 -- GND
    {0, 0, 0, 0},     // 32 -- AREF
    PIN_DEF(A, 7),    // 33 -- PA7 (ADC7/PCINT7)
    PIN_DEF(A, 6),    // 34 -- PA6 (ADC6/PCINT6)
    PIN_DEF(A, 5),    // 35 -- PA5 (ADC5/PCINT5)
    PIN_DEF(A, 4),    // 36 -- PA4 (ADC4/PCINT4)
    PIN_DEF(A, 3),    // 37 -- PA3 (ADC3/PCINT3)
    PIN_DEF(A, 2),    // 38 -- PA2 (ADC2/PCINT2)
    PIN_DEF(A, 1),    // 39 -- PA1 (ADC1/PCINT1)
    PIN_DEF(A, 0),    // 40 -- PA0 (ADC0/PCINT0)
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA328P_TQFP32_MCU_DIGITALIO_H_
