#ifndef HAL_MCU_ATMEGA324P_TQFP32_MCU_DIGITALIO_H_
#define HAL_MCU_ATMEGA324P_TQFP32_MCU_DIGITALIO_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define PIN_DEF(port, pin) {reinterpret_cast<int>(&DDR ## port),      \
                            reinterpret_cast<int>(&PORT ## port),     \
                            reinterpret_cast<int>(&PIN ## port), pin}

constexpr static DigitalIOPinDescriptor DigitalIOPinMap[] = {
    {0, 0, 0, 0},     //  0 -- artificial pin
    PIN_DEF(B, 5),    //  1 -- (PCINT13/MOSI) PB3
    PIN_DEF(B, 6),    //  2 -- (PCINT14/MISO) PB4
    PIN_DEF(B, 7),    //  3 -- (PCINT15/SCK)PB7
    { 0, 0, 0, 0},    //  4 -- RST
    { 0, 0, 0, 0},    //  5 -- VCC
    { 0, 0, 0, 0},    //  6 -- GND
    ???,    //  7 -- XTAL2
    ???,    //  8 -- XTAL2
    PIN_DEF(D, 0),    //  9 -- (PCINT24/RXD0) PD0
    PIN_DEF(D, 1),    // 10 -- (PCINT25/TXD0) PD1
    PIN_DEF(D, 2),    // 11 -- (PCINT26/INT0) PD2
    PIN_DEF(D, 3),    // 12 -- (PCINT27/INT1/) PD3
    PIN_DEF(D, 4),    // 13 -- (PCINT28/OC1B) PD4
    PIN_DEF(D, 5),    // 14 -- (PCINT29/OC1A) PD5
    PIN_DEF(D, 6),    // 15 -- (PCINT30/OC2B/ICP) PD6
    PIN_DEF(D, 7),    // 16 -- (PCINT31/OC2A) PD7
    {0, 0, 0, 0},     // 17 -- VCC
    {0, 0, 0, 0},     // 18 -- GND
    PIN_DEF(C, 0),    // 19 -- (PCINT16/SCL) PC0
    PIN_DEF(C, 1),    // 20 -- (PCINT17/SDA) PC1
    PIN_DEF(C, 2),    // 21 -- (PCINT18/TCK) PC2
    PIN_DEF(C, 3),    // 22 -- (PCINT19/TMS) PC3
    PIN_DEF(C, 4),    // 23 -- (PCINT20/TDO) PC4
    PIN_DEF(C, 5),    // 24 -- (PCINT21/TDI) PC5
    PIN_DEF(C, 6),    // 25 -- (PCINT22/TOSC1) PC6
    PIN_DEF(C, 7),    // 26 -- (PCINT23/TOSC2) PC7
    ???,    // 27 -- AVCC
    { 0, 0, 0, 0},    // 28 -- GND
    ???,    // 29 -- AREF
    PIN_DEF(A, 7),    // 30 -- (PCINT7/ADC7) PA7
    PIN_DEF(A, 6),    // 31 -- (PCINT6/ADC6) PA6
    PIN_DEF(A, 5)     // 32 -- (PCINT5/ADC5) PA5
    PIN_DEF(A, 4)     // 33 -- (PCINT4/ADC4) PA4
    PIN_DEF(A, 3)     // 34 -- (PCINT3/ADC3) PA3
    PIN_DEF(A, 2)     // 35 -- (PCINT2/ADC2) PA2
    PIN_DEF(A, 1)     // 36 -- (PCINT1/ADC1) PA1
    PIN_DEF(A, 0)     // 37 -- (PCINT0/ADC0) PA0
	{ 0, 0, 0, 0},    // 38 -- VCC
	{ 0, 0, 0, 0},    // 39 -- GND
	PIN_DEF(B, 0),    // 40 -- (PCINT8/XCK0/T0) PB0
	PIN_DEF(B, 1),    // 41 -- (PCINT9/CLK0/T1) PB1
	PIN_DEF(B, 2),    // 42 -- (PCINT10/INT2/AIN0) PB2
    PIN_DEF(B, 3),    // 43 -- (PCINT11/OC0A/AIN1) PB3
	PIN_DEF(B, 4),    // 44 -- (PCINT12/OC0B/SS) PB4        
};

#undef PIN_DEF

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA324P_TQFP32_MCU_DIGITALIO_H_
