#include <util/delay.h>
#include "DigitalIO.h"
#include "boards.h"

constexpr hal::DigitalIO pin2(2);

int main() {
    pin2.init(hal::DigitalIO::INPUT);
    
    constexpr auto pinD13 = hal::DigitalIO(hal::bsp::pins::D13);
    pinD13.init(hal::DigitalIO::OUTPUT);
    
    // constexpr hal::DigitalIO pinBad(0);  // <- compile error

    // int i; constexpr hal::DigitalIO pinBad2(i);  // <- compile error
    
    while(1) {
        bool pin_state = pin2.read();
        _delay_ms(200);
        pinD13.set();
        pinD13.reset();
        pinD13.set();
        pinD13.toggle();
        pinD13.write(true);
        pinD13.write(false);
	}
}
