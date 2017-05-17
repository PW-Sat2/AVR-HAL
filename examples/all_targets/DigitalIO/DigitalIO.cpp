#include <hal/hal>

hal::DigitalIO<hal::mcu::pin_scl> pin2;

int main() {
    pin2.init(hal::IDigitalIO::Mode::OUTPUT);

    auto pin3 = hal::DigitalIO<hal::mcu::pin_sda>();
    pin3.init(hal::IDigitalIO::Mode::INPUT);

    hal::IDigitalIO& interface = pin2;

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
