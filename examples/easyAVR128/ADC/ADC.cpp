#include <avr/io.h>
#include <util/delay.h>
#include "Analog.h"
#include "Serial.h"

using hal::InternalADC;
using hal::Serial0;


volatile uint8_t flag = 0;
volatile int x;

void foo(int val) {
    x = val;
    flag = 1;
}


int main() {
    Serial0.init(115200, hal::STDIO::ENABLE);
    InternalADC::init(InternalADC::Prescaler::DIV_128,
                      InternalADC::Reference::AVcc);

    InternalADC::set_channel(InternalADC::Input::ADC0);

    InternalADC::enable_interrupt(foo);
    InternalADC::set_trigger(InternalADC::TriggerSource::FreeRunning);
    InternalADC::trigger_conversion();
    sei();

    while (true) {
        if (flag) {
            printf("read: %d\r\n", x);
            flag = 0;
        }
    }
}
