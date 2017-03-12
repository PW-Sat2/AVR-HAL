#ifndef HAL_PERIPH_WATCHDOG_H_
#define HAL_PERIPH_WATCHDOG_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include "bit_operations.h"

namespace hal {

class Watchdog {
 public:
    enum class Period : int {
        p15ms   = 0,
        p30ms   = 1,
        p60ms   = 2,
        p120ms  = 3,
        p250ms  = 4,
        p500ms  = 5,
        p1000ms = 6,
        p2000ms = 7,
#ifdef WDTO_4S
        p4000ms = 8,
#endif
#ifdef WDTO_8S
        p8000ms = 9
#endif
    };

    static void kick() __attribute__((always_inline)) {
        wdt_reset();
    }

    static void enable(Period period) {
        wdt_enable(static_cast<int>(period));
    }

    static void disable() {
        kick();
#ifdef MCUSR
        libs::clear_bit<WDRF>(MCUSR);
#elif defined(MCUCSR)
        libs::clear_bit<WDRF>(MCUCSR);
#else
    #error "Investigate watchdog!"
#endif

        wdt_disable();
    }
};


}  // namespace hal

#endif  // HAL_PERIPH_WATCHDOG_H_
