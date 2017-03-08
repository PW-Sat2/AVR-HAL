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
        DIV_32 = 3,
        DIV_64 = 4,
        DIV_128 = 5,
        DIV_256 = 6,
        DIV_1024 = 7
    };

    static void init(Prescaler prescaler) {
        TCCR0 = static_cast<uint8_t>(prescaler);
    }

    static void enable_overflow_interrupt() {
        set_bit(TIMSK, TOIE0);
    }

    static void set_output_compare(uint8_t value) {
        OCR0 = value;
    }

    static void enable_compare_interrupt() {
        set_bit(TIMSK, OCIE0);
    }
};

}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_MCU_TIMERS_H_
