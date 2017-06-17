#include <hal/hal>

using hal::Analog::InternalADC;
using hal::Serial0;

volatile int x;

ISR(ADC_vect) {
    x = InternalADC::read_nowait();
}

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    InternalADC::init(InternalADC::Prescaler::DIV_128,
                      InternalADC::Reference::AVcc);

    InternalADC::select_channel(InternalADC::Input::ADC0);

    InternalADC::enable_interrupt();
    sei();

    set_sleep_mode(SLEEP_MODE_ADC);
    sleep_enable();
    while (true) {
        sleep_cpu();
        printf("read: %d\r\n", x);
    }
}
