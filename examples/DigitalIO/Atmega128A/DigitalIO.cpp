#include <util/delay.h>
#include "periph/DigitalIO.h"

constexpr hal::DigitalIO pin2(2);

int main() {
    pin2.init(hal::DigitalIO::OUTPUT);

    constexpr auto pin3 = hal::DigitalIO(3);
    pin3.init(hal::DigitalIO::INPUT);

    // constexpr hal::DigitalIO pinBad(0);  // <- compile error

    // int i; constexpr hal::DigitalIO pinBad2(i);  // <- compile error

    while (true) {
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();

        _delay_ms(200);
        bool pin_state = pin3.read();
        _delay_ms(200);
    }
}
