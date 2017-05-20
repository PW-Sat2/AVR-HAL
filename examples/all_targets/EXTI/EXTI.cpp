#include <hal/hal>

ISR(INT0_vect) {
    printf("a");
    _delay_ms(10);
}

ISR(INT1_vect) {
    printf("b");
    _delay_ms(10);
}

using namespace hal::DigitalIO::ExternalInterrupt;

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    printf("INIT!\r\n");

    constexpr Line<0> line(Mode::rising);
    constexpr Line<1> line2(Mode::rising);
    line.enable();
    line2.enable();

    sei();

    while (true) {
    }
}
