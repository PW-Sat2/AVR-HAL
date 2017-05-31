#ifndef HAL_DEVICES_ADG708_H_
#define HAL_DEVICES_ADG708_H_

#include "hal/periph.h"

namespace hal {

class ADG708 {
 public:
    constexpr explicit ADG708(DigitalIO::Interface& pin_A0,
                              DigitalIO::Interface& pin_A1,
                              DigitalIO::Interface& pin_A2,
                              DigitalIO::Interface& pin_EN)
        : pin_A0{pin_A0}, pin_A1{pin_A1}, pin_A2{pin_A2}, pin_EN{pin_EN} {
    }

    void init() const {
        this->pin_A0.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_A1.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_A2.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_EN.init(DigitalIO::Interface::Mode::OUTPUT);

        this->disable();
    }

    void enable() const {
        this->pin_EN.set();
    }

    void disable() const {
        this->pin_EN.reset();
    }

    void select(uint8_t channel) const {
        this->pin_A0.write(static_cast<bool>(channel & 0b001));
        this->pin_A1.write(static_cast<bool>(channel & 0b010));
        this->pin_A2.write(static_cast<bool>(channel & 0b100));
    }

 private:
    DigitalIO::Interface &pin_A0, &pin_A1, &pin_A2, &pin_EN;
};

}  // namespace hal

#endif  // HAL_DEVICES_ADG708_H_
