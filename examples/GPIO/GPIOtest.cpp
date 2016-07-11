#include "config.h"
#include "devices/LED.h"
#include <util/delay.h>

int main() {	
    hal::DigitalIO pin2 = hal::DigitalIO::init<hal::bsp::D2, hal::DigitalIO::OUTPUT>();
    
    hal::DigitalIO pin3(hal::bsp::D3);
    pin3.pinmode(hal::DigitalIO::OUTPUT);
    
    hal::LED led(hal::bsp::LED);
	led.init();
	
    while(1) {
        
        led.on();
        _delay_ms(200);
        led.off();
        _delay_ms(200);
        
        hal::DigitalIO led_pin(hal::bsp::D13);
        led_pin.set();
        led_pin.reset();
        
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
