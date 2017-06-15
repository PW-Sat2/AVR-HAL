#ifndef HAL_BOARDS_EVB_MEGA644P_HAL_BOARD_H_
#define HAL_BOARDS_EVB_MEGA644P_HAL_BOARD_H_

#include "hal/periph.h"

namespace hal {
namespace bsp {
namespace pins {

using A0 = DigitalIO::GPIO<40>;
using A1 = DigitalIO::GPIO<39>;
using A2 = DigitalIO::GPIO<38>;
using A3 = DigitalIO::GPIO<37>;
using A4 = DigitalIO::GPIO<36>;
using A5 = DigitalIO::GPIO<35>;
using A6 = DigitalIO::GPIO<34>;
using A7 = DigitalIO::GPIO<33>;
using B0 = DigitalIO::GPIO<1>;
using B1 = DigitalIO::GPIO<2>;
using B2 = DigitalIO::GPIO<3>;
using B3 = DigitalIO::GPIO<4>;
using B4 = DigitalIO::GPIO<5>;
using B5 = DigitalIO::GPIO<6>;
using B6 = DigitalIO::GPIO<7>;
using B7 = DigitalIO::GPIO<8>;
using C0 = DigitalIO::GPIO<22>;
using C1 = DigitalIO::GPIO<23>;
using C2 = DigitalIO::GPIO<24>;
using C3 = DigitalIO::GPIO<25>;
using C4 = DigitalIO::GPIO<26>;
using C5 = DigitalIO::GPIO<27>;
using C6 = DigitalIO::GPIO<28>;
using C7 = DigitalIO::GPIO<29>;
using D0 = DigitalIO::GPIO<14>;
using D1 = DigitalIO::GPIO<15>;
using D2 = DigitalIO::GPIO<16>;
using D3 = DigitalIO::GPIO<17>;
using D4 = DigitalIO::GPIO<18>;
using D5 = DigitalIO::GPIO<19>;
using D6 = DigitalIO::GPIO<20>;
using D7 = DigitalIO::GPIO<21>;

}  // namespace pins
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EVB_MEGA644P_HAL_BOARD_H_
