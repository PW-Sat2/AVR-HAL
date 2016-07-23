#include "Serial.h"

void handler(uint8_t byte) {
    hal::Serial0.print_byte('x');
//    printf("got: %d\r\n", byte);
}

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    hal::Serial0.enable_rx_interrupt(handler);

    sei();

    while (true) {
    }
}
