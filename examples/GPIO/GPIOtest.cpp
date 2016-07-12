#include <util/delay.h>
#include "periph/GPIO.h"
#include "devices/LED.h"
#include "boards/boards.h"

constexpr hal::DigitalIO pin3(hal::bsp::D3);

int main() {
    hal::bsp::led.init();

    pin3.init(hal::DigitalIO::OUTPUT);
    
    constexpr auto pin2 = hal::DigitalIO(hal::bsp::D2);
    pin2.init(hal::DigitalIO::OUTPUT);
    
    // constexpr hal::DigitalIO pinBad(0);  // <- compile error
    
    while(1) {
        hal::bsp::led.toggle();
        _delay_ms(200);
      
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        
        pin3.set();
        pin3.reset();
        pin3.set();
        pin3.reset();
        pin3.set();
        pin3.reset();
	}
}
