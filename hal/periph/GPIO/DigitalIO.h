#ifndef HAL_PERIPH_GPIO_DIGITALIO_H_
#define HAL_PERIPH_GPIO_DIGITALIO_H_

#include "hal/periph/GPIO/PeriphDescriptors.h"

#include "hal/libs.h"
#include "hal/mcu.h"
#include "IDigitalIO.h"

namespace hal {

template<int pin_nr>
class DigitalIO : public IDigitalIO {
 public:
    constexpr DigitalIO() {}
    constexpr static auto PORTx = mcu::DigitalIOPinMap[pin_nr].PORTx;
    constexpr static auto DDRx = mcu::DigitalIOPinMap[pin_nr].DDRx;
    constexpr static auto PINx = mcu::DigitalIOPinMap[pin_nr].PINx;
    constexpr static auto pin = mcu::DigitalIOPinMap[pin_nr].pin;

    static_assert(PORTx != 0, "Incorrect pin!");
    static_assert(DDRx != 0, "Incorrect pin!");
    static_assert(PINx != 0, "Incorrect pin!");
    static_assert(pin <= 7, "Incorrect pin!");

    void init(const Mode mode) override {
        pinmode(mode);
    }

    void set() override {
        set_bit_dio(PORTx);
    }

    void reset() override {
        clear_bit_dio(PORTx);
    }

    void write(bool value) override {
        if (value) {
            this->set();
        } else {
            this->reset();
        }
    }

    bool read() override {
        return libs::read_bit(*((volatile uint8_t *)(PINx)), pin);
    }

    void toggle() override {
        if (read()) {
            reset();
        } else {
            set();
        }
    }

    inline void pinmode(const DigitalIO::Mode mode) const
            __attribute__((always_inline)) {
        switch (mode) {
        case Mode::OUTPUT:
            set_bit_dio(DDRx);
            // clear_bit_dio(PORTx);
            break;
        case Mode::INPUT_PULLUP:
            clear_bit_dio(DDRx);
            set_bit_dio(PORTx);
            break;
        case Mode::INPUT:
            [[fallthrought]]
        default:
            clear_bit_dio(DDRx);
            clear_bit_dio(PORTx);
            break;
        }
    }

 private:
    void set_bit_dio(int reg) const __attribute__((always_inline)) {
        libs::set_bit(*((volatile uint8_t *)(reg)), pin);
    }

    void clear_bit_dio(int reg) const __attribute__((always_inline)) {
        libs::clear_bit(*((volatile uint8_t *)(reg)), pin);
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_GPIO_DIGITALIO_H_
