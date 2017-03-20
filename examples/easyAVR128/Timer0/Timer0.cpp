#include <hal/hal>

ISR(TIMER0_OVF_vect) {
    hal::Serial0.print_byte('x');
}

int main() {
    hal::Serial0.init(9600);

    hal::Timer0::init(hal::Timer0::Prescaler::DIV_1024, hal::Timer0::Mode::CTC);

    hal::Timer0::enable_overflow_interrupt();
    hal::Timer0::set_output_compare(10);

    while (true) {
        static int counter = 0;
        hal::Serial0.printf("Counter value = %d\r\n", counter++);

        _delay_ms(200);
    }
}
