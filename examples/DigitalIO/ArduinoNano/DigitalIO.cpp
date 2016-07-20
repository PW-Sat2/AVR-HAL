#include <util/delay.h>
#include "periph/DigitalIO.h"
#include "boards/boards.h"

constexpr hal::DigitalIO pinD3(hal::bsp::pins::D3);

int main() {
    pinD3.init(hal::DigitalIO::INPUT);
    
    constexpr auto pin2 = hal::DigitalIO(2);
    pin2.init(hal::DigitalIO::OUTPUT);
    
    // constexpr hal::DigitalIO pinBad(0);  // <- compile error

    // int i; constexpr hal::DigitalIO pinBad2(i);  // <- compile error
    
    while(1) {
        _delay_ms(200);
      
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        
        bool pin_state = pinD3.read();
    }
}
