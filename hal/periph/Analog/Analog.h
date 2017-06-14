#ifndef HAL_PERIPH_ANALOG_ANALOG_H_
#define HAL_PERIPH_ANALOG_ANALOG_H_

#include <avr/io.h>
#include "hal/libs/bit_operations.h"
#include "hal/mcu.h"

namespace hal {
namespace Analog {

class InternalADC : public mcu::InternalADCMcuSpecific, libs::PureStatic {
 public:
    enum class Prescaler : uint8_t {
        DIV_2   = 0,
        DIV_4   = 2,
        DIV_8   = 3,
        DIV_16  = 4,
        DIV_32  = 5,
        DIV_64  = 6,
        DIV_128 = 7
    };

    static void init(Prescaler prescaler, Reference reference) {
        set_prescaler(prescaler);
        set_reference(reference);
        enable();
    }

    static void set_prescaler(Prescaler prescaler) {
        ADCSRA &= 0b11111000;
        ADCSRA |= static_cast<uint8_t>(prescaler);
    }

    static void set_reference(Reference reference) {
        ADMUX &= 0b00111111;
        ADMUX |= (static_cast<uint8_t>(reference) << 6);
    }

    static void disable() {
        libs::clear_bit(ADCSRA, ADEN);
    }

    static void enable() {
        libs::set_bit(ADCSRA, ADEN);
    }

    static uint10_t read() {
        trigger_conversion();
        wait_for_conversion_finish();
        return read_nowait();
    }

    static uint10_t read_nowait() {
        return ADC;
    }

    static void trigger_conversion() {
        libs::set_bit(ADCSRA, ADSC);
    }

    static void wait_for_conversion_finish() {
        while (!conversion_finished()) {
        }
    }

    static bool conversion_finished() {
        return !libs::read_bit(ADCSRA, ADSC);
    }

    static void enable_interrupt() {
        libs::set_bit(ADCSRA, ADIE);
    }

    static void disable_interrupt() {
        libs::clear_bit(ADCSRA, ADIE);
    }

    static void select_channel(Input input) {
        mcu::InternalADCMux::select(input);
    }
};

template<InternalADC::Input pin>
class AnalogGPIO : libs::PureStatic {
 public:
    static uint10_t read() {
        select();
        return InternalADC::read();
    }

    static uint10_t read_nowait() {
        return InternalADC::read_nowait();
    }

    static void select() {
        mcu::InternalADCMux::select(pin);
    }
};

}  // namespace Analog
}  // namespace hal

#endif  // HAL_PERIPH_ANALOG_ANALOG_H_
