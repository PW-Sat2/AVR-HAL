#include <hal/hal>

using namespace std::chrono_literals;
using pin2 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

int main() {
    pin2::init(hal::DigitalIO::Mode::OUTPUT);

    using pin3 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    pin3::init(hal::DigitalIO::Mode::INPUT);

    while (true) {
        pin2::set();
        pin2::reset();

        hal::sleep_for(200ms);
        bool pin_state = pin3::read();
        pin2::write(pin_state);
        pin2::toggle();
        hal::sleep_for(200ms);
    }
}
