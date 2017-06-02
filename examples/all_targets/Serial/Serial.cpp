#include <hal/hal>

using hal::Serial0;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stderr();

    while (true) {
        static int counter = 0;
        hal::Serial0.printf("Counter value = %d\r\n", counter++);

        _delay_ms(200);
    }
}
