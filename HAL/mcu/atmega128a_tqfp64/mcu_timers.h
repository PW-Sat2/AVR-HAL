#ifndef HAL_MCU_ATMEGA128A_TQFP64_MCU_TIMERS_H_
#define HAL_MCU_ATMEGA128A_TQFP64_MCU_TIMERS_H_

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

    enum class Mode : uint8_t {
        normal = 0,
        PWM_phase_correct = 1,
        CTC = 2,
        FastPWM = 3
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR0 = (static_cast<uint8_t>(mode) & 0b01 << WGM00) |
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

class Timer1 {
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

    enum class Mode : uint8_t {
        normal = 0,
        PWM_phase_correct_8b = 1,
        PWM_phase_correct_9b = 2,
        PWM_phase_correct_10b = 3,
        CTC_OCRnA_TOP = 4,
        FastPWM_8b = 5,
        FastPWM_9b = 6,
        FastPWM_10b = 7,
        PWM_phase_and_frequency_correct_ICRn_TOP = 8,
        PWM_phase_and_frequency_correct_OCRnA_TOP = 9,
        PWM_phase_correct_ICRn_TOP = 10,
        PWM_phase_correct_OCRnA_TOP = 11,
        CTC_ICRn_TOP = 12,
        FastPWM_ICRn_TOP = 14,
        FastPWM_OCRnA_TOP = 15
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR1A = (static_cast<uint8_t>(mode) & 0b0011);
        TCCR1B = (static_cast<uint8_t>(mode) & 0b1100 << 1) |
                  static_cast<uint8_t>(prescaler);
    }

    static void set_output_compare_A(uint16_t value) {
        OCR1A = value;
    }

    static void set_output_compare_B(uint16_t value) {
        OCR1B = value;
    }

    static void set_output_compare_C(uint16_t value) {
        OCR1C = value;
    }

    static void enable_overflow_interrupt() {
        SBI(TIMSK, TOIE1);
    }

    static void enable_compare_A_interrupt() {
        SBI(TIMSK, OCIE1A);
    }

    static void enable_compare_B_interrupt() {
        SBI(TIMSK, OCIE1B);
    }

    static void enable_compare_C_interrupt() {
        SBI(ETIMSK, OCIE1C);
    }
};

class Timer3 {
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

    enum class Mode : uint8_t {
        normal = 0,
        PWM_phase_correct_8b = 1,
        PWM_phase_correct_9b = 2,
        PWM_phase_correct_10b = 3,
        CTC_OCRnA_TOP = 4,
        FastPWM_8b = 5,
        FastPWM_9b = 6,
        FastPWM_10b = 7,
        PWM_phase_and_frequency_correct_ICRn_TOP = 8,
        PWM_phase_and_frequency_correct_OCRnA_TOP = 9,
        PWM_phase_correct_ICRn_TOP = 10,
        PWM_phase_correct_OCRnA_TOP = 11,
        CTC_ICRn_TOP = 12,
        FastPWM_ICRn_TOP = 14,
        FastPWM_OCRnA_TOP = 15
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR3A = (static_cast<uint8_t>(mode) & 0b0011);
        TCCR3B = (static_cast<uint8_t>(mode) & 0b1100 << 1) |
                  static_cast<uint8_t>(prescaler);
    }

    static void set_output_compare_A(uint16_t value) {
        OCR3A = value;
    }

    static void set_output_compare_B(uint16_t value) {
        OCR3B = value;
    }

    static void set_output_compare_C(uint16_t value) {
        OCR3C = value;
    }

    static void enable_overflow_interrupt() {
        SBI(ETIMSK, TOIE3);
    }

    static void enable_compare_A_interrupt() {
        SBI(ETIMSK, OCIE3A);
    }

    static void enable_compare_B_interrupt() {
        SBI(ETIMSK, OCIE3B);
    }

    static void enable_compare_C_interrupt() {
        SBI(ETIMSK, OCIE3C);
    }
};

class Timer2 {
 public:
    enum class Prescaler : uint8_t {
        No_Clock = 0,
        DIV_1 = 1,
        DIV_8 = 2,
        DIV_64 = 3,
        DIV_256 = 4,
        DIV_1024 = 5,
        EXT_T2_falling = 6,
        EXT_T2_rising = 7
    };

    enum class Mode : uint8_t {
        normal = 0,
        PWM_phase_correct = 1,
        CTC = 2,
        FastPWM = 3
    };

    static void init(Prescaler prescaler, Mode mode) {
        TCCR2 = (static_cast<uint8_t>(mode) & 0b01 << WGM20) |
                (static_cast<uint8_t>(mode) & 0b10 << WGM21) |
                 static_cast<uint8_t>(prescaler);
    }

    static void set_output_compare(uint8_t value) {
        OCR2 = value;
    }

    static void enable_overflow_interrupt() {
        SBI(TIMSK, TOIE2);
    }

    static void enable_compare_interrupt() {
        SBI(TIMSK, OCIE2);
    }
};

}  // namespace hal

#endif  // HAL_MCU_ATMEGA128A_TQFP64_MCU_TIMERS_H_
