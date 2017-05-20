#include <hal/hal>

int main() {
    hal::DigitalIO<hal::mcu::pin_sda> pin_sda;
    hal::DigitalIO<hal::mcu::pin_scl> pin_scl;

    hal::I2C::Software i2c{pin_sda, pin_scl};

    i2c.init();

    while (true) {
        i2c.write(0x12);
        _delay_ms(10);
    }
}
