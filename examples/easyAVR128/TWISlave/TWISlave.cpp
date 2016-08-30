#include <util/delay.h>
#include "Serial.h"
#include "array_view.h"
#include "TWISlave.h"

void hal::TWISlave::callback() {
    printf("callback!: %d\n", TWISlave::rx_buffer_cnt);
    for(int i = 0; i < TWISlave::rx_buffer_cnt; ++i) {
        printf("%d ", TWISlave::rx_buffer[i]);
    }
    printf("\n");
}

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    hal::TWISlave::init(0x1E);

    sei();

    for(int i = 0; i < 10; ++i) {
        hal::TWISlave::tx_buffer[i] = 10+i;
    }
    while (true) {
        _delay_ms(10);
    }
}
