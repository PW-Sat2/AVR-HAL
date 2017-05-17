#ifndef HAL_DEVICES_LED_H_
#define HAL_DEVICES_LED_H_

#include "hal/periph.h"

namespace hal {

class LED {
 public:
    constexpr LED(IDigitalIO& pin) :
            led_pin{pin} {
    }

    void init() const {
        led_pin.init(IDigitalIO::Mode::OUTPUT);
    }

    void on() const {
        led_pin.set();
    }

    void off() const {
        led_pin.reset();
    }

    void write(bool state) const {
        led_pin.write(state);
    }

    void toggle() const {
        led_pin.toggle();
    }

 private:
    IDigitalIO& led_pin;
};

}  // namespace hal

#endif  // HAL_DEVICES_LED_H_
