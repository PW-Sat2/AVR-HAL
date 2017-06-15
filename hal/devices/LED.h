#ifndef HAL_DEVICES_LED_H_
#define HAL_DEVICES_LED_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

template<typename led_pin>
struct LED : libs::PureStatic {
    static void init() {
        led_pin::init(DigitalIO::Mode::OUTPUT);
    }

    static void on() {
        led_pin::set();
    }

    static void off() {
        led_pin::reset();
    }

    static void write(bool state) {
        led_pin::write(state);
    }

    static void toggle() {
        led_pin::toggle();
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_LED_H_
