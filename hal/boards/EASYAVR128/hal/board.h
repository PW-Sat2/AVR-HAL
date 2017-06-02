#ifndef HAL_BOARDS_EASYAVR128_HAL_BOARD_H_
#define HAL_BOARDS_EASYAVR128_HAL_BOARD_H_

#include "hal/periph.h"

namespace hal {
namespace bsp {
namespace pins {

#undef PE0
#undef PE1
#undef PE2
#undef PE3
#undef PE4
#undef PE5
#undef PE6
#undef PE7
#undef PB0
#undef PB1
#undef PB2
#undef PB3
#undef PB4
#undef PB5
#undef PB6
#undef PB7
#undef PG3
#undef PG4
#undef PD0
#undef PD1
#undef PD2
#undef PD3
#undef PD4
#undef PD5
#undef PD6
#undef PD7
#undef PG0
#undef PG1
#undef PC0
#undef PC1
#undef PC2
#undef PC3
#undef PC4
#undef PC5
#undef PC6
#undef PC7
#undef PG2
#undef PA7
#undef PA6
#undef PA5
#undef PA4
#undef PA3
#undef PA2
#undef PA1
#undef PA0
#undef PF7
#undef PF6
#undef PF5
#undef PF4
#undef PF3
#undef PF2
#undef PF1
#undef PF0

static constexpr DigitalIO::Interface::Pin PE0 = 2;
static constexpr DigitalIO::Interface::Pin PE1 = 3;
static constexpr DigitalIO::Interface::Pin PE2 = 4;
static constexpr DigitalIO::Interface::Pin PE3 = 5;
static constexpr DigitalIO::Interface::Pin PE4 = 6;
static constexpr DigitalIO::Interface::Pin PE5 = 7;
static constexpr DigitalIO::Interface::Pin PE6 = 8;
static constexpr DigitalIO::Interface::Pin PE7 = 9;
static constexpr DigitalIO::Interface::Pin PB0 = 10;
static constexpr DigitalIO::Interface::Pin PB1 = 11;
static constexpr DigitalIO::Interface::Pin PB2 = 12;
static constexpr DigitalIO::Interface::Pin PB3 = 13;
static constexpr DigitalIO::Interface::Pin PB4 = 14;
static constexpr DigitalIO::Interface::Pin PB5 = 15;
static constexpr DigitalIO::Interface::Pin PB6 = 16;
static constexpr DigitalIO::Interface::Pin PB7 = 17;
static constexpr DigitalIO::Interface::Pin PG3 = 18;
static constexpr DigitalIO::Interface::Pin PG4 = 19;
static constexpr DigitalIO::Interface::Pin PD0 = 25;
static constexpr DigitalIO::Interface::Pin PD1 = 26;
static constexpr DigitalIO::Interface::Pin PD2 = 27;
static constexpr DigitalIO::Interface::Pin PD3 = 28;
static constexpr DigitalIO::Interface::Pin PD4 = 29;
static constexpr DigitalIO::Interface::Pin PD5 = 30;
static constexpr DigitalIO::Interface::Pin PD6 = 31;
static constexpr DigitalIO::Interface::Pin PD7 = 32;
static constexpr DigitalIO::Interface::Pin PG0 = 33;
static constexpr DigitalIO::Interface::Pin PG1 = 34;
static constexpr DigitalIO::Interface::Pin PC0 = 35;
static constexpr DigitalIO::Interface::Pin PC1 = 36;
static constexpr DigitalIO::Interface::Pin PC2 = 37;
static constexpr DigitalIO::Interface::Pin PC3 = 38;
static constexpr DigitalIO::Interface::Pin PC4 = 39;
static constexpr DigitalIO::Interface::Pin PC5 = 40;
static constexpr DigitalIO::Interface::Pin PC6 = 41;
static constexpr DigitalIO::Interface::Pin PC7 = 42;
static constexpr DigitalIO::Interface::Pin PG2 = 43;
static constexpr DigitalIO::Interface::Pin PA7 = 44;
static constexpr DigitalIO::Interface::Pin PA6 = 45;
static constexpr DigitalIO::Interface::Pin PA5 = 46;
static constexpr DigitalIO::Interface::Pin PA4 = 47;
static constexpr DigitalIO::Interface::Pin PA3 = 48;
static constexpr DigitalIO::Interface::Pin PA2 = 49;
static constexpr DigitalIO::Interface::Pin PA1 = 50;
static constexpr DigitalIO::Interface::Pin PA0 = 51;
static constexpr DigitalIO::Interface::Pin PF7 = 54;
static constexpr DigitalIO::Interface::Pin PF6 = 55;
static constexpr DigitalIO::Interface::Pin PF5 = 56;
static constexpr DigitalIO::Interface::Pin PF4 = 57;
static constexpr DigitalIO::Interface::Pin PF3 = 58;
static constexpr DigitalIO::Interface::Pin PF2 = 59;
static constexpr DigitalIO::Interface::Pin PF1 = 60;
static constexpr DigitalIO::Interface::Pin PF0 = 61;

static constexpr DigitalIO::Interface::Pin LED = PA7;

}  // namespace pins
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EASYAVR128_HAL_BOARD_H_
