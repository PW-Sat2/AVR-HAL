#include <hal/hal>

constexpr hal::ADG849 mux_1(hal::mcu::pin_scl);

int main() {
    constexpr hal::ADG849 mux_2(hal::mcu::pin_sda);

    mux_1.init();
    mux_2.init();

    while (true) {
        mux_1.select(0);
        mux_2.select(0);
        _delay_ms(200);

        mux_1.select(1);
        mux_2.select(1);
        _delay_ms(200);

        uint8_t channel = 0;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);

        channel = 1;
        mux_1.select(channel);
        mux_2.select(channel);
        _delay_ms(200);
    }
}
