#include <avr/io.h>
#include <util/delay.h>
#include "Analog.h"
#include "Serial.h"

using hal::InternalADC;
using hal::Serial0;


int main() {
    Serial0.init(115200, hal::STDIO::ENABLE);
    InternalADC::init(InternalADC::Prescaler::DIV_128,
                      InternalADC::Reference::AVcc, 3.3);

    InternalADC::select_channel(InternalADC::Input::ADC0);

    while (true) {
        printf("read: %d = %f V\r\n", InternalADC::read(), InternalADC::read_voltage());
    }
}
