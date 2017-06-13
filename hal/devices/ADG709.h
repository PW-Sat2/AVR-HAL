#ifndef HAL_DEVICES_ADG709_H_
#define HAL_DEVICES_ADG709_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

class ADG709 {
 public:
    enum class Channel : uint8_t {
        S1 = 0,
        S2 = 1,
        S3 = 2,
        S4 = 3,
    };

    constexpr explicit ADG709(DigitalIO::Interface& pin_A0,
                              DigitalIO::Interface& pin_A1,
                              DigitalIO::Interface& pin_EN)
        : pin_A0{pin_A0}, pin_A1{pin_A1}, pin_EN{pin_EN} {
    }

    void init() const {
        this->pin_A0.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_A1.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_EN.init(DigitalIO::Interface::Mode::OUTPUT);

        this->disable();
    }

    void enable() const {
        this->pin_EN.set();
    }

    void disable() const {
        this->pin_EN.reset();
    }

    void select(Channel channel) const {
        this->pin_A0.write(libs::read_bit<0>(static_cast<uint8_t>(channel)));
        this->pin_A1.write(libs::read_bit<1>(static_cast<uint8_t>(channel)));
    }

 private:
    DigitalIO::Interface &pin_A0, &pin_A1, &pin_EN;
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_ADG709_H_
