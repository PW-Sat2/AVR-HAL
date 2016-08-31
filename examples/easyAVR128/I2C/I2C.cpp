#include <util/delay.h>

#include "TWI.h"

int main() {
    hal::TWI::init<100000>();
    hal::TWI::enable_internal_pullups();
    hal::I2C_Device<hal::TWI> dev{0x1E};

    while (true) {
        hal::libs::array<uint8_t, 20> arr_w;

        for (int i = 0; i < arr_w.size(); ++i) {
            arr_w[i] = 100-i;
        }

        dev.write(arr_w);

        _delay_ms(10);

        hal::libs::array<uint8_t, 10> arr;
        dev.read(arr);

        _delay_ms(10);
    }
}
