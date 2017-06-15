#include <hal/hal>

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
        _delay_ms(200);

        mux_1::select(ADG849::Channel::S2);
        mux_2::select(ADG849::Channel::S2);
        _delay_ms(200);

        ADG849::Channel channel = ADG849::Channel::S1;
        mux_1::select(channel);
        mux_2::select(channel);
        _delay_ms(200);

        channel = ADG849::Channel::S2;
        mux_1::select(channel);
        mux_2::select(channel);
        _delay_ms(200);
    }
}
