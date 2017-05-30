#include <hal/hal>

hal::DigitalIO::GPIO<hal::mcu::pin_scl> mux_pin_1;
hal::ADG849 mux_1(mux_pin_1);

int main() {
    hal::DigitalIO::GPIO<hal::mcu::pin_sda> mux_pin_2;
    hal::ADG849 mux_2(mux_pin_2);

    mux_1.init(hal::ADG849::Channel::S1);
    mux_2.init(hal::ADG849::Channel::S1);

    while (true) {
        mux_1.select(hal::ADG849::Channel::S1);
        mux_2.select(hal::ADG849::Channel::S1);
        _delay_ms(200);

        mux_1.select(hal::ADG849::Channel::S2);
        mux_2.select(hal::ADG849::Channel::S2);
        _delay_ms(200);

        hal::ADG849::Channel channel = hal::ADG849::Channel::S1;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);

        channel = hal::ADG849::Channel::S2;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);
    }
}
