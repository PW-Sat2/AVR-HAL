#include <hal/hal>

constexpr hal::TPS3813 WDT_1(hal::mcu::pin_scl, 10);

int main() {
    WDT_1.init();

    constexpr auto WDT_2 = hal::TPS3813(hal::mcu::pin_sda, 10);
    WDT_2.init();

    while (true) {
        WDT_1.kick();
        WDT_2.kick();
        _delay_ms(1000);
    }
}
