#include <hal/hal>

using namespace hal;

hal::SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_4,
                   SPI::Polarity::idle_high,
                   SPI::Phase::leading_sample,
                   SPI::DataOrder::LSB_first> spi;

hal::DigitalIO<hal::mcu::pin_mosi> pin_mosi;
hal::DigitalIO<hal::mcu::pin_miso> pin_miso;
hal::DigitalIO<hal::mcu::pin_sck> pin_sck;
hal::DigitalIO<hal::mcu::pin_sda> pin_sda;
hal::DigitalIO<hal::mcu::pin_scl> pin_scl;

hal::SPI::Software<SPI::Polarity::idle_high,
                   SPI::Phase::leading_sample> spiSoft{pin_mosi, pin_miso, pin_sck};

int main() {
    spi.init();
    spiSoft.init();

    constexpr SPI::Device dev1{spi, pin_sda};  // I2C pin because we know
                                                        // it exists on every board!

    constexpr SPI::Device dev2{spiSoft, pin_scl};  // I2C pin because we know
                                                            // it exists on every board!
    dev1.init();
    dev2.init();

    dev1.shift(0xFF);
    dev2.shift(0xFF);

    hal::libs::array<uint8_t, 3> data = {1, 2, 3};

    dev1.transfer(data, data);
}
