#include <hal/hal>

int main() {
    hal::DigitalIO::GPIO<hal::mcu::pin_sda> pin_sda;
    hal::DigitalIO::GPIO<hal::mcu::pin_scl> pin_scl;

    hal::I2C::Software i2c{pin_sda, pin_scl};

    i2c.init();

    while (true) {
        hal::libs::array<uint8_t, 3> arr = {0x00, 0x01, 0x02};
        i2c.write(0xAA, arr);
        i2c.read(0xAB, arr);
        i2c.writeRead(0xAC, arr, arr);
        _delay_ms(10);
    }
}
