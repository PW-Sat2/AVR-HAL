#ifndef HAL_DEVICES_TPS3813_H_
#define HAL_DEVICES_TPS3813_H_

#include "hal/periph.h"

namespace hal {

template<int pulse_time_ms>
class TPS3813 {
 public:
    constexpr explicit TPS3813(DigitalIO::Interface& pin_WDI) : pin_WDI{pin_WDI} {
    }

    void init() const {
        this->pin_WDI.init(hal::DigitalIO::Interface::Mode::OUTPUT);
        this->pin_WDI.reset();
    }

    void kick() const {
        this->pin_WDI.set();
        _delay_ms(pulse_time_ms);
        this->pin_WDI.reset();
    }

 private:
    DigitalIO::Interface &pin_WDI;
};

}  // namespace hal

#endif  // HAL_DEVICES_TPS3813_H_
