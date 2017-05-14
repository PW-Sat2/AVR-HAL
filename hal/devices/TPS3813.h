#ifndef HAL_DEVICES_TPS3813_H_
#define HAL_DEVICES_TPS3813_H_

#include "hal/periph.h"

namespace hal {

class TPS3813 {
 public:
    constexpr explicit TPS3813(DigitalIO::Pin pin_WDI, uint8_t pulse_time_ms) : pin_WDI{pin_WDI}, pulse_time_ms{pulse_time_ms} {
    }

    void init() const {
        this->pin_WDI.pinmode(DigitalIO::OUTPUT);
        this->pin_WDI.reset();
    }

    void kick() const {
        this->pin_WDI.set();
        _delay_ms(this->pulse_time_ms);
        this->pin_WDI.reset();
    }

 private:
    DigitalIO pin_WDI;
    uint8_t pulse_time_ms;
};

}  // namespace hal

#endif  // HAL_DEVICES_TPS3813_H_
