#include <hal/hal>

using namespace std::chrono_literals;

int main() {
    using pin_sda = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    using pin_scl = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

    using i2c = hal::I2C::Software<pin_sda, pin_scl>;

    i2c::init();

    while (true) {
        std::array<uint8_t, 3> arr = {0x00, 0x01, 0x02};
        i2c::write(0xAA, arr);
        i2c::read(0xAB, arr);
        i2c::write_read(0xAC, arr, arr);
        hal::sleep_for(10ms);
    }
}
