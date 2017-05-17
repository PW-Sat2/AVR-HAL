#include <hal/hal>

int main() {
    hal::DigitalIO<hal::mcu::pin_sda> pin_sda;
    hal::DigitalIO<hal::mcu::pin_scl> pin_scl;

    hal::SoftI2C i2c{pin_sda, pin_scl};

    i2c.init();
    hal::I2C_Device dev{i2c, 0x1E};

    while (true) {
        dev.write(0x12);
        _delay_ms(10);
    }
}
