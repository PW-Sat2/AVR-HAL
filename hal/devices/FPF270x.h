#ifndef HAL_DEVICES_FPF270X_H_
#define HAL_DEVICES_FPF270X_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

class FPF270x {
 public:
    constexpr FPF270x(DigitalIO::Interface &pin_on,
                      DigitalIO::Interface &pin_flag,
                      DigitalIO::Interface &pin_pgood) :
            pin_on{pin_on}, pin_flag{pin_flag}, pin_pgood{pin_pgood} {
    }

    void init() {
        this->pin_on.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_flag.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
        this->pin_pgood.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    }

    void on() {
        this->pin_on.reset();
    }

    void off() {
        this->pin_on.set();
    }

    bool error_occured() {
        return this->pin_flag.read();
    }

    bool power_good() {
        return this->pin_pgood.read();
    }

 private:
    DigitalIO::Interface &pin_on, &pin_flag, &pin_pgood;
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_FPF270X_H_
