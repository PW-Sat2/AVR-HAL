#ifndef HAL_ARDUINOMEGA_H_
#define HAL_ARDUINOMEGA_H_

#include "periph/GPIO.h"
#include "devices/LED.h"

namespace hal {
namespace bsp {

enum Pins {
    D0 = 2,
    D1 = 3,
    D2 = 6,
    D3 = 7,
    D4 = 1,
    D5 = 5,
    D6 = 15,
    D7 = 16,
    D8 = 17,
    D9 = 18,
    D10 = 23,
    D11 = 24,
    D12 = 25,
    D13 = 26,
    D14 = 64,
    D15 = 63,
    D16 = 13,
    D17 = 12,
    D18 = 46,
    D19 = 45,
    D20 = 44,
    D21 = 43,
    D22 = 78,
    D23 = 77,
    D24 = 76,
    D25 = 75,
    D26 = 74,
    D27 = 73,
    D28 = 72,
    D29 = 71,
    D30 = 60,
    D31 = 59,
    D32 = 58,
    D33 = 57,
    D34 = 56,
    D35 = 55,
    D36 = 54,
    D37 = 53,
    D38 = 50,
    D39 = 70,
    D40 = 52,
    D41 = 51,
    D42 = 42,
    D43 = 41,
    D44 = 40,
    D45 = 39,
    D46 = 38,
    D47 = 37,
    D48 = 36,
    D49 = 35,
    D50 = 22,
    D51 = 21,
    D52 = 20,
    D53 = 19,
    
    
    A0 = 97,
    A1 = 96,
    A2 = 95,
    A3 = 94,
    A4 = 93,
    A5 = 92,
    A6 = 91,
    A7 = 90,
    A8 = 89,
    A9 = 88,
    A10 = 87,
    A11 = 86,
    A12 = 85,
    A13 = 84,
    A14 = 83,
    A15 = 82,
    
    LED = D13
};

constexpr static hal::LED led(LED);

}
}
#endif  // HAL_ARDUINOMEGA_H_
