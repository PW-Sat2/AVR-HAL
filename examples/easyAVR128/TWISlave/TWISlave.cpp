#include <util/delay.h>
#include "Serial.h"
#include "array_view.h"
#include "TWISlave.h"

void callback(hal::libs::array_view<uint8_t> && arr) {
    printf("callback!: %d\n", arr.size());
    for(auto x : arr) {
        printf("%d ", x);
    }
    printf("\n");
}

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    hal::TWISlave::init(0x1E, callback);

    sei();

    for(int i = 0; i < 10; ++i) {
        hal::TWISlave::tx_buffer[i] = 10+i;
    }
    while (true) {
        _delay_ms(10);
    }
}
