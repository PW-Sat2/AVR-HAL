#ifndef HAL_DEVICES_ADG709_H_
#define HAL_DEVICES_ADG709_H_

#include "hal/periph.h"

namespace hal {

class ADG709 {
 public:
    constexpr explicit ADG709(IDigitalIO& pin_A0, IDigitalIO& pin_A1,
                              IDigitalIO& pin_EN)
        : pin_A0{pin_A0}, pin_A1{pin_A1}, pin_EN{pin_EN} {
    }

    void init() const {
        this->pin_A0.init(IDigitalIO::Mode::OUTPUT);
        this->pin_A1.init(IDigitalIO::Mode::OUTPUT);
        this->pin_EN.init(IDigitalIO::Mode::OUTPUT);

        this->disable();
    }

    void enable() const {
        this->pin_EN.set();
    }

    void disable() const {
        this->pin_EN.reset();
    }

    void select(uint8_t channel) const {
        this->pin_A0.write(static_cast<bool>(channel & 0b01));
        this->pin_A1.write(static_cast<bool>(channel & 0b10));
    }

 private:
    IDigitalIO &pin_A0, &pin_A1, &pin_EN;
};

}  // namespace hal

#endif  // HAL_DEVICES_ADG709_H_
