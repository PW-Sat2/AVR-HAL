#ifndef HAL_MCU_AT90CAN128_TQFP64_MCU_CORE_H_
#define HAL_MCU_AT90CAN128_TQFP64_MCU_CORE_H_

namespace hal {
namespace cpu {

#include <avr/io.h>
#include "bit_operations.h"

enum class SleepModes : uint8_t {
    Idle = 0,
    ADC_Noise_Reduction = 1,
    Power_Down = 2,
    Power_Save = 3,
    Standby = 6
};

inline void set_sleep_mode(SleepModes mode) {
    SMCR = (static_cast<uint8_t>(mode) << 1);
}

inline void sleep_enable() {
    set_bit(SMCR, SE);
}

inline void sleep_disable() {
    clear_bit(SMCR, SE);
}

inline void sleep_cpu() {
    __asm__ __volatile__("sleep" "\n\t" ::);
}

}  // namespace cpu
}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_MCU_CORE_H_