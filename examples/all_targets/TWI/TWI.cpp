#include <hal/hal>

int main() {
    hal::I2C::Hardware twi;
    twi.init<100000>();
    twi.enable_internal_pullups();

    while (true) {
        twi.write(0x12);
        _delay_ms(10);
    }
}
