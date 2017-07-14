#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;
using namespace hal::devices;

int main() {
    hal::Serial0.init(115200);
    hal::Serial0.redirect_stdio();
    hal::Serial0.redirect_stderr();

    using pin_sda = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    using pin_scl = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

    using i2c = hal::I2C::Software<pin_sda, pin_scl>;
    i2c::init();

    using memory = AT24C02::AT24C02<i2c>;


    AT24C02::Data<10> mem{0};

    for (int i = 0; i < 10; ++i) {
        mem.data[i] = i;
    }

    memory::write(mem);

    hal::sleep_for(1000ms);

    while (true) {
        AT24C02::Data<10> mem_read{0};
        memory::read(mem_read);

        for (const uint8_t x : mem_read.data) {
            printf("%d, ", x);
        }
        printf("\r\n");
        hal::sleep_for(100ms);
    }
}
