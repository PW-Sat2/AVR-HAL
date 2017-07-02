#include <hal/hal>

using hal::Serial0;
using namespace hal::devices;

using cs = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
using DDRY_pin = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

using spi = hal::SPI::Hardware<cs,
                               hal::SPI::HardwareClockDivisor::SPIHard_DIV_4,
                               hal::SPI::Polarity::idle_low,
                               hal::SPI::Phase::trailing_sample,
                               hal::SPI::DataOrder::MSB_first>;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stderr();

    spi::init();
    AD7714::AD7714<spi, DDRY_pin> ext_adc;

    hal::Serial0.printf("Start \r\n");

    ext_adc.init();
    hal::Serial0.printf("AD7714 init\r\n");

    while (true) {
        ext_adc.change_channel(AD7714::Channels::AIN3_4_CH);
        hal::Serial0.printf("Channel changed\r\n");
        ext_adc.set_filter(AD7714::Polarity::UNIPOLAR, 4000);
        hal::Serial0.printf("Filter set\r\n");
        ext_adc.set_mode(AD7714::Modes::SELF_CALIB, AD7714::Gain::GAIN_1);
        hal::Serial0.printf("Calibration started\r\n");

        while (!ext_adc.data_ready()) {}
        hal::Serial0.printf("ADC ready\r\n");

        uint24_t data = ext_adc.read_data_no_wait();
        hal::Serial0.printf("LSB = %ul;\t", data);
    }
}
