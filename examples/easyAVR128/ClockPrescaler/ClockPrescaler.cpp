#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        hal::sleep_for(100ms);
    }

    hal::cpu::set_clock_divider<10>();

    for (int i = 0; i < 10; ++i) {
        printf("X\r\n");
        hal::sleep_for(100ms);
    }
}
