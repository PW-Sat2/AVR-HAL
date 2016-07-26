#include <util/delay.h>

#include "TWI.h"

int main() {
    hal::TWI::init(100000);
    hal::TWI::enable_internal_pullups();
    hal::I2C_Device_t<hal::TWI> dev(0x1E);

    while (true) {
        dev.write(0x12);
        _delay_ms(10);
    }
}
