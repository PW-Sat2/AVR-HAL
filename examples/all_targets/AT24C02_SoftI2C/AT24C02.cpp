#include <hal/hal>

using hal::Serial0;

int main() {
    hal::Serial0.init(115200);
    hal::Serial0.redirect_stdio();
    hal::Serial0.redirect_stderr();

    hal::DigitalIO::GPIO<hal::mcu::pin_sda> pin_sda;
    hal::DigitalIO::GPIO<hal::mcu::pin_scl> pin_scl;

    hal::I2C::Software i2c{pin_sda, pin_scl};

    hal::AT24C02 memory{i2c};

    i2c.init();

    hal::AT24C02::Data<10> mem{0};

    for (int i = 0; i < 10; ++i) {
        mem.data[i] = i;
    }

    memory.write(mem);

    _delay_ms(1000);

    while (true) {
        hal::AT24C02::Data<10> mem_read{0};
        memory.read(mem_read);

        for (const uint8_t x : mem_read.data) {
            printf("%d, ", x);
        }
        printf("\r\n");
        _delay_ms(100);
    }
}
