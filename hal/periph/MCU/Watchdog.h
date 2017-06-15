#ifndef HAL_PERIPH_MCU_WATCHDOG_H_
#define HAL_PERIPH_MCU_WATCHDOG_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include "hal/libs.h"

namespace hal {

class Watchdog : libs::PureStatic {
 public:
    Watchdog() = delete;

    enum class Period : uint8_t {
        p15ms   = WDTO_15MS,
        p30ms   = WDTO_30MS,
        p60ms   = WDTO_60MS,
        p120ms  = WDTO_120MS,
        p250ms  = WDTO_250MS,
        p500ms  = WDTO_500MS,
        p1000ms = WDTO_1S,
        p2000ms = WDTO_2S,
#ifdef WDTO_4S
        p4000ms = WDTO_4S,
#endif
#ifdef WDTO_8S
        p8000ms = WDTO_8S
#endif
    };

    static void kick() __attribute__((always_inline)) {
        wdt_reset();
    }

    static void enable(Period period) {
        wdt_enable(static_cast<uint8_t>(period));
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

#endif  // HAL_PERIPH_MCU_WATCHDOG_H_
