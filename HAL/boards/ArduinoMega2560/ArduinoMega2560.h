#ifndef HAL_ARDUINOMEGA_H_
#define HAL_ARDUINOMEGA_H_

#include "periph/DigitalIO.h"
#include "devices/LED.h"

namespace hal {
	
namespace bsp {

namespace pins {
static constexpr DigitalIO::Pin D0 = 2;
static constexpr DigitalIO::Pin D1 = 3;
static constexpr DigitalIO::Pin D2 = 6;
static constexpr DigitalIO::Pin D3 = 7;
static constexpr DigitalIO::Pin D4 = 1;
static constexpr DigitalIO::Pin D5 = 5;
static constexpr DigitalIO::Pin D6 = 15;
static constexpr DigitalIO::Pin D7 = 16;
static constexpr DigitalIO::Pin D8 = 17;
static constexpr DigitalIO::Pin D9 = 18;
static constexpr DigitalIO::Pin D10 = 23;
static constexpr DigitalIO::Pin D11 = 24;
static constexpr DigitalIO::Pin D12 = 25;
static constexpr DigitalIO::Pin D13 = 26;
static constexpr DigitalIO::Pin D14 = 64;
static constexpr DigitalIO::Pin D15 = 63;
static constexpr DigitalIO::Pin D16 = 13;
static constexpr DigitalIO::Pin D17 = 12;
static constexpr DigitalIO::Pin D18 = 46;
static constexpr DigitalIO::Pin D19 = 45;
static constexpr DigitalIO::Pin D20 = 44;
static constexpr DigitalIO::Pin D21 = 43;
static constexpr DigitalIO::Pin D22 = 78;
static constexpr DigitalIO::Pin D23 = 77;
static constexpr DigitalIO::Pin D24 = 76;
static constexpr DigitalIO::Pin D25 = 75;
static constexpr DigitalIO::Pin D26 = 74;
static constexpr DigitalIO::Pin D27 = 73;
static constexpr DigitalIO::Pin D28 = 72;
static constexpr DigitalIO::Pin D29 = 71;
static constexpr DigitalIO::Pin D30 = 60;
static constexpr DigitalIO::Pin D31 = 59;
static constexpr DigitalIO::Pin D32 = 58;
static constexpr DigitalIO::Pin D33 = 57;
static constexpr DigitalIO::Pin D34 = 56;
static constexpr DigitalIO::Pin D35 = 55;
static constexpr DigitalIO::Pin D36 = 54;
static constexpr DigitalIO::Pin D37 = 53;
static constexpr DigitalIO::Pin D38 = 50;
static constexpr DigitalIO::Pin D39 = 70;
static constexpr DigitalIO::Pin D40 = 52;
static constexpr DigitalIO::Pin D41 = 51;
static constexpr DigitalIO::Pin D42 = 42;
static constexpr DigitalIO::Pin D43 = 41;
static constexpr DigitalIO::Pin D44 = 40;
static constexpr DigitalIO::Pin D45 = 39;
static constexpr DigitalIO::Pin D46 = 38;
static constexpr DigitalIO::Pin D47 = 37;
static constexpr DigitalIO::Pin D48 = 36;
static constexpr DigitalIO::Pin D49 = 35;
static constexpr DigitalIO::Pin D50 = 22;
static constexpr DigitalIO::Pin D51 = 21;
static constexpr DigitalIO::Pin D52 = 20;
static constexpr DigitalIO::Pin D53 = 19;

static constexpr DigitalIO::Pin A0 = 97;
static constexpr DigitalIO::Pin A1 = 96;
static constexpr DigitalIO::Pin A2 = 95;
static constexpr DigitalIO::Pin A3 = 94;
static constexpr DigitalIO::Pin A4 = 93;
static constexpr DigitalIO::Pin A5 = 92;
static constexpr DigitalIO::Pin A6 = 91;
static constexpr DigitalIO::Pin A7 = 90;
static constexpr DigitalIO::Pin A8 = 89;
static constexpr DigitalIO::Pin A9 = 88;
static constexpr DigitalIO::Pin A10 = 87;
static constexpr DigitalIO::Pin A11 = 86;
static constexpr DigitalIO::Pin A12 = 85;
static constexpr DigitalIO::Pin A13 = 84;
static constexpr DigitalIO::Pin A14 = 83;
static constexpr DigitalIO::Pin A15 = 82;

static constexpr DigitalIO::Pin LED = D13;
}

constexpr static hal::LED led(pins::LED);

}
}
#endif  // HAL_ARDUINOMEGA_H_
