#ifndef HAL_PERIPH_ANALOG_H_
#define HAL_PERIPH_ANALOG_H_

#include <stdio.h>
#include <avr/io.h>
#include "bit_operations.h"
#include "mcu.h"
#include "boards.h"

namespace hal {

class InternalADC : public mcu::InternalADCMcuSpecific {
 public:
    InternalADC() = delete;

    enum class Prescaler : uint8_t {
        DIV_2 = 0,
        DIV_4 = 2,
        DIV_8 = 3,
        DIV_16 = 4,
        DIV_32 = 5,
        DIV_64 = 6,
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

    static void trigger_conversion() {
        SBI(ADCSRA, ADSC);
    }

    static void disable() {
        CBI(ADCSRA, ADEN);
    }

    static void enable() {
        SBI(ADCSRA, ADEN);
    }

    static uint16_t read() {
        trigger_conversion();
        while (RBI(ADCSRA, ADSC)) {
        }
        return ADC;
    }

    static void enable_interrupt() {
        SBI(ADCSRA, ADIE);
    }

    static void set_channel(Input input) {
        mcu::InternalADCMux::set(input);
    }
};

class AnalogGPIO {
 public:
    explicit constexpr AnalogGPIO(InternalADC::Input input) :
        pin_mode_mem{input} {
    }

    uint16_t read() const {
        mcu::InternalADCMux::set(pin_mode_mem);
        return InternalADC::read();
    }

    void set() const {
        mcu::InternalADCMux::set(pin_mode_mem);
    }

    uint16_t read_nowait() const {
        return InternalADC::read();
    }

 private:
    const InternalADC::Input pin_mode_mem;
};

}  // namespace hal

#endif  // HAL_PERIPH_ANALOG_H_
