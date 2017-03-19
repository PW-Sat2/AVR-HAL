#ifndef HAL_PERIPH_ANALOG_ANALOG_H_
#define HAL_PERIPH_ANALOG_ANALOG_H_

#include <avr/io.h>
#include "bit_operations.h"
#include "mcu.h"

namespace hal {

class InternalADC : public mcu::InternalADCMcuSpecific {
 public:
    InternalADC() = delete;

    enum class Reference : uint8_t {
        AREF = 0,
        AVcc = 1,
        Internal_1V1 = 2,
        Internal_2V56 = 3
    };

    enum class Prescaler : uint16_t {
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
        libs::write_mask<0, 3>(ADCSRA, prescaler);
    }

    static void set_reference(Reference reference) {
        libs::write_mask<6, 2>(ADMUX, reference);
    }

    static void disable() {
        libs::clear_bit(ADCSRA, ADEN);
    }

    static void enable() {
        libs::set_bit(ADCSRA, ADEN);
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
#ifdef MUX5
        libs::write_mask<MUX5, 1>(ADCSRB, libs::read_bit(static_cast<uint8_t>(input), 5));
#endif

#ifdef MUX4
        libs::write_mask<0, 5>(ADMUX, input);
#else
        libs::write_mask<0, 4>(ADMUX, input);
#endif
    }

#ifdef ADFR
    enum class TriggerSource : uint8_t {
        FreeRunning = 0,
        Disable = 1,
    };

    static void set_trigger(const TriggerSource trigger) {
        if (trigger == TriggerSource::FreeRunning) {
            libs::set_bit(ADCSRA, ADFR);
        } else {
            libs::clear_bit(ADCSRA, ADFR);
        }
    }
#endif

#ifdef ADATE
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
            libs::write_mask<0, 3>(ADCSRB, trigger);
            libs::set_bit(ADCSRA, ADATE);
        }
    }
#endif
};

class AnalogGPIO {
 public:
    explicit constexpr AnalogGPIO(InternalADC::Input pin) :
        pin{pin} {
    }

    uint16_t read() const {
        InternalADC::select_channel(pin);
        return InternalADC::read();
    }

    uint16_t read_nowait() const {
        return InternalADC::read_nowait();
    }

    void select() const {
        InternalADC::select_channel(pin);
    }

 private:
    const InternalADC::Input pin;
};

}  // namespace hal

#endif  // HAL_PERIPH_ANALOG_ANALOG_H_
