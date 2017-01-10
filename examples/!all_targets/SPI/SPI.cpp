#include "SPIHardware.h"
#include "SPISoftware.h"
#include "SPI.h"
#include "mcu.h"
#include "array_view.h"

using namespace hal;

using spi = hal::SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_4,
                               SPI::Polarity::idle_high,
                               SPI::Phase::leading_sample,
                               SPI::DataOrder::LSB_first>;

using spiSoft = hal::SPI::Software<1, 2, 3,
                                   SPI::Polarity::idle_high,
                                   SPI::Phase::leading_sample,
                                   SPI::DataOrder::LSB_first>;

int main() {
    spi::init();
    spiSoft::init();

    constexpr SPI::Device<spi> dev1{hal::mcu::pin_sda};  // I2C pin because we know
                                                        // it exists on every board!

    constexpr SPI::Device<spiSoft> dev2{hal::mcu::pin_scl};  // I2C pin because we know
                                                            // it exists on every board!
    dev1.init();
    dev2.init();

    dev1.shift(0xFF);
    dev2.shift(0xFF);

    uint8_t data[] = { 1, 2, 3 };

    dev1.transfer(hal::libs::make_array_view(data),
            hal::libs::make_array_view(data));
}
