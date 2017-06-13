#ifndef HAL_BOARDS_ARDUINOMEGA2560_HAL_BOARD_H_
#define HAL_BOARDS_ARDUINOMEGA2560_HAL_BOARD_H_

#include "hal/periph.h"
namespace hal {
namespace bsp {
namespace pins {

using D0  = DigitalIO::GPIO<2>;
using D1  = DigitalIO::GPIO<3>;
using D2  = DigitalIO::GPIO<6>;
using D3  = DigitalIO::GPIO<7>;
using D4  = DigitalIO::GPIO<1>;
using D5  = DigitalIO::GPIO<5>;
using D6  = DigitalIO::GPIO<15>;
using D7  = DigitalIO::GPIO<16>;
using D8  = DigitalIO::GPIO<17>;
using D9  = DigitalIO::GPIO<18>;
using D10 = DigitalIO::GPIO<23>;
using D11 = DigitalIO::GPIO<24>;
using D12 = DigitalIO::GPIO<25>;
using D13 = DigitalIO::GPIO<26>;
using D14 = DigitalIO::GPIO<64>;
using D15 = DigitalIO::GPIO<63>;
using D16 = DigitalIO::GPIO<13>;
using D17 = DigitalIO::GPIO<12>;
using D18 = DigitalIO::GPIO<46>;
using D19 = DigitalIO::GPIO<45>;
using D20 = DigitalIO::GPIO<44>;
using D21 = DigitalIO::GPIO<43>;
using D22 = DigitalIO::GPIO<78>;
using D23 = DigitalIO::GPIO<77>;
using D24 = DigitalIO::GPIO<76>;
using D25 = DigitalIO::GPIO<75>;
using D26 = DigitalIO::GPIO<74>;
using D27 = DigitalIO::GPIO<73>;
using D28 = DigitalIO::GPIO<72>;
using D29 = DigitalIO::GPIO<71>;
using D30 = DigitalIO::GPIO<60>;
using D31 = DigitalIO::GPIO<59>;
using D32 = DigitalIO::GPIO<58>;
using D33 = DigitalIO::GPIO<57>;
using D34 = DigitalIO::GPIO<56>;
using D35 = DigitalIO::GPIO<55>;
using D36 = DigitalIO::GPIO<54>;
using D37 = DigitalIO::GPIO<53>;
using D38 = DigitalIO::GPIO<50>;
using D39 = DigitalIO::GPIO<70>;
using D40 = DigitalIO::GPIO<52>;
using D41 = DigitalIO::GPIO<51>;
using D42 = DigitalIO::GPIO<42>;
using D43 = DigitalIO::GPIO<41>;
using D44 = DigitalIO::GPIO<40>;
using D45 = DigitalIO::GPIO<39>;
using D46 = DigitalIO::GPIO<38>;
using D47 = DigitalIO::GPIO<37>;
using D48 = DigitalIO::GPIO<36>;
using D49 = DigitalIO::GPIO<35>;
using D50 = DigitalIO::GPIO<22>;
using D51 = DigitalIO::GPIO<21>;
using D52 = DigitalIO::GPIO<20>;
using D53 = DigitalIO::GPIO<19>;

using A0  = DigitalIO::GPIO<97>;
using A1  = DigitalIO::GPIO<96>;
using A2  = DigitalIO::GPIO<95>;
using A3  = DigitalIO::GPIO<94>;
using A4  = DigitalIO::GPIO<93>;
using A5  = DigitalIO::GPIO<92>;
using A6  = DigitalIO::GPIO<91>;
using A7  = DigitalIO::GPIO<90>;
using A8  = DigitalIO::GPIO<89>;
using A9  = DigitalIO::GPIO<88>;
using A10 = DigitalIO::GPIO<87>;
using A11 = DigitalIO::GPIO<86>;
using A12 = DigitalIO::GPIO<85>;
using A13 = DigitalIO::GPIO<84>;
using A14 = DigitalIO::GPIO<83>;
using A15 = DigitalIO::GPIO<82>;

}  // namespace pins

using LED = devices::LED<pins::D13>;
}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_ARDUINOMEGA2560_HAL_BOARD_H_
