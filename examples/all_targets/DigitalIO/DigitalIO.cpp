#include <hal/hal>

using pin2 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

int main() {
    pin2::init(hal::DigitalIO::Mode::OUTPUT);

    using pin3 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    pin3::init(hal::DigitalIO::Mode::INPUT);

    while (true) {
        pin2::set();
        pin2::reset();

        _delay_ms(200);
        bool pin_state = pin3::read();
        pin2::write(pin_state);
        pin2::toggle();
        _delay_ms(200);
    }
}
