#ifndef HAL_BOARDS_EASYAVR128_HAL_BOARD_H_
#define HAL_BOARDS_EASYAVR128_HAL_BOARD_H_

#include "hal/devices.h"
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

using PE0 = DigitalIO::GPIO<2>;
using PE1 = DigitalIO::GPIO<3>;
using PE2 = DigitalIO::GPIO<4>;
using PE3 = DigitalIO::GPIO<5>;
using PE4 = DigitalIO::GPIO<6>;
using PE5 = DigitalIO::GPIO<7>;
using PE6 = DigitalIO::GPIO<8>;
using PE7 = DigitalIO::GPIO<9>;
using PB0 = DigitalIO::GPIO<10>;
using PB1 = DigitalIO::GPIO<11>;
using PB2 = DigitalIO::GPIO<12>;
using PB3 = DigitalIO::GPIO<13>;
using PB4 = DigitalIO::GPIO<14>;
using PB5 = DigitalIO::GPIO<15>;
using PB6 = DigitalIO::GPIO<16>;
using PB7 = DigitalIO::GPIO<17>;
using PG3 = DigitalIO::GPIO<18>;
using PG4 = DigitalIO::GPIO<19>;
using PD0 = DigitalIO::GPIO<25>;
using PD1 = DigitalIO::GPIO<26>;
using PD2 = DigitalIO::GPIO<27>;
using PD3 = DigitalIO::GPIO<28>;
using PD4 = DigitalIO::GPIO<29>;
using PD5 = DigitalIO::GPIO<30>;
using PD6 = DigitalIO::GPIO<31>;
using PD7 = DigitalIO::GPIO<32>;
using PG0 = DigitalIO::GPIO<33>;
using PG1 = DigitalIO::GPIO<34>;
using PC0 = DigitalIO::GPIO<35>;
using PC1 = DigitalIO::GPIO<36>;
using PC2 = DigitalIO::GPIO<37>;
using PC3 = DigitalIO::GPIO<38>;
using PC4 = DigitalIO::GPIO<39>;
using PC5 = DigitalIO::GPIO<40>;
using PC6 = DigitalIO::GPIO<41>;
using PC7 = DigitalIO::GPIO<42>;
using PG2 = DigitalIO::GPIO<43>;
using PA7 = DigitalIO::GPIO<44>;
using PA6 = DigitalIO::GPIO<45>;
using PA5 = DigitalIO::GPIO<46>;
using PA4 = DigitalIO::GPIO<47>;
using PA3 = DigitalIO::GPIO<48>;
using PA2 = DigitalIO::GPIO<49>;
using PA1 = DigitalIO::GPIO<50>;
using PA0 = DigitalIO::GPIO<51>;
using PF7 = DigitalIO::GPIO<54>;
using PF6 = DigitalIO::GPIO<55>;
using PF5 = DigitalIO::GPIO<56>;
using PF4 = DigitalIO::GPIO<57>;
using PF3 = DigitalIO::GPIO<58>;
using PF2 = DigitalIO::GPIO<59>;
using PF1 = DigitalIO::GPIO<60>;
using PF0 = DigitalIO::GPIO<61>;


}  // namespace pins
using LED = devices::LED<pins::PA7>;
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_EASYAVR128_HAL_BOARD_H_
