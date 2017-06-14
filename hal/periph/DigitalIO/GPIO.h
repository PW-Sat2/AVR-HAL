#ifndef HAL_PERIPH_DIGITALIO_GPIO_H_
#define HAL_PERIPH_DIGITALIO_GPIO_H_

#include "hal/periph/DigitalIO/PeriphDescriptors.h"

#include "hal/libs.h"
#include "hal/mcu.h"

namespace hal {
namespace DigitalIO {

using Pin = uint8_t;

enum class Mode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
};

template<int pin_nr_>
class GPIO {
 private:
    constexpr static auto PORTxx = mcu::DigitalIOPinMap[pin_nr_].PORTx;
    constexpr static auto DDRxx  = mcu::DigitalIOPinMap[pin_nr_].DDRx;
    constexpr static auto PINxx  = mcu::DigitalIOPinMap[pin_nr_].PINx;
    constexpr static auto pin   = mcu::DigitalIOPinMap[pin_nr_].pin;

 public:
    constexpr static volatile uint8_t* PORTx = (volatile uint8_t*) PORTxx;
    constexpr static volatile uint8_t* DDRx = (volatile uint8_t*) DDRxx;
    constexpr static volatile uint8_t* PINx = (volatile uint8_t*) PINxx;

    static_assert(PORTxx != 0, "Incorrect pin!");
    static_assert(DDRxx != 0, "Incorrect pin!");
    static_assert(PINxx != 0, "Incorrect pin!");
    static_assert(pin <= 7, "Incorrect pin!");

    GPIO() = delete;

    constexpr static auto pin_nr = pin_nr_;

    static constexpr inline void init(const Mode mode) {
        pinmode(mode);
    }

    static constexpr inline void set() {
        libs::set_bit<pin>(*PORTx);
    }

    static constexpr inline void reset() {
        libs::clear_bit<pin>(*PORTx);
    }

    static constexpr inline void write(bool value) {
        libs::write_bit<pin>(*PORTx, value);
    }

    static constexpr inline bool read() {
        return libs::read_bit<pin>(*PINx);
    }

    static constexpr inline void toggle() {
        libs::set_bit<pin>(*PINx);
    }

 private:

    static constexpr inline void
    pinmode(const DigitalIO::Mode mode) __attribute__((always_inline)) {
        switch (mode) {
            case Mode::OUTPUT:
                libs::set_bit<pin>(*DDRx);
                break;

            case Mode::INPUT_PULLUP:
                libs::clear_bit<pin>(*DDRx);
                libs::set_bit<pin>(*PORTx);
                break;

            case Mode::INPUT:
            default:
                libs::clear_bit<pin>(*DDRx);
                libs::clear_bit<pin>(*PORTx);
                break;
        }
    }
};

}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_GPIO_H_
