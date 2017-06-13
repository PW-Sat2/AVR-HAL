#include <hal/hal>

using namespace hal;

using pin_ss = hal::DigitalIO::GPIO<hal::mcu::pin_ss>;

using spi_hard = hal::SPI::Hardware<pin_ss,
                   SPI::HardwareClockDivisor::SPIHard_DIV_4,
                   SPI::Polarity::idle_high,
                   SPI::Phase::leading_sample,
                   SPI::DataOrder::LSB_first>;

using pin_mosi = hal::DigitalIO::GPIO<hal::mcu::pin_mosi>;
using pin_miso = hal::DigitalIO::GPIO<hal::mcu::pin_miso>;
using pin_sck = hal::DigitalIO::GPIO<hal::mcu::pin_sck>;

using spi_soft = hal::SPI::Software<pin_mosi, pin_miso, pin_sck, pin_ss, SPI::Polarity::idle_high,  //
                   SPI::Phase::leading_sample>;

int main() {
    spi_hard::init();
    spi_soft::init();

    spi_hard::init();
    spi_soft::init();

    spi_hard::transfer(0xFF);
    spi_soft::transfer(0xFF);

    std::array<uint8_t, 3> data = {1, 2, 3};

    spi_soft::transfer(data, data);
    spi_hard::transfer(data, data);
}
