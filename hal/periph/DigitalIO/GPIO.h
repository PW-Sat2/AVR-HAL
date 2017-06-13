#ifndef HAL_PERIPH_DIGITALIO_GPIO_H_
#define HAL_PERIPH_DIGITALIO_GPIO_H_

#include "hal/periph/DigitalIO/PeriphDescriptors.h"

#include "Interface.h"
#include "hal/libs.h"
#include "hal/mcu.h"

namespace hal {
namespace DigitalIO {

template<int pin_nr>
class GPIO {
 public:
    constexpr static auto PORTx = mcu::DigitalIOPinMap[pin_nr].PORTx;
    constexpr static auto DDRx  = mcu::DigitalIOPinMap[pin_nr].DDRx;
    constexpr static auto PINx  = mcu::DigitalIOPinMap[pin_nr].PINx;
    constexpr static auto pin   = mcu::DigitalIOPinMap[pin_nr].pin;

    static_assert(PORTx != 0, "Incorrect pin!");
    static_assert(DDRx != 0, "Incorrect pin!");
    static_assert(PINx != 0, "Incorrect pin!");
    static_assert(pin <= 7, "Incorrect pin!");

    GPIO() = delete;
    GPIO(GPIO&) = delete;

    static constexpr inline void init(const Mode mode) {
        pinmode(mode);
    }

    static constexpr inline void set() {
        set_bit_dio(PORTx);
    }

    static constexpr inline void reset() {
        clear_bit_dio(PORTx);
    }

    static constexpr inline void write(bool value) {
        if (value) {
            set();
        } else {
            reset();
        }
    }

    static constexpr inline bool read() {
        return libs::read_bit(*((volatile uint8_t*)(PINx)), pin);
    }

    static constexpr inline void toggle() {
        if (read()) {
            reset();
        } else {
            set();
        }
    }

    static constexpr inline void pinmode(const DigitalIO::Mode mode)
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
            default:
                clear_bit_dio(DDRx);
                clear_bit_dio(PORTx);
                break;
        }
    }

 private:
    static constexpr inline void set_bit_dio(int reg) __attribute__((always_inline)) {
        libs::set_bit(*((volatile uint8_t*)(reg)), pin);
    }

    static constexpr inline void clear_bit_dio(int reg) __attribute__((always_inline)) {
        libs::clear_bit(*((volatile uint8_t*)(reg)), pin);
    }
};

}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_GPIO_H_
