#include <hal/hal>

using twi = hal::I2C::Hardware;

int main() {
    twi::init<100000>();
    twi::enable_internal_pullups();

    while (true) {
        std::array<uint8_t, 3> arr = {0x00, 0x01, 0x02};
        twi::write(0xAA, arr);
        twi::read(0xAB, arr);
        twi::write_read(0xAC, arr, arr);
        _delay_ms(10);
    }
}
