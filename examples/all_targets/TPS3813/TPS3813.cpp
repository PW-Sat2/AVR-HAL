#include <hal/hal>

using namespace std::chrono_literals;

using kick_pin1 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;
using WDT_1     = hal::devices::TPS3813<kick_pin1, 10>;

int main() {
    WDT_1::init();

    using kick_pin2 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    using WDT_2     = hal::devices::TPS3813<kick_pin2, 5>;
    WDT_2::init();

    while (true) {
        WDT_1::kick();
        WDT_2::kick();
        hal::sleep_for(1000ms);
    }
}
