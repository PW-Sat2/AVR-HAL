#include <avr/io.h>
#include <avr/interrupt.h>
#include "Serial.h"

#ifdef USART0_RX_vect
ISR(USART0_RX_vect) {
#else
ISR(USART_RX_vect) {
#endif
    hal::Serial0.printf("got: %d\r\n", hal::Serial0.read_byte_nowait());
}

int main() {
    hal::Serial0.init(9600);
    hal::Serial0.enable_rx_interrupt();

    sei();

    while (true) {
    }
}
