#ifndef HAL_MCU_AT90CAN128_TQFP64_MCU_TIMERS_H_
#define HAL_MCU_AT90CAN128_TQFP64_MCU_TIMERS_H_

namespace hal {

#include <avr/io.h>
#include "bit_operations.h"

class Timer0 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock = 0,
        DIV_1 = 1,
        DIV_8 = 2,
        DIV_64 = 3,
        DIV_256 = 4,
        DIV_1024 = 5,
        T0_falling = 6,
        T0_rising = 7
    };

    enum class Mode : uint8_t {
        Normal = 0,
        PWM_phase_correct = 1,
        CTC = 2,
        FastPWM = 3
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR0A = (static_cast<uint8_t>(mode) & 0b01 << WGM00) |
                 (static_cast<uint8_t>(mode) & 0b10 << WGM01) |
                  static_cast<uint8_t>(prescaler);
    }

    static void enable_overflow_interrupt() {
        libs::set_bit(TIMSK0, TOIE0);
    }

    static void set_output_compare(uint8_t value) {
        OCR0A = value;
    }

    static void enable_compare_interrupt() {
        libs::set_bit(TIMSK0, OCIE0A);
    }
};

}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_MCU_TIMERS_H_
