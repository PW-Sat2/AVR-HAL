#include <hal/hal>

hal::DigitalIO::GPIO<hal::mcu::pin_scl> kick_pin1;
hal::TPS3813<10> WDT_1(kick_pin1);

int main() {
    WDT_1.init();

    hal::DigitalIO::GPIO<hal::mcu::pin_sda> kick_pin2;
    auto WDT_2 = hal::TPS3813<5>(kick_pin2);
    WDT_2.init();

    while (true) {
        WDT_1.kick();
        WDT_2.kick();
        _delay_ms(1000);
    }
}
