#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;
using namespace hal::DigitalIO::ExternalInterrupt;

ISR(INT0_vect) {
    printf("a");
    hal::sleep_for(10ms);
}

ISR(INT1_vect) {
    printf("b");
    hal::sleep_for(10ms);
}

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();
    printf("INIT!\r\n");

    using line  = Line<0, Mode::rising>;
    using line2 = Line<1, Mode::rising>;
    line::enable();
    line2::enable();

    sei();

    while (true) {
    }
}
