#include <hal/hal>

constexpr hal::DigitalIO pin2(hal::mcu::pin_scl);

int main() {
    pin2.init(hal::DigitalIO::OUTPUT);

    constexpr auto pin3 = hal::DigitalIO(hal::mcu::pin_sda);
    pin3.init(hal::DigitalIO::INPUT);

    while (true) {
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();
        pin2.set();
        pin2.reset();

        _delay_ms(200);
        bool pin_state = pin3.read();
        pin2.write(pin_state);
        pin2.toggle();
        _delay_ms(200);
    }
}
