#include <hal/hal>

hal::I2C::Hardware twi;

int main() {
    twi.init<10000>();
    twi.enable_internal_pullups();

    hal::AT24C02 memory{twi};

    hal::Serial0.init(115200, hal::STDIO::ENABLE);

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
