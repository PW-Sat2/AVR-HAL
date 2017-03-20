#include <hal/hal>

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        _delay_ms(100);
    }

    hal::cpu::set_clock_divider<10>();

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        _delay_ms(100);
    }

    hal::cpu::sleep_enable();

    while (true) {
        hal::cpu::sleep_cpu();
    }
}
