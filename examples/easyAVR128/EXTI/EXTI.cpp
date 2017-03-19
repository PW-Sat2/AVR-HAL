#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "EXTI.h"
#include "Serial.h"

ISR(INT0_vect) {
    printf("a");
    _delay_ms(10);
}

ISR(INT1_vect) {
    printf("b");
    _delay_ms(10);
}

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);
    printf("INIT!\r\n");

    constexpr hal::ExternalInterrupt line(0, hal::ExternalInterrupt::Mode::rising);
    constexpr hal::ExternalInterrupt line2(1, hal::ExternalInterrupt::Mode::rising);
    line.enable();
    line2.enable();

    sei();

    hal::cpu::set_sleep_mode(hal::cpu::SleepModes::Idle);
    hal::cpu::sleep_enable();

    while (true) {
        hal::cpu::sleep_cpu();
    }
}
