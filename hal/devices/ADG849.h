#ifndef HAL_DEVICES_ADG849_H_
#define HAL_DEVICES_ADG849_H_

#include "hal/periph.h"

namespace hal {

class ADG849 {
 public:
    constexpr explicit ADG849(DigitalIO::Pin pin_IN) : pin_IN{pin_IN} {
    }

    void init() const {
        this->pin_IN.pinmode(DigitalIO::OUTPUT);
    }

    void select(uint8_t channel) const {
        this->pin_IN.write(static_cast<bool>(channel));
    }

 private:
    DigitalIO pin_IN;
};

}  // namespace hal

#endif  // HAL_DEVICES_ADG849_H_
