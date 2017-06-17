#include <hal/hal>

using hal::Serial0;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        _delay_ms(100);
    }

    hal::cpu::set_clock_divider<10>();

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        _delay_ms(100);
    }
}
