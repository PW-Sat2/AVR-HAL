#include <hal/hal>

using hal::Serial0;
using hal::devices::ADXRS453::ADXRS453;

using gpio = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;

using spi = hal::SPI::Hardware<gpio,
                               hal::SPI::HardwareClockDivisor::SPIHard_DIV_4,
                               hal::SPI::Polarity::idle_high,
                               hal::SPI::Phase::leading_sample,
                               hal::SPI::DataOrder::LSB_first>;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stderr();

    spi::init();
    using gyro1 = ADXRS453<spi>;

    hal::Serial0.printf("Start \r\n");

    bool status = gyro1::device_status();
    hal::Serial0.printf("Sensor init = %d\r\n", status);

    while (true) {
        float temperature    = gyro1::get_temperature();
        float rate           = gyro1::get_rate();
        uint32_t sensor_data = gyro1::get_sensor_data();

        hal::Serial0.printf("Temperature = %f;\t", temperature);
        hal::Serial0.printf("Rate = %f;\t", rate);
        hal::Serial0.printf("Sensor data = %ul\r\n", sensor_data);

        _delay_ms(500);
    }
}
