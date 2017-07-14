#include <hal/hal>

using namespace std::chrono_literals;
using namespace hal::devices;

using mux_pin_1 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;
using mux_1     = ADG849::ADG849<mux_pin_1>;

int main() {
    using mux_pin_2 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    using mux_2     = ADG849::ADG849<mux_pin_2>;

    mux_1::init(ADG849::Channel::S1);
    mux_2::init(ADG849::Channel::S1);

    while (true) {
        mux_1::select(ADG849::Channel::S1);
        mux_2::select(ADG849::Channel::S1);
        hal::sleep_for(200ms);

        mux_1::select(ADG849::Channel::S2);
        mux_2::select(ADG849::Channel::S2);
        hal::sleep_for(200ms);

        ADG849::Channel channel = ADG849::Channel::S1;
        mux_1::select(channel);
        mux_2::select(channel);
        hal::sleep_for(200ms);

        channel = ADG849::Channel::S2;
        mux_1::select(channel);
        mux_2::select(channel);
        hal::sleep_for(200ms);
    }
}
