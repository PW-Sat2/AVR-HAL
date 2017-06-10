#ifndef HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "hal/periph/DigitalIO/PeriphDescriptors.h"

namespace hal {
namespace mcu {

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},   //  0 -- artificial pin
    PIN_DEF(D, 3),  //  1 -- (PCINT19/OC2B/INT1) PD3
    PIN_DEF(D, 4),  //  2 -- (PCINT20/XCK/T0) PD4
    {0, 0, 0, 0},   //  3 -- GND
    {0, 0, 0, 0},   //  4 -- VCC
    {0, 0, 0, 0},   //  5 -- GND
    {0, 0, 0, 0},   //  6 -- VCC
    PIN_DEF(B, 6),  //  7 -- (PCINT6/XTAL1/TOSC1) PB6
    PIN_DEF(B, 7),  //  8 -- (PCINT7/XTAL2/TOSC2) PB7
    PIN_DEF(D, 5),  //  9 -- (PCINT21/OC0B/T1) PD5
    PIN_DEF(D, 6),  // 10 -- (PCINT22/OC0A/AIN0) PD6
    PIN_DEF(D, 7),  // 11 -- (PCINT23/AIN1) PD7
    PIN_DEF(B, 0),  // 12 -- (PCINT0/CLKO/ICP1) PB0
    PIN_DEF(B, 1),  // 13 -- (PCINT1/OC1A) PB1
    PIN_DEF(B, 2),  // 14 -- (PCINT2/SS/OC1B) PB2
    PIN_DEF(B, 3),  // 15 -- (PCINT3/OC2A/MOSI) PB3
    PIN_DEF(B, 4),  // 16 -- (PCINT4/MISO) PB4
    PIN_DEF(B, 5),  // 17 -- (SCK/PCINT5) PB5
    {0, 0, 0, 0},   // 18 -- AVCC
    {0, 0, 0, 0},   // 19 -- ADC6
    {0, 0, 0, 0},   // 20 -- AREF
    {0, 0, 0, 0},   // 21 -- GND
    {0, 0, 0, 0},   // 22 -- ADC7
    PIN_DEF(C, 0),  // 23 -- (ADC0/PCINT8) PC0
    PIN_DEF(C, 1),  // 24 -- (ADC1/PCINT9) PC1
    PIN_DEF(C, 2),  // 25 -- PC2 (ADC2/PCINT10)
    PIN_DEF(C, 3),  // 26 -- PC3 (ADC3/PCINT11)
    PIN_DEF(C, 4),  // 27 -- PC4 (ADC4/SDA/PCINT12)
    PIN_DEF(C, 5),  // 28 -- PC5 (ADC5/SCL/PCINT13)
    PIN_DEF(C, 6),  // 29 -- PC6 (RESET/PCINT14)
    PIN_DEF(D, 0),  // 30 -- PD0 (RXD/PCINT16)
    PIN_DEF(D, 1),  // 31 -- PD1 (TXD/PCINT17)
    PIN_DEF(D, 2)   // 32 -- PD2 (INT0/PCINT18)
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_DIGITALIO_H_
