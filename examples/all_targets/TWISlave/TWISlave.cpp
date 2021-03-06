#include <hal/hal>

using namespace std::chrono_literals;

void hal::TWISlave::callbackRx() {
    printf("callbackRx!: %d\n", TWISlave::rx_buffer_cnt);
    for (int i = 0; i < TWISlave::rx_buffer_cnt; ++i) {
        printf("%d ", TWISlave::rx_buffer[i]);
    }
    printf("\n");
}

void hal::TWISlave::callbackTx() {
    printf("callbackTx!");
}

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();
    hal::TWISlave::init(0x1E);

    sei();

    for (int i = 0; i < 10; ++i) {
        hal::TWISlave::tx_buffer[i] = 10 + i;
    }
    while (true) {
        hal::sleep_for(10ms);
    }
}
