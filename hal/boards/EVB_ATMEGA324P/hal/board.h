#ifndef HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_
#define HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_

#include "hal/periph.h"

namespace hal {
namespace bsp {
namespace pins {

#undef PA0
#undef PA1
#undef PA2
#undef PA3
#undef PA4
#undef PA5
#undef PA6
#undef PA7
#undef PB0
#undef PB1
#undef PB2
#undef PB3
#undef PB4
#undef PB5
#undef PB6
#undef PB7
#undef PC0
#undef PC1
#undef PC2
#undef PC3
#undef PC4
#undef PC5
#undef PC6
#undef PC7
#undef PD0
#undef PD1
#undef PD2
#undef PD3
#undef PD4
#undef PD5
#undef PD6
#undef PD7


static constexpr DigitalIO::Pin PA0 = 37;
static constexpr DigitalIO::Pin PA1 = 36;
static constexpr DigitalIO::Pin PA2 = 35;
static constexpr DigitalIO::Pin PA3 = 34;
static constexpr DigitalIO::Pin PA4 = 33;
static constexpr DigitalIO::Pin PA5 = 32;
static constexpr DigitalIO::Pin PA6 = 31;
static constexpr DigitalIO::Pin PA7 = 30;
static constexpr DigitalIO::Pin PB0 = 40;
static constexpr DigitalIO::Pin PB1 = 41;
static constexpr DigitalIO::Pin PB2 = 42;
static constexpr DigitalIO::Pin PB3 = 43;
static constexpr DigitalIO::Pin PB4 = 44;
static constexpr DigitalIO::Pin PB5 = 1;
static constexpr DigitalIO::Pin PB6 = 2;
static constexpr DigitalIO::Pin PB7 = 3;
static constexpr DigitalIO::Pin PD0 = 19;
static constexpr DigitalIO::Pin PD1 = 20;
static constexpr DigitalIO::Pin PD2 = 21;
static constexpr DigitalIO::Pin PD3 = 22;
static constexpr DigitalIO::Pin PD4 = 23;
static constexpr DigitalIO::Pin PD5 = 34;
static constexpr DigitalIO::Pin PD6 = 35;
static constexpr DigitalIO::Pin PD7 = 36;
static constexpr DigitalIO::Pin PC0 = 9;
static constexpr DigitalIO::Pin PC1 = 10;
static constexpr DigitalIO::Pin PC2 = 11;
static constexpr DigitalIO::Pin PC3 = 12;
static constexpr DigitalIO::Pin PC4 = 13;
static constexpr DigitalIO::Pin PC5 = 14;
static constexpr DigitalIO::Pin PC6 = 15;
static constexpr DigitalIO::Pin PC7 = 16;


static constexpr DigitalIO::Pin LED = PB7;
}  // namespace pins

constexpr static hal::LED led(pins::LED);

}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_
