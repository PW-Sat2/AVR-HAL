#include <util/delay.h>
#include "periph/GPIO.h"
#include "devices/LED.h"
#include "boards/boards.h"
#include "periph/Serial.h"

constexpr hal::DigitalIO pin3(hal::bsp::pins::D3);

constexpr static SerialX_<0> Serial0;
//constexpr static SerialX_<1> Serial1;

int main() {
	Serial0.init(9600);
	//Serial1.init(9600);
    //hal::bsp::led.init();

    //pin3.init(hal::DigitalIO::OUTPUT);
    //
    //constexpr auto pin2 = hal::DigitalIO(hal::bsp::pins::D2);
    //pin2.init(hal::DigitalIO::OUTPUT);
    
    // constexpr hal::DigitalIO pinBad(0);  // <- compile error
	
	// int i; constexpr hal::DigitalIO pinBad2(i);  // <- compile error
    
    while(1) {
		static int i = 0;
		//Serial0.printf("A: %d\r\n", i++);
		//printfX(Serial0, "A");
		//Serial1.printf("B");
		Serial0.print_byte('A');
		//Serial1.print_byte('B');
        //hal::bsp::led.toggle();
        //_delay_ms(200);
      
        //pin2.set();
        //pin2.reset();
        //pin2.set();
        //pin2.reset();
        //pin2.set();
        //pin2.reset();
        //
        //pin3.set();
        //pin3.reset();
        //pin3.set();
        //pin3.reset();
        //pin3.set();
        //pin3.reset();
	}
}
