#ifndef HAL_PERIPH_GPIO_DIGITALIO_H_
#define HAL_PERIPH_GPIO_DIGITALIO_H_

#include "hal/periph/GPIO/PeriphDescriptors.h"

#include "hal/libs.h"
#include "hal/mcu.h"

namespace hal {

// hack for checking bad pin association
extern int DigitalIO_bad_pin_or_cannot_be_evaluated_at_compiletime;

class DigitalIO {
 public:
    using Pin = uint8_t;

    enum Mode {
        INPUT, OUTPUT, INPUT_PULLUP
    };

    constexpr explicit DigitalIO(Pin pin) :
            pin(mcu::DigitalIOPinMap[pin].pin), DDRx(
                    (mcu::DigitalIOPinMap[pin].DDRx == 0) ?
                            DigitalIO_bad_pin_or_cannot_be_evaluated_at_compiletime :
                            mcu::DigitalIOPinMap[pin].DDRx), PORTx(
                    mcu::DigitalIOPinMap[pin].PORTx), PINx(
                    mcu::DigitalIOPinMap[pin].PINx) {
    }
    enum class RUNTIME {
        ENABLED
    };
    constexpr explicit DigitalIO(Pin pin, __attribute__((unused)) RUNTIME) :
            pin(mcu::DigitalIOPinMap[pin].pin),
            DDRx(mcu::DigitalIOPinMap[pin].DDRx),
            PORTx(mcu::DigitalIOPinMap[pin].PORTx),
            PINx(mcu::DigitalIOPinMap[pin].PINx) {
    }

    void init(const DigitalIO::Mode mode) const __attribute__((always_inline)) {
        pinmode(mode);
    }

    void set() const __attribute__((always_inline)) {
        set_bit_dio(PORTx);
    }

    void reset() const __attribute__((always_inline)) {
        clear_bit_dio(PORTx);
    }

    void write(bool value) const __attribute__((always_inline)) {
        if (value) {
            this->set();
        } else {
            this->reset();
        }
    }

    bool read() const __attribute__((always_inline)) {
        return libs::read_bit(*((volatile uint8_t *)(PINx)), pin);
    }

    void toggle() const __attribute__((always_inline)) {
        if (read()) {
            reset();
        } else {
            set();
        }
    }

    inline void pinmode(const DigitalIO::Mode mode) const
            __attribute__((always_inline)) {
        switch (mode) {
        case OUTPUT:
            set_bit_dio(DDRx);
//            clear_bit_dio(PORTx);
            break;
        case INPUT_PULLUP:
            clear_bit_dio(DDRx);
            set_bit_dio(PORTx);
            break;
        case INPUT:
            [[fallthrought]]
        default:
            clear_bit_dio(DDRx);
            clear_bit_dio(PORTx);
            break;
        }
    }

 private:
    const Pin pin;
    const int DDRx, PORTx, PINx;

    void set_bit_dio(int reg) const __attribute__((always_inline)) {
        libs::set_bit(*((volatile uint8_t *)(reg)), pin);
    }

    void clear_bit_dio(int reg) const __attribute__((always_inline)) {
        libs::clear_bit(*((volatile uint8_t *)(reg)), pin);
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_GPIO_DIGITALIO_H_
