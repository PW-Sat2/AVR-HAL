#ifndef HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_
#define HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_

#include "hal/devices.h"
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

using PA0 = DigitalIO::GPIO<37>;
using PA1 = DigitalIO::GPIO<36>;
using PA2 = DigitalIO::GPIO<35>;
using PA3 = DigitalIO::GPIO<34>;
using PA4 = DigitalIO::GPIO<33>;
using PA5 = DigitalIO::GPIO<32>;
using PA6 = DigitalIO::GPIO<31>;
using PA7 = DigitalIO::GPIO<30>;
using PB0 = DigitalIO::GPIO<40>;
using PB1 = DigitalIO::GPIO<41>;
using PB2 = DigitalIO::GPIO<42>;
using PB3 = DigitalIO::GPIO<43>;
using PB4 = DigitalIO::GPIO<44>;
using PB5 = DigitalIO::GPIO<1>;
using PB6 = DigitalIO::GPIO<2>;
using PB7 = DigitalIO::GPIO<3>;
using PD0 = DigitalIO::GPIO<19>;
using PD1 = DigitalIO::GPIO<20>;
using PD2 = DigitalIO::GPIO<21>;
using PD3 = DigitalIO::GPIO<22>;
using PD4 = DigitalIO::GPIO<23>;
using PD5 = DigitalIO::GPIO<34>;
using PD6 = DigitalIO::GPIO<35>;
using PD7 = DigitalIO::GPIO<36>;
using PC0 = DigitalIO::GPIO<9>;
using PC1 = DigitalIO::GPIO<10>;
using PC2 = DigitalIO::GPIO<11>;
using PC3 = DigitalIO::GPIO<12>;
using PC4 = DigitalIO::GPIO<13>;
using PC5 = DigitalIO::GPIO<14>;
using PC6 = DigitalIO::GPIO<15>;
using PC7 = DigitalIO::GPIO<16>;


}  // namespace pins
using LED = devices::LED<pins::PB7>;
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EVB_ATMEGA324P_HAL_BOARD_H_
