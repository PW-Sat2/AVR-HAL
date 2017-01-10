#ifndef HAL_PERIPH_ANALOG_H_
#define HAL_PERIPH_ANALOG_H_

#include <avr/io.h>
#include "bit_operations.h"
#include "mcu.h"

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

    static void disable() {
        clear_bit(ADCSRA, ADEN);
    }

    static void enable() {
        set_bit(ADCSRA, ADEN);
    }

    static uint16_t read() {
        trigger_conversion();
        wait_for_conversion_finish();
        return read_nowait();
    }

    static uint16_t read_nowait() {
        return ADC;
    }

    static void trigger_conversion() {
        set_bit(ADCSRA, ADSC);
    }

    static void wait_for_conversion_finish() {
        while (!conversion_finished()) {
        }
    }

    static bool conversion_finished() {
        return !read_bit(ADCSRA, ADSC);
    }

    static void enable_interrupt() {
        set_bit(ADCSRA, ADIE);
    }

    static void disable_interrupt() {
        clear_bit(ADCSRA, ADIE);
    }

    static void select_channel(Input input) {
        mcu::InternalADCMux::select(input);
    }
};

class AnalogGPIO {
 public:
    explicit constexpr AnalogGPIO(InternalADC::Input pin) :
        pin{pin} {
    }

    uint16_t read() const {
        mcu::InternalADCMux::select(pin);
        return InternalADC::read();
    }

    uint16_t read_nowait() const {
        return InternalADC::read_nowait();
    }

    void select() const {
        mcu::InternalADCMux::select(pin);
    }

 private:
    const InternalADC::Input pin;
};

}  // namespace hal

#endif  // HAL_PERIPH_ANALOG_H_
