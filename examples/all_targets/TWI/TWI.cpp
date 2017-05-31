#include <hal/hal>

int main() {
    hal::I2C::Hardware twi;
    twi.init<100000>();
    twi.enable_internal_pullups();

    while (true) {
        hal::libs::array<uint8_t, 3> arr = {0x00, 0x01, 0x02};
        twi.write(0xAA, arr);
        twi.read(0xAB, arr);
        twi.writeRead(0xAC, arr, arr);
        _delay_ms(10);
    }
}
