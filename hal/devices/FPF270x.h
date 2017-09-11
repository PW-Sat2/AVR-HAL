#ifndef HAL_DEVICES_FPF270X_H_
#define HAL_DEVICES_FPF270X_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

template<typename pin_on, typename pin_flag, typename pin_pgood>
struct FPF270x : libs::PureStatic {
    static void init() {
        pin_on::init(DigitalIO::Mode::OUTPUT);
        pin_flag::init(DigitalIO::Mode::INPUT_PULLUP);
        pin_pgood::init(DigitalIO::Mode::INPUT_PULLUP);
    }

    static void on() {
        pin_on::reset();
    }

    static void off() {
        pin_on::set();
    }

    static bool error_occured() {
        return !pin_flag::read();
    }

    static bool power_good() {
        return pin_pgood::read();
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_FPF270X_H_
