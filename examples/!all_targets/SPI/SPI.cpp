#include "SPI.h"
#include "mcu.h"
#include "array_view.h"

int main() {
    hal::SPI::init(hal::SPI::Polarity::idle_high,
            hal::SPI::Phase::leading_sample, hal::SPI::DataOrder::MSB_first,
            hal::SPI::ClockDivisor::DIV_128);

    constexpr hal::SPI_Device dev1{hal::mcu::pin_sda};  // I2C pin because we know
                                                        // it exists on every board!
    dev1.init();

    dev1.shift(0xFF);

    uint8_t data[] = { 1, 2, 3 };

    dev1.transfer(hal::libs::make_array_view(data),
            hal::libs::make_array_view(data));
}
