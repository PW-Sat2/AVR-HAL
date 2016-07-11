#include <util/delay.h>
#include "config.h"
#include "devices/FPF270x.hpp"

int main() {
    hal::FPF270x LCLTest(hal::bsp::D1, hal::bsp::D2, hal::bsp::D3);
    LCLTest.init();

    while (1) {
        LCLTest.on();
        _delay_ms(200);
        
        bool pwr_good = LCLTest.powerGood();
        bool error_event = LCLTest.errorOccured();
        
        LCLTest.off();
        _delay_ms(200);
    }
}
