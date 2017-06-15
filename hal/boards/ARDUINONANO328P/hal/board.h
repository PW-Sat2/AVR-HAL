#ifndef HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_
#define HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_

#include "hal/periph.h"

namespace hal {
namespace bsp {
namespace pins {

using D0  = DigitalIO::GPIO<30>;
using D1  = DigitalIO::GPIO<31>;
using D2  = DigitalIO::GPIO<32>;
using D3  = DigitalIO::GPIO<1>;
using D4  = DigitalIO::GPIO<2>;
using D5  = DigitalIO::GPIO<9>;
using D6  = DigitalIO::GPIO<10>;
using D7  = DigitalIO::GPIO<11>;
using D8  = DigitalIO::GPIO<12>;
using D9  = DigitalIO::GPIO<13>;
using D10 = DigitalIO::GPIO<14>;
using D11 = DigitalIO::GPIO<15>;
using D12 = DigitalIO::GPIO<16>;
using D13 = DigitalIO::GPIO<17>;

using A0 = DigitalIO::GPIO<23>;
using A1 = DigitalIO::GPIO<24>;
using A2 = DigitalIO::GPIO<25>;
using A3 = DigitalIO::GPIO<26>;
using A4 = DigitalIO::GPIO<27>;
using A5 = DigitalIO::GPIO<28>;
using A6 = DigitalIO::GPIO<19>;
using A7 = DigitalIO::GPIO<22>;


}  // namespace pins
using LED = devices::LED<pins::D13>;
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_ARDUINONANO328P_HAL_BOARD_H_
