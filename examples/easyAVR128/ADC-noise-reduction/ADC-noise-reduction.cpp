#include <avr/io.h>
#include <util/delay.h>
#include "Analog.h"
#include "Serial.h"

using hal::InternalADC;
using hal::Serial0;


volatile int x;

ISR(ADC_vect) {
    x = InternalADC::read_nowait();
}

int main() {
    Serial0.init(115200, hal::STDIO::ENABLE);
    InternalADC::init(InternalADC::Prescaler::DIV_128,
                      InternalADC::Reference::AVcc, 5);

    InternalADC::select_channel(InternalADC::Input::ADC0);

    InternalADC::enable_interrupt();
    sei();

    hal::cpu::set_sleep_mode(hal::cpu::SleepModes::ADC_Noise_Reduction);
    while (true) {
        hal::cpu::sleep_cpu();  // triggers ADC conversion
        printf("read: %d\r\n", x);
    }
}
