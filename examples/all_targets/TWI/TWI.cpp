#include <hal/hal>

int main() {
    hal::TWI twi;
    twi.init<100000>();
    twi.enable_internal_pullups();
    hal::I2C_Device dev{twi, 0x1E};

    while (true) {
        dev.write(0x12);
        _delay_ms(10);
    }
}
