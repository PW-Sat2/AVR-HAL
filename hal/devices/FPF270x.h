#ifndef HAL_DEVICES_FPF270X_H_
#define HAL_DEVICES_FPF270X_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

template <typename pin_on,
    typename pin_flag,
    typename pin_pgood
    >
class FPF270x {
 public:
    void init() {
        pin_on::init(DigitalIO::Mode::OUTPUT);
        pin_flag::init(DigitalIO::Mode::INPUT_PULLUP);
        pin_pgood::init(DigitalIO::Mode::INPUT_PULLUP);
    }

    void on() {
        pin_on::reset();
    }

    void off() {
        pin_on::set();
    }

    bool error_occured() {
        return pin_flag::read();
    }

    bool power_good() {
        return pin_pgood::read();
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_FPF270X_H_
