#ifndef HAL_BOARDS_EASYAVR128_EASYAVR128_H_
#define HAL_BOARDS_EASYAVR128_EASYAVR128_H_

#include "periph/DigitalIO.h"
#include "devices/LED.h"

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

static constexpr DigitalIO::Pin PE0 = 2;
static constexpr DigitalIO::Pin PE1 = 3;
static constexpr DigitalIO::Pin PE2 = 4;
static constexpr DigitalIO::Pin PE3 = 5;
static constexpr DigitalIO::Pin PE4 = 6;
static constexpr DigitalIO::Pin PE5 = 7;
static constexpr DigitalIO::Pin PE6 = 8;
static constexpr DigitalIO::Pin PE7 = 9;
static constexpr DigitalIO::Pin PB0 = 10;
static constexpr DigitalIO::Pin PB1 = 11;
static constexpr DigitalIO::Pin PB2 = 12;
static constexpr DigitalIO::Pin PB3 = 13;
static constexpr DigitalIO::Pin PB4 = 14;
static constexpr DigitalIO::Pin PB5 = 15;
static constexpr DigitalIO::Pin PB6 = 16;
static constexpr DigitalIO::Pin PB7 = 17;
static constexpr DigitalIO::Pin PG3 = 18;
static constexpr DigitalIO::Pin PG4 = 19;
static constexpr DigitalIO::Pin PD0 = 25;
static constexpr DigitalIO::Pin PD1 = 26;
static constexpr DigitalIO::Pin PD2 = 27;
static constexpr DigitalIO::Pin PD3 = 28;
static constexpr DigitalIO::Pin PD4 = 29;
static constexpr DigitalIO::Pin PD5 = 30;
static constexpr DigitalIO::Pin PD6 = 31;
static constexpr DigitalIO::Pin PD7 = 32;
static constexpr DigitalIO::Pin PG0 = 33;
static constexpr DigitalIO::Pin PG1 = 34;
static constexpr DigitalIO::Pin PC0 = 35;
static constexpr DigitalIO::Pin PC1 = 36;
static constexpr DigitalIO::Pin PC2 = 37;
static constexpr DigitalIO::Pin PC3 = 38;
static constexpr DigitalIO::Pin PC4 = 39;
static constexpr DigitalIO::Pin PC5 = 40;
static constexpr DigitalIO::Pin PC6 = 41;
static constexpr DigitalIO::Pin PC7 = 42;
static constexpr DigitalIO::Pin PG2 = 43;
static constexpr DigitalIO::Pin PA7 = 44;
static constexpr DigitalIO::Pin PA6 = 45;
static constexpr DigitalIO::Pin PA5 = 46;
static constexpr DigitalIO::Pin PA4 = 47;
static constexpr DigitalIO::Pin PA3 = 48;
static constexpr DigitalIO::Pin PA2 = 49;
static constexpr DigitalIO::Pin PA1 = 50;
static constexpr DigitalIO::Pin PA0 = 51;
static constexpr DigitalIO::Pin PF7 = 54;
static constexpr DigitalIO::Pin PF6 = 55;
static constexpr DigitalIO::Pin PF5 = 56;
static constexpr DigitalIO::Pin PF4 = 57;
static constexpr DigitalIO::Pin PF3 = 58;
static constexpr DigitalIO::Pin PF2 = 59;
static constexpr DigitalIO::Pin PF1 = 60;
static constexpr DigitalIO::Pin PF0 = 61;


static constexpr DigitalIO::Pin LED0 = PE4;
static constexpr DigitalIO::Pin LED1 = PE5;
static constexpr DigitalIO::Pin LED2 = PE6;
static constexpr DigitalIO::Pin LED3 = PE7;
}  // namespace pins

constexpr static hal::LED led0(pins::LED0);
constexpr static hal::LED led1(pins::LED1);
constexpr static hal::LED led2(pins::LED2);
constexpr static hal::LED led3(pins::LED3);


}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EASYAVR128_EASYAVR128_H_
