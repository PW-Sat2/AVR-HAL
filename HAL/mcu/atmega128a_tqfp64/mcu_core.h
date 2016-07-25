#ifndef HAL_MCU_ATMEGA128A_TQFP64_MCU_CORE_H_
#define HAL_MCU_ATMEGA128A_TQFP64_MCU_CORE_H_

namespace hal {
namespace cpu {

#include <avr/io.h>
#include "bit_operations.h"

enum class SleepModes : uint8_t {
    Idle = 0,
    ADC_Noise_Reduction = 2,
    Power_Down = 4,
    Power_Save = 6,
    Standby = 5,
    Extended_Standby = 7
};

void set_sleep_mode(SleepModes mode) {
    MCUCR &= 0b11000011;
    MCUCR |= (static_cast<uint8_t>(mode) << 2);
}

void sleep_enable() {
    SBI(MCUCR, SE);
}

void sleep_disable() {
    CBI(MCUCR, SE);
}

void sleep_cpu() {
    __asm__ __volatile__("sleep" "\n\t" ::);
}

}  // namespace cpu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA128A_TQFP64_MCU_CORE_H_
