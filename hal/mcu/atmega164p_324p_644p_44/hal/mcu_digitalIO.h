#ifndef HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "hal/periph/GPIO/PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define PIN_DEF(port, pin) {reinterpret_cast<int>(&DDR ## port),      \
                            reinterpret_cast<int>(&PORT ## port),     \
                            reinterpret_cast<int>(&PIN ## port), pin}

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},   //  0 -- padding
    PIN_DEF(B, 5),  //  1 -- PB5 (PCINT13/MOSI)
    PIN_DEF(B, 6),  //  2 -- PB6 (PCINT14/MISO)
    PIN_DEF(B, 7),  //  3 -- PB7 (PCINT15/SCK)
    {0, 0, 0, 0},   //  4 -- RESET
    {0, 0, 0, 0},   //  5 -- VCC
    {0, 0, 0, 0},   //  6 -- GND
    {0, 0, 0, 0},   //  7 -- XTAL2
    {0, 0, 0, 0},   //  8 -- XTAL1
    PIN_DEF(D, 0),  //  9 -- PD0 (PCINT24/RXD0)
    PIN_DEF(D, 1),  // 10 -- PD1 (PCINT25/TXD0)
    PIN_DEF(D, 2),  // 11 -- PD2 (PCINT26/RXD1/INT0)
    PIN_DEF(D, 3),  // 12 -- PD3 (PCINT27/TXD1/INT1)
    PIN_DEF(D, 4),  // 13 -- PD4 (PCINT28/XCK1/OC1B)
    PIN_DEF(D, 5),  // 14 -- PD5 (PCINT29/OC1A)
    PIN_DEF(D, 6),  // 15 -- PD6 (PCINT30/OC2B/ICP1)
    PIN_DEF(D, 7),  // 16 -- PD7 (PCINT31/OC2A)
    {0, 0, 0, 0},   // 17 -- VCC
    {0, 0, 0, 0},   // 18 -- GND
    PIN_DEF(C, 0),  // 19 -- PC0 (PCINT16/SCL)
    PIN_DEF(C, 1),  // 20 -- PC1 (PCINT17/SDA)
    PIN_DEF(C, 2),  // 21 -- PC2 (PCINT18/TCK)
    PIN_DEF(C, 3),  // 22 -- PC3 (PCINT19/TMS)
    PIN_DEF(C, 4),  // 23 -- PC4 (TDO/PCINT20)
    PIN_DEF(C, 5),  // 24 -- PC5 (TDI/PCINT21)
    PIN_DEF(C, 6),  // 25 -- PC6 (TOSC1/PCINT22)
    PIN_DEF(C, 7),  // 26 -- PC7 (TOSC2/PCINT23)
    {0, 0, 0, 0},   // 27 -- AVCC
    {0, 0, 0, 0},   // 28 -- GND
    {0, 0, 0, 0},   // 29 -- AREF
    PIN_DEF(A, 7),  // 30 -- PA7 (ADC7/PCINT7)
    PIN_DEF(A, 6),  // 31 -- PA6 (ADC6/PCINT6)
    PIN_DEF(A, 5),  // 32 -- PA5 (ADC5/PCINT5)
    PIN_DEF(A, 4),  // 33 -- PA4 (ADC4/PCINT4)
    PIN_DEF(A, 3),  // 34 -- PA3 (ADC3/PCINT3)
    PIN_DEF(A, 2),  // 35 -- PA2 (ADC2/PCINT2)
    PIN_DEF(A, 1),  // 36 -- PA1 (ADC1/PCINT1)
    PIN_DEF(A, 0),  // 37 -- PA0 (ADC0/PCINT0)
    {0, 0, 0, 0},   // 38 -- VCC
    {0, 0, 0, 0},   // 39 -- GND
    PIN_DEF(B, 0),  // 40 -- PB0 (XCK0/T0/PCINT8)
    PIN_DEF(B, 1),  // 41 -- PB1 (T1/CLKO/PCINT9)
    PIN_DEF(B, 2),  // 42 -- PB2 (AIN0/INT2/PCINT10)
    PIN_DEF(B, 3),  // 43 -- PB3 (AIN1/OC0A/PCINT11)
    PIN_DEF(B, 4)   // 44 -- PB4 (SS/OC0B/PCINT12)
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_DIGITALIO_H_
