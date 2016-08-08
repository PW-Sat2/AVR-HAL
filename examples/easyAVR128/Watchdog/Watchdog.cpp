#include "Watchdog.h"
#include "Serial.h"

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    printf("reset\r\n");

    hal::Watchdog::enable(hal::Watchdog::Period::p_1000ms);
    hal::Watchdog::reset();

    while (true) {
    }
}
