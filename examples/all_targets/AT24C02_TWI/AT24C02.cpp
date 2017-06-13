#include <hal/hal>

using hal::Serial0;

using twi = hal::I2C::Hardware;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    twi::init<10000>();
    twi::enable_internal_pullups();

    hal::AT24C02<twi> memory;

    hal::AT24C02_::Data<10> mem{0};

    for (int i = 0; i < 10; ++i) {
        mem.data[i] = i;
    }

    memory.write(mem);

    _delay_ms(1000);

    while (true) {
        hal::AT24C02_::Data<10> mem_read{0};
        memory.read(mem_read);

        for (const uint8_t x : mem_read.data) {
            printf("%d, ", x);
        }
        printf("\r\n");
        _delay_ms(100);
    }
}
