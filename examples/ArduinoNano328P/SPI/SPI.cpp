#include <util/delay.h>
#include "SPI.h"
#include "boards.h"
#include "array_view.h"

int main() {
    hal::SPI::init(hal::SPI::Polarity::idle_high,
            hal::SPI::Phase::leading_sample, hal::SPI::DataOrder::MSB_first,
            hal::SPI::ClockDivisor::DIV_128);

    constexpr hal::SPI_Device dev1{hal::bsp::pins::D10};

    dev1.init();

    while (1) {
        hal::SPI::shift(0xAA);
        dev1.shift(0x55);

        uint8_t data[] = { 1, 2, 3 };

        dev1.transfer(hal::libs::make_array_view(data),
                hal::libs::make_array_view(data));
        _delay_ms(1);
    }
}
