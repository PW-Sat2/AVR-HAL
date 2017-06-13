#ifndef HAL_DEVICES_ADG709_H_
#define HAL_DEVICES_ADG709_H_

#include "hal/periph.h"

namespace hal {
namespace devices {
namespace ADG709 {

enum class Channel : uint8_t {
    S1 = 0,
    S2 = 1,
    S3 = 2,
    S4 = 3,
};

template<typename pin_A0, typename pin_A1, typename pin_EN>
class ADG709 {
 public:
    static void init() {
        pin_A0::init(DigitalIO::Mode::OUTPUT);
        pin_A1::init(DigitalIO::Mode::OUTPUT);
        pin_EN::init(DigitalIO::Mode::OUTPUT);

        disable();
    }

    static void enable() {
        pin_EN::set();
    }

    static void disable() {
        pin_EN::reset();
    }

    static void select(Channel channel) {
        pin_A0::write(libs::read_bit<0>(static_cast<uint8_t>(channel)));
        pin_A1::write(libs::read_bit<1>(static_cast<uint8_t>(channel)));
    }
};

}  // namespace ADG709
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_ADG709_H_
