#ifndef FPF270X_H_
#define FPF270X_H_

#include "hal/periph.h"

namespace hal {

class FPF270x {
public:
    constexpr FPF270x(const DigitalIO::Interface::Pin pin_on,
            const DigitalIO::Interface::Pin pin_flag, const DigitalIO::Interface::Pin pin_pgood) :
            pin_on{pin_on}, pin_flag{pin_flag}, pin_pgood{pin_pgood} {
    }

    void init() {
        this->pin_on.init(IDigitalIO::Mode::OUTPUT);
        this->pin_flag.init(IDigitalIO::Mode::INPUT_PULLUP);
        this->pin_pgood.init(IDigitalIO::Mode::INPUT_PULLUP);
    }

    void on() {
        this->pin_on.reset();
    }

    void off() {
        this->pin_on.set();
    }

    bool errorOccured() {
        return this->pin_flag.read();
    }

    bool powerGood() {
        return this->pin_pgood.read();
    }

private:
    const DigitalIO pin_on, pin_flag, pin_pgood;
};

}  // namespace hal

#endif /* FPF270X_H_ */
