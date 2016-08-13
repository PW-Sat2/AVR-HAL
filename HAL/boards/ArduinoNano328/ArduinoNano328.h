#ifndef HAL_BOARDS_ARDUINONANO328_ARDUINONANO328_H_
#define HAL_BOARDS_ARDUINONANO328_ARDUINONANO328_H_

#include "periph/DigitalIO.h"
#include "devices/LED.h"

namespace hal {

namespace bsp {

namespace pins {
static constexpr DigitalIO::Pin D0 = 30;
static constexpr DigitalIO::Pin D1 = 31;
static constexpr DigitalIO::Pin D2 = 32;
static constexpr DigitalIO::Pin D3 = 1;
static constexpr DigitalIO::Pin D4 = 2;
static constexpr DigitalIO::Pin D5 = 9;
static constexpr DigitalIO::Pin D6 = 10;
static constexpr DigitalIO::Pin D7 = 11;
static constexpr DigitalIO::Pin D8 = 12;
static constexpr DigitalIO::Pin D9 = 13;
static constexpr DigitalIO::Pin D10 = 14;
static constexpr DigitalIO::Pin D11 = 15;
static constexpr DigitalIO::Pin D12 = 16;
static constexpr DigitalIO::Pin D13 = 17;

static constexpr DigitalIO::Pin A0 = 23;
static constexpr DigitalIO::Pin A1 = 24;
static constexpr DigitalIO::Pin A2 = 25;
static constexpr DigitalIO::Pin A3 = 26;
static constexpr DigitalIO::Pin A4 = 27;
static constexpr DigitalIO::Pin A5 = 28;
static constexpr DigitalIO::Pin A6 = 19;
static constexpr DigitalIO::Pin A7 = 22;

static constexpr DigitalIO::Pin LED = D13;
}  // namespace pins

constexpr static hal::LED led(pins::LED);

}  // namespace bsp
}  // namespace hal
#endif  // HAL_BOARDS_ARDUINONANO328_ARDUINONANO328_H_
