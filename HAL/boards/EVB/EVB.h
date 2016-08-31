#ifndef HAL_BOARDS_EVB_EVB_H_
#define HAL_BOARDS_EVB_EVB_H_

#include "periph/DigitalIO.h"
#include "devices/LED.h"

namespace hal {
namespace bsp {
namespace pins {

static constexpr DigitalIO::Pin A0 = 40;
static constexpr DigitalIO::Pin A1 = 39;
static constexpr DigitalIO::Pin A2 = 38;
static constexpr DigitalIO::Pin A3 = 37;
static constexpr DigitalIO::Pin A4 = 36;
static constexpr DigitalIO::Pin A5 = 35;
static constexpr DigitalIO::Pin A6 = 34;
static constexpr DigitalIO::Pin A7 = 33;
static constexpr DigitalIO::Pin B0 =  1;
static constexpr DigitalIO::Pin B1 =  2;
static constexpr DigitalIO::Pin B2 =  3;
static constexpr DigitalIO::Pin B3 =  4;
static constexpr DigitalIO::Pin B4 =  5;
static constexpr DigitalIO::Pin B5 =  6;
static constexpr DigitalIO::Pin B6 =  7;
static constexpr DigitalIO::Pin B7 =  8;
static constexpr DigitalIO::Pin C0 = 22;
static constexpr DigitalIO::Pin C1 = 23;
static constexpr DigitalIO::Pin C2 = 24;
static constexpr DigitalIO::Pin C3 = 25;
static constexpr DigitalIO::Pin C4 = 26;
static constexpr DigitalIO::Pin C5 = 27;
static constexpr DigitalIO::Pin C6 = 28;
static constexpr DigitalIO::Pin C7 = 29;
static constexpr DigitalIO::Pin D0 = 14;
static constexpr DigitalIO::Pin D1 = 15;
static constexpr DigitalIO::Pin D2 = 16;
static constexpr DigitalIO::Pin D3 = 17;
static constexpr DigitalIO::Pin D4 = 18;
static constexpr DigitalIO::Pin D5 = 19;
static constexpr DigitalIO::Pin D6 = 20;
static constexpr DigitalIO::Pin D7 = 21;

}  // namespace pins

}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EVB_EVB_H_
