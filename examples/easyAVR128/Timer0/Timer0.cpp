#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;

ISR(TIMER0_OVF_vect) {
    hal::Serial0.print_byte('x');
}

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    hal::Timer0::init(hal::Timer0::Prescaler::DIV_1024, hal::Timer0::Mode::CTC);

    hal::Timer0::enable_overflow_interrupt();
    hal::Timer0::set_output_compare(10);

    while (true) {
        static int counter = 0;
        hal::Serial0.printf("Counter value = %d\r\n", counter++);

        hal::sleep_for(200ms);
    }
}
