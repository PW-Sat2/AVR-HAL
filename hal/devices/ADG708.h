#ifndef HAL_DEVICES_ADG708_H_
#define HAL_DEVICES_ADG708_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

struct ADG708_ {
    enum class Channel : uint8_t {
        S1 = 0,
        S2 = 1,
        S3 = 2,
        S4 = 3,
        S5 = 4,
        S6 = 5,
        S7 = 6,
        S8 = 7
    };
};

template <typename pin_A0,
    typename pin_A1,
    typename pin_A2,
    typename pin_EN>
class ADG708 : public ADG708_ {
 public:
    void init() const {
        pin_A0::init(DigitalIO::Mode::OUTPUT);
        pin_A1::init(DigitalIO::Mode::OUTPUT);
        pin_A2::init(DigitalIO::Mode::OUTPUT);
        pin_EN::init(DigitalIO::Mode::OUTPUT);

        disable();
    }

    void enable() const {
        pin_EN::set();
    }

    void disable() const {
        pin_EN::reset();
    }

    void select(Channel channel) const {
        pin_A0::write(libs::read_bit<0>(static_cast<uint8_t>(channel)));
        pin_A1::write(libs::read_bit<1>(static_cast<uint8_t>(channel)));
        pin_A2::write(libs::read_bit<2>(static_cast<uint8_t>(channel)));
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_ADG708_H_
