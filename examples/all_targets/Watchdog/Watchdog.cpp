#include <hal/hal>

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    printf("reset\r\n");

    hal::Watchdog::enable(hal::Watchdog::Period::p1000ms);
    hal::Watchdog::kick();

    while (true) {
    }
}
