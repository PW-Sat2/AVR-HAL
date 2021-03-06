#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;
using namespace hal::devices;

using twi = hal::I2C::Hardware;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    twi::init<10000>();
    twi::enable_internal_pullups();

    using memory = AT24C02::AT24C02<twi>;

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
