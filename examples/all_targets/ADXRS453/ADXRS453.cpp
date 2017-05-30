#include <hal/hal>

hal::DigitalIO::GPIO<hal::mcu::pin_sda> gpio;

hal::SPI::Hardware<hal::SPI::HardwareClockDivisor::SPIHard_DIV_4,
                   hal::SPI::Polarity::idle_high,
                   hal::SPI::Phase::leading_sample,
                   hal::SPI::DataOrder::LSB_first>
    spi(gpio);

int main() {
    hal::Serial0.init(115200);

    spi.init();
    hal::ADXRS453 gyro1(spi);

    hal::Serial0.printf("Start \r\n");

    bool status = gyro1.deviceStatus();
    hal::Serial0.printf("Sensor init = %d\r\n", status);

    while (true) {
        float temperature    = gyro1.getTemperature();
        float rate           = gyro1.getRate();
        uint32_t sensor_data = gyro1.getSensorData();

        hal::Serial0.printf("Temperature = %f;\t", temperature);
        hal::Serial0.printf("Rate = %f;\t", rate);
        hal::Serial0.printf("Sensor data = %ul\r\n", sensor_data);

        _delay_ms(500);
    }
}
