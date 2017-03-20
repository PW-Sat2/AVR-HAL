#ifndef HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_ANALOG_H_
#define HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_ANALOG_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal/libs.h"

namespace hal {
namespace mcu {

class InternalADCMcuSpecific {
 public:
    InternalADCMcuSpecific() = delete;

    enum class Reference : uint8_t {
        AREF = 0,
        AVcc = 1,
        Internal_1V1 = 3
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
        TempSensor = 8,
        REF1V1 = 14,
        REFGND = 15
    };

    template<Input input>
    static void disable_digital() {
        static_assert(input < Input::ADC6, "Disabling digital buffer allowed only on ADC0..8");
        DIDR0 |= (1 << static_cast<uint8_t>(input));
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
        ADMUX &= 0b11110000;
        ADMUX |= static_cast<uint8_t>(input);
    }
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA164P_324P_644P_44_HAL_MCU_ANALOG_H_
