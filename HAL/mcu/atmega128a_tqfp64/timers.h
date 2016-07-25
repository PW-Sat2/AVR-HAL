#ifndef HAL_MCU_ATMEGA128A_TQFP64_TIMERS_H_
#define HAL_MCU_ATMEGA128A_TQFP64_TIMERS_H_

namespace hal {

#include <avr/interrupt.h>
#include <avr/io.h>
#include "bit_operations.h"

class Timer0 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock = 0,
        DIV_1 = 1,
        DIV_8 = 2,
        DIV_32 = 3,
        DIV_64 = 4,
        DIV_128 = 5,
        DIV_256 = 6,
        DIV_1024 = 7
    };

    static void init(Prescaler prescaler) {
        TCCR0 |= static_cast<uint8_t>(prescaler);
    }

    enum class Mode : uint8_t {
        normal = 0,
        PWM_phase_correct = 1,
        CTC = 2,
        FastPWM = 3
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR0 |= (static_cast<uint8_t>(mode) & 0b01 << WGM00) |
                 (static_cast<uint8_t>(mode) & 0b10 << WGM01) |
                  static_cast<uint8_t>(prescaler);
    }

    static void set_output_compare(uint8_t value) {
        OCR0 = value;
    }

    static void enable_overflow_interrupt() {
        SBI(TIMSK, TOIE0);
    }

    static void enable_compare_interrupt() {
        SBI(TIMSK, OCIE0);
    }
};

}  // namespace hal

#endif /* HAL_MCU_ATMEGA128A_TQFP64_TIMERS_H_ */
