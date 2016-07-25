#ifndef HAL_PERIPH_WATCHDOG_H_
#define HAL_PERIPH_WATCHDOG_H_

#include <avr/wdt.h>
#include "mcu.h"

namespace hal {

class Watchdog : public mcu::Watchdog {
 public:
    static void reset() __attribute__((always_inline)) {
        wdt_reset();
    }

    static void enable(Period period) {
        wdt_enable(static_cast<int>(period));
    }

    static void disable() {
        wdt_disable();
    }
};


}  // namespace hal

#endif  // HAL_PERIPH_WATCHDOG_H_
