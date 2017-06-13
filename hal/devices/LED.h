#ifndef HAL_DEVICES_LED_H_
#define HAL_DEVICES_LED_H_

#include "hal/periph.h"

namespace hal {

template <typename GPIO>
class LED {
 public:
    constexpr LED(GPIO& pin) : led_pin{pin} {
    }

    void init() const {
        led_pin.init(DigitalIO::Mode::OUTPUT);
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
    GPIO& led_pin;
};

}  // namespace hal

#endif  // HAL_DEVICES_LED_H_
