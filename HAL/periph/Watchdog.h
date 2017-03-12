#ifndef HAL_PERIPH_WATCHDOG_H_
#define HAL_PERIPH_WATCHDOG_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include "bit_operations.h"

namespace hal {

class Watchdog {
 public:
    enum class Period : int {
        p_15ms = 0,
        p_30ms = 1,
        p_60ms = 2,
        p_120ms = 3,
        p_250ms = 4,
        p_500ms = 5,
        p_1000ms = 6,
        p_2000ms = 7,
#ifdef WDTO_8S
        p_4000ms = 8,
        p_8000ms = 9
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
