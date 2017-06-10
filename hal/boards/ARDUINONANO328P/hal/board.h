#ifndef HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_
#define HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_

#include "hal/periph.h"

namespace hal {
namespace bsp {
namespace pins {

static constexpr DigitalIO::Interface::Pin D0  = 30;
static constexpr DigitalIO::Interface::Pin D1  = 31;
static constexpr DigitalIO::Interface::Pin D2  = 32;
static constexpr DigitalIO::Interface::Pin D3  = 1;
static constexpr DigitalIO::Interface::Pin D4  = 2;
static constexpr DigitalIO::Interface::Pin D5  = 9;
static constexpr DigitalIO::Interface::Pin D6  = 10;
static constexpr DigitalIO::Interface::Pin D7  = 11;
static constexpr DigitalIO::Interface::Pin D8  = 12;
static constexpr DigitalIO::Interface::Pin D9  = 13;
static constexpr DigitalIO::Interface::Pin D10 = 14;
static constexpr DigitalIO::Interface::Pin D11 = 15;
static constexpr DigitalIO::Interface::Pin D12 = 16;
static constexpr DigitalIO::Interface::Pin D13 = 17;

static constexpr DigitalIO::Interface::Pin A0 = 23;
static constexpr DigitalIO::Interface::Pin A1 = 24;
static constexpr DigitalIO::Interface::Pin A2 = 25;
static constexpr DigitalIO::Interface::Pin A3 = 26;
static constexpr DigitalIO::Interface::Pin A4 = 27;
static constexpr DigitalIO::Interface::Pin A5 = 28;
static constexpr DigitalIO::Interface::Pin A6 = 19;
static constexpr DigitalIO::Interface::Pin A7 = 22;

static constexpr DigitalIO::Interface::Pin LED = D13;

}  // namespace pins
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_
