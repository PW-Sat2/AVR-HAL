#include <hal/hal>

using mux_pin_1 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;
hal::ADG849<mux_pin_1> mux_1;

int main() {
    using mux_pin_2 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    hal::ADG849<mux_pin_2> mux_2;

    mux_1.init( hal::ADG849_::Channel::S1);
    mux_2.init( hal::ADG849_::Channel::S1);

    while (true) {
        mux_1.select( hal::ADG849_::Channel::S1);
        mux_2.select( hal::ADG849_::Channel::S1);
        _delay_ms(200);

        mux_1.select( hal::ADG849_::Channel::S2);
        mux_2.select( hal::ADG849_::Channel::S2);
        _delay_ms(200);

         hal::ADG849_::Channel channel =  hal::ADG849_::Channel::S1;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);

        channel =  hal::ADG849_::Channel::S2;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);
    }
}
