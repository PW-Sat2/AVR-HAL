#include <hal/hal>

using hal::Serial0;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();
    printf("reset\r\n");

    hal::Watchdog::enable(hal::Watchdog::Period::p1000ms);
    hal::Watchdog::kick();

    while (true) {
    }
}
