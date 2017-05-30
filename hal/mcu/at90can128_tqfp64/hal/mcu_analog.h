#ifndef HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_ANALOG_H_
#define HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_ANALOG_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include "hal/libs.h"

namespace hal {
namespace mcu {

class InternalADCMcuSpecific {
 public:
    InternalADCMcuSpecific() = delete;

    enum class Reference : uint8_t { AREF = 0, AVcc = 1, Internal_2V56 = 3 };
    enum class Input : uint8_t {
        ADC0          = 0,
        ADC1          = 1,
        ADC2          = 2,
        ADC3          = 3,
        ADC4          = 4,
        ADC5          = 5,
        ADC6          = 6,
        ADC7          = 7,
        ADC00_Gain10  = 8,
        ADC10_Gain10  = 9,
        ADC00_Gain200 = 10,
        ADC10_Gain200 = 11,
        ADC22_Gain10  = 12,
        ADC32_Gain10  = 13,
        ADC22_Gain200 = 14,
        ADC32_Gain200 = 15,
        ADC01_Gain1   = 16,
        ADC11_Gain1   = 17,
        ADC21_Gain1   = 18,
        ADC31_Gain1   = 19,
        ADC41_Gain1   = 20,
        ADC51_Gain1   = 21,
        ADC61_Gain1   = 22,
        ADC71_Gain1   = 23,
        ADC02_Gain1   = 24,
        ADC12_Gain1   = 25,
        ADC22_Gain1   = 26,
        ADC32_Gain1   = 27,
        ADC42_Gain1   = 28,
        ADC52_Gain1   = 29,
        REF1V1        = 30,
        GND           = 31
    };

    enum class TriggerSource : uint8_t {
        Disable             = 8,
        FreeRunning         = 0,
        AnalogComparator    = 1,
        ExternalInterrupt_0 = 2,
        Timer_0_compare_A   = 3,
        Timer_0_overflow    = 4,
        Timer_1_compare_B   = 5,
        Timer_1_overflow    = 6,
        Timer_1_capture     = 7
    };

    static void set_trigger(const TriggerSource trigger) {
        if (trigger == TriggerSource::Disable) {
            libs::clear_bit(ADCSRA, ADATE);
        } else {
            ADCSRB = static_cast<uint8_t>(trigger);
            libs::set_bit(ADCSRA, ADATE);
        }
    }
};

class InternalADCMux {
 public:
    InternalADCMux() = delete;

    static void select(InternalADCMcuSpecific::Input input) {
        ADMUX &= 0b11100000;
        ADMUX |= static_cast<uint8_t>(input);
    }
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_ANALOG_H_
