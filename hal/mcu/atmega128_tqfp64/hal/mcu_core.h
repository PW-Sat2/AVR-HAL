#ifndef HAL_MCU_ATMEGA128A_TQFP64_HAL_MCU_CORE_H_
#define HAL_MCU_ATMEGA128A_TQFP64_HAL_MCU_CORE_H_

namespace hal {
namespace cpu {

#include <avr/io.h>
#include "hal/libs.h"

enum class SleepModes : uint8_t {
    Idle = 0,
    ADC_Noise_Reduction = 2,
    Power_Down = 4,
    Power_Save = 6,
    Standby = 5,
    Extended_Standby = 7
};

inline void set_sleep_mode(SleepModes mode) {
    MCUCR &= 0b11000011;
    MCUCR |= (static_cast<uint8_t>(mode) << 2);
}

inline void sleep_enable() {
    libs::set_bit(MCUCR, SE);
}

inline void sleep_disable() {
    libs::clear_bit(MCUCR, SE);
}

inline void sleep_cpu() {
    __asm__ __volatile__("sleep" "\n\t" ::);
}

template<int divisor>
inline void set_clock_divider() {
    XDIV = 0;
    static_assert((divisor >= 1) && (divisor <= 129), "Clock divisor can be in rage 1..129!");
    if (divisor > 1) {
        XDIV = 129-divisor;
        libs::set_bit(XDIV, 7);
    }
}

}  // namespace cpu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA128A_TQFP64_HAL_MCU_CORE_H_
