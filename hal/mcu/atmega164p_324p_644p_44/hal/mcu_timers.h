#ifndef HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_TIMERS_H_
#define HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_TIMERS_H_

#include <avr/io.h>
#include "hal/libs.h"

namespace hal {
namespace mcu {

class Timer0 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock   = 0,
        DIV_1      = 1,
        DIV_8      = 2,
        DIV_64     = 3,
        DIV_256    = 4,
        DIV_1024   = 5,
        T0_falling = 6,
        T0_rising  = 7,
    };

    enum class Mode : uint8_t {
        Normal                     = 0,
        PWM_phase_correct_top_0xFF = 1,
        CTC                        = 2,
        FastPWM                    = 3,
        PWM_phase_correct_top_OCRA = 5,
        FastPWM_top_OCRA           = 7,
    };

    static void init(Mode mode, Prescaler prescaler) {
        TCCR0A = static_cast<uint8_t>(mode) & 0b11;

        TCCR0B = static_cast<uint8_t>(prescaler) |
                 (hal::libs::read_bit<2>(static_cast<uint8_t>(mode)) << WGM02);
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

class Timer1 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock   = 0,
        DIV_1      = 1,
        DIV_8      = 2,
        DIV_64     = 3,
        DIV_256    = 4,
        DIV_1024   = 5,
        T1_FALLING = 6,
        T1_RISING  = 7,
    };

    enum class Mode : uint8_t {
        Normal                                    = 0,
        PWM_phase_correct_8b                      = 1,
        PWM_phase_correct_9b                      = 2,
        PWM_phase_correct_10b                     = 3,
        CTC_OCRnA_TOP                             = 4,
        FastPWM_8b                                = 5,
        FastPWM_9b                                = 6,
        FastPWM_10b                               = 7,
        PWM_phase_and_frequency_correct_ICRn_TOP  = 8,
        PWM_phase_and_frequency_correct_OCRnA_TOP = 9,
        PWM_phase_correct_ICRn_TOP                = 10,
        PWM_phase_correct_OCRnA_TOP               = 11,
        CTC_ICRn_TOP                              = 12,
        FastPWM_ICRn_TOP                          = 14,
        FastPWM_OCRnA_TOP                         = 15
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR1A = num(mode) & 0b0011;
        TCCR1B = ((num(mode) & 0b1100) << 1) | num(prescaler);
    }

    static void set_output_compare_A(uint16_t value) {
        OCR1A = value;
    }

    static void set_output_compare_B(uint16_t value) {
        OCR1B = value;
    }

    static void enable_overflow_interrupt() {
        libs::set_bit(TIMSK1, TOIE1);
    }

    static void enable_compare_A_interrupt() {
        libs::set_bit(TIMSK1, OCIE1A);
    }

    static void enable_compare_B_interrupt() {
        libs::set_bit(TIMSK1, OCIE1B);
    }
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_TIMERS_H_
