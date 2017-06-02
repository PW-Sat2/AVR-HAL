#include <hal/hal>

using hal::Serial0;

#ifdef USART0_RX_vect
ISR(USART0_RX_vect) {
#else
ISR(USART_RX_vect) {
#endif
    hal::Serial0.printf("got: %d\r\n", hal::Serial0.read_byte_nowait());
}

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();
    hal::Serial0.enable_rx_interrupt();

    sei();

    while (true) {
    }
}
