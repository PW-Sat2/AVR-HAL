#ifndef HAL_ARDUINOMEGA_H_
#define HAL_ARDUINOMEGA_H_

#include "periph/GPIO.h"
#include "devices/LED.h"

namespace hal {
namespace bsp {

constexpr static DigitalIO::Pin D0 = 2;
constexpr static DigitalIO::Pin D1 = 3;
constexpr static DigitalIO::Pin D2 = 6;
constexpr static DigitalIO::Pin D3 = 7;
constexpr static DigitalIO::Pin D4 = 1;
constexpr static DigitalIO::Pin D5 = 5;
constexpr static DigitalIO::Pin D6 = 15;
constexpr static DigitalIO::Pin D7 = 16;
constexpr static DigitalIO::Pin D8 = 17;
constexpr static DigitalIO::Pin D9 = 18;
constexpr static DigitalIO::Pin D10 = 23;
constexpr static DigitalIO::Pin D11 = 24;
constexpr static DigitalIO::Pin D12 = 25;
constexpr static DigitalIO::Pin D13 = 26;
constexpr static DigitalIO::Pin D14 = 64;
constexpr static DigitalIO::Pin D15 = 63;
constexpr static DigitalIO::Pin D16 = 13;
constexpr static DigitalIO::Pin D17 = 12;
constexpr static DigitalIO::Pin D18 = 46;
constexpr static DigitalIO::Pin D19 = 45;
constexpr static DigitalIO::Pin D20 = 44;
constexpr static DigitalIO::Pin D21 = 43;
constexpr static DigitalIO::Pin D22 = 78;
constexpr static DigitalIO::Pin D23 = 77;
constexpr static DigitalIO::Pin D24 = 76;
constexpr static DigitalIO::Pin D25 = 75;
constexpr static DigitalIO::Pin D26 = 74;
constexpr static DigitalIO::Pin D27 = 73;
constexpr static DigitalIO::Pin D28 = 72;
constexpr static DigitalIO::Pin D29 = 71;
constexpr static DigitalIO::Pin D30 = 60;
constexpr static DigitalIO::Pin D31 = 59;
constexpr static DigitalIO::Pin D32 = 58;
constexpr static DigitalIO::Pin D33 = 57;
constexpr static DigitalIO::Pin D34 = 56;
constexpr static DigitalIO::Pin D35 = 55;
constexpr static DigitalIO::Pin D36 = 54;
constexpr static DigitalIO::Pin D37 = 53;
constexpr static DigitalIO::Pin D38 = 50;
constexpr static DigitalIO::Pin D39 = 70;
constexpr static DigitalIO::Pin D40 = 52;
constexpr static DigitalIO::Pin D41 = 51;
constexpr static DigitalIO::Pin D42 = 42;
constexpr static DigitalIO::Pin D43 = 41;
constexpr static DigitalIO::Pin D44 = 40;
constexpr static DigitalIO::Pin D45 = 39;
constexpr static DigitalIO::Pin D46 = 38;
constexpr static DigitalIO::Pin D47 = 37;
constexpr static DigitalIO::Pin D48 = 36;
constexpr static DigitalIO::Pin D49 = 35;
constexpr static DigitalIO::Pin D50 = 22;
constexpr static DigitalIO::Pin D51 = 21;
constexpr static DigitalIO::Pin D52 = 20;
constexpr static DigitalIO::Pin D53 = 19;

// Arduino A-pins
constexpr static DigitalIO::Pin A0 = 97;
constexpr static DigitalIO::Pin A1 = 96;
constexpr static DigitalIO::Pin A2 = 95;
constexpr static DigitalIO::Pin A3 = 94;
constexpr static DigitalIO::Pin A4 = 93;
constexpr static DigitalIO::Pin A5 = 92;
constexpr static DigitalIO::Pin A6 = 91;
constexpr static DigitalIO::Pin A7 = 90;
constexpr static DigitalIO::Pin A8 = 89;
constexpr static DigitalIO::Pin A9 = 88;
constexpr static DigitalIO::Pin A10 = 87;
constexpr static DigitalIO::Pin A11 = 86;
constexpr static DigitalIO::Pin A12 = 85;
constexpr static DigitalIO::Pin A13 = 84;
constexpr static DigitalIO::Pin A14 = 83;
constexpr static DigitalIO::Pin A15 = 82;

constexpr static DigitalIO::Pin LED = D13;

}
}
#endif  // HAL_ARDUINOMEGA_H_
