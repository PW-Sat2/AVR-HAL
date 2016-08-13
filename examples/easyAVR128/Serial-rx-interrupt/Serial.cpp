#include "Serial.h"

ISR(USART0_RX_vect) {
    hal::Serial0.printf("got: %d\r\n", hal::Serial0.read_byte_nowait());
}

int main() {
    hal::Serial0.init(9600);
    hal::Serial0.enable_rx_interrupt();

    sei();

    while (true) {
    }
}
