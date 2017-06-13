#include <hal/hal>

using kick_pin1 = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;
hal::devices::TPS3813::TPS3813<kick_pin1, 10> WDT_1;

int main() {
    WDT_1.init();

    using kick_pin2 = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    auto WDT_2      = hal::devices::TPS3813::TPS3813<kick_pin2, 5>();
    WDT_2.init();

    while (true) {
        WDT_1.kick();
        WDT_2.kick();
        _delay_ms(1000);
    }
}
