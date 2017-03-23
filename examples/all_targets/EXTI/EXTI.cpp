#include <hal/hal>

ISR(INT0_vect) {
    printf("a");
    _delay_ms(10);
}

ISR(INT1_vect) {
    printf("b");
    _delay_ms(10);
}

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    printf("INIT!\r\n");

    constexpr hal::ExternalInterrupt::Line<0> line(hal::ExternalInterrupt::Mode::rising);
    constexpr hal::ExternalInterrupt::Line<1> line2(hal::ExternalInterrupt::Mode::rising);
    line.enable();
    line2.enable();

    sei();

    while (true) {
    }
}
