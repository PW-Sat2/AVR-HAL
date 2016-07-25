#include "Serial.h"

ISR(USART0_RX_vect) {
    printf("got: %d\r\n", UDR0);
}

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    hal::Serial0.enable_rx_interrupt();

    sei();

    while (true) {
    }
}
