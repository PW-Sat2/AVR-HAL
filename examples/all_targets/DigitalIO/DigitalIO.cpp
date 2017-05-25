#include <hal/hal>

hal::DigitalIO::GPIO<hal::mcu::pin_scl> pin2;

int main() {
    pin2.init(hal::DigitalIO::Interface::Mode::OUTPUT);

    auto pin3 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>();
    pin3.init(hal::DigitalIO::Interface::Mode::INPUT);

    hal::DigitalIO::Interface& interface = pin2;

    while (true) {
        pin2.set();
        pin2.reset();
        interface.set();
        interface.reset();

        _delay_ms(200);
        bool pin_state = pin3.read();
        pin2.write(pin_state);
        pin2.toggle();
        _delay_ms(200);
    }
}
