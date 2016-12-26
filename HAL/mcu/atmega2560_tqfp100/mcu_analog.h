#ifndef HAL_MCU_ATMEGA2560_TQFP100_MCU_ANALOG_H_
#define HAL_MCU_ATMEGA2560_TQFP100_MCU_ANALOG_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_operations.h"

namespace hal {
namespace mcu {

class InternalADCMcuSpecific {
 public:
    InternalADCMcuSpecific() = delete;

    enum class Reference : uint8_t {
        AREF = 0,
        AVcc = 1,
        Internal_1V1 = 2,
        Internal_2V56 = 3
    };

    enum class Input : uint8_t {
        ADC0 = 0,
        ADC1 = 1,
        ADC2 = 2,
        ADC3 = 3,
        ADC4 = 4,
        ADC5 = 5,
        ADC6 = 6,
        ADC7 = 7,
        ADC00_Gain10 = 8,
        ADC10_Gain10 = 9,
        ADC00_Gain200 = 10,
        ADC10_Gain200 = 11,
        ADC22_Gain10 = 12,
        ADC32_Gain10 = 13,
        ADC22_Gain200 = 14,
        ADC32_Gain200 = 15,
        ADC01_Gain1 = 16,
        ADC11_Gain1 = 17,
        ADC21_Gain1 = 18,
        ADC31_Gain1 = 19,
        ADC41_Gain1 = 20,
        ADC51_Gain1 = 21,
        ADC61_Gain1 = 22,
        ADC71_Gain1 = 23,
        ADC02_Gain1 = 24,
        ADC12_Gain1 = 25,
        ADC22_Gain1 = 26,
        ADC32_Gain1 = 27,
        ADC42_Gain1 = 28,
        ADC52_Gain1 = 29,
        REF1V1 = 30,
        GND = 31,
        ADC8 = 32,
        ADC9 = 33,
        ADC10 = 34,
        ADC11 = 35,
        ADC12 = 36,
        ADC13 = 37,
        ADC14 = 38,
        ADC15 = 39,
        ADC88_Gain10 = 40,
        ADC98_Gain10 = 41,
        ADC88_Gain200 = 42,
        ADC98_Gain200 = 43,
        ADC10_10_Gain10 = 44,
        ADC11_10_Gain10 = 45,
        ADC10_10_Gain200 = 46,
        ADC11_10_Gain200 = 47,
        ADC8_9_Gain1 = 48,
        ADC9_9_Gain1 = 49,
        ADC10_9_Gain1 = 50,
        ADC11_9_Gain1 = 51,
        ADC12_9_Gain1 = 52,
        ADC13_9_Gain1 = 53,
        ADC14_9_Gain1 = 54,
        ADC15_9_Gain1 = 55,
        ADC8_10_Gain1 = 56,
        ADC9_10_Gain1 = 57,
        ADC10_10_Gain1 = 58,
        ADC11_10_Gain1 = 59,
        ADC12_10_Gain1 = 60,
        ADC13_10_Gain1 = 61
    };

    template<Input input>
    static void disable_digital() {
        static_assert((input <= Input::ADC7) &&
                      (input >= Input::ADC8) &&
                      (input <= Input::ADC15),
                      "Disabling digital buffer allowed only on ADC0..15");
        if (input <= Input::ADC7) {
            DIDR0 |= (1 << static_cast<uint8_t>(input));
        } else {
            DIDR2 |= (1 << (static_cast<uint8_t>(input)-32));
        }
    }

    enum class TriggerSource : uint8_t {
        Disable = 8,
        FreeRunning = 0,
        AnalogComparator = 1,
        ExternalInterrupt_0 = 2,
        Timer_0_compare_A = 3,
        Timer_0_overflow = 4,
        Timer_1_compare_B = 5,
        Timer_1_overflow = 6,
        Timer_1_capture = 7
    };

    static void set_trigger(const TriggerSource trigger) {
        if (trigger == TriggerSource::Disable) {
            clear_bit(ADCSRA, ADATE);
        } else {
            ADCSRB = static_cast<uint8_t>(trigger);
            set_bit(ADCSRA, ADATE);
        }
    }
};

class InternalADCMux {
 public:
    InternalADCMux() = delete;

    static void select(const InternalADCMcuSpecific::Input input) {
        ADMUX &= 0b11110000;
        ADMUX |= get_last_4_bits(input);
        ADCSRB &= 0b11110111;
        ADCSRB |= get_5th_bit(input) << 3;
    }

 private:
    constexpr static uint8_t get_last_4_bits(const InternalADCMcuSpecific::Input input) {
        return (static_cast<uint8_t>(input) & 0b1111);
    }
    constexpr static uint8_t get_5th_bit(const InternalADCMcuSpecific::Input input) {
        return ((static_cast<uint8_t>(input) & 0b10000) >> 4);
    }
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA2560_TQFP100_MCU_ANALOG_H_
