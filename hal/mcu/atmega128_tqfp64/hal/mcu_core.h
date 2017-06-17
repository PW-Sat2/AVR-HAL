#ifndef HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_CORE_H_
#define HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_CORE_H_

#include <avr/io.h>
#include "hal/libs.h"

namespace hal {
namespace cpu {

template<int divisor>
inline void set_clock_divider() {
    XDIV = 0;
    static_assert((divisor >= 1) && (divisor <= 129),
                  "Clock divisor can be in rage 1..129!");
    if (divisor > 1) {
        XDIV = 129 - divisor;
        libs::set_bit(XDIV, 7);
    }
}

}  // namespace cpu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA128_TQFP64_HAL_MCU_CORE_H_
