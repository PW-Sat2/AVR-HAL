#ifndef HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_TIMERS_H_
#define HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_TIMERS_H_

namespace hal {

#include <avr/io.h>
#include "hal/libs.h"

class Timer0 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock   = 0,
        DIV_1      = 1,
        DIV_8      = 2,
        DIV_32     = 3,
        DIV_256    = 4,
        DIV_1024   = 5,
        T0_falling = 6,
        T0_rising  = 7
    };

    enum class Mode : uint8_t { Normal = 0 };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR0A = (static_cast<uint8_t>(mode) & 0b001 << WGM00) |
                 (static_cast<uint8_t>(mode) & 0b010 << WGM01);
        TCCR0B = (static_cast<uint8_t>(mode) & 0b100 << WGM02) |
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

#endif  // HAL_MCU_ATMEGA328P_TQFP32_HAL_MCU_TIMERS_H_
