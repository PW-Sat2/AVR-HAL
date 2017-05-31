#include <hal/hal>

using namespace hal;

hal::DigitalIO::GPIO<hal::mcu::pin_ss> pin_ss;

hal::SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_4,
                   SPI::Polarity::idle_high,
                   SPI::Phase::leading_sample,
                   SPI::DataOrder::LSB_first>
    spi_hard{pin_ss};

hal::DigitalIO::GPIO<hal::mcu::pin_mosi> pin_mosi;
hal::DigitalIO::GPIO<hal::mcu::pin_miso> pin_miso;
hal::DigitalIO::GPIO<hal::mcu::pin_sck> pin_sck;

hal::DigitalIO::GPIO<hal::mcu::pin_sda> pin_sda;
hal::DigitalIO::GPIO<hal::mcu::pin_scl> pin_scl;

hal::SPI::Software<SPI::Polarity::idle_high,  //
                   SPI::Phase::leading_sample>
    spi_soft{pin_mosi, pin_miso, pin_sck, pin_ss};

int main() {
    spi_hard.init();
    spi_soft.init();

    spi_hard.init();
    spi_soft.init();

    spi_hard.transfer(0xFF);
    spi_soft.transfer(0xFF);

    hal::libs::array<uint8_t, 3> data = {1, 2, 3};

    SPI::Interface* interface = &spi_hard;
    interface->transfer(data, data);
}
