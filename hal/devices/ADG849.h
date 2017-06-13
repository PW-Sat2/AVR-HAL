#ifndef HAL_DEVICES_ADG849_H_
#define HAL_DEVICES_ADG849_H_

#include "hal/periph.h"

namespace hal {
struct ADG849_ {
    enum class Channel : bool {
        S1 = 0,
        S2 = 1,
    };
};
template <typename pin_IN>
class ADG849 : public ADG849_ {
 public:

    /*!
     * Function to initialize device.
     * It sets DigitalIO IN pin as OUTPUT.
     * @param default_channel sets multiplexer channel after initialization
     */
    void init(Channel default_channel) const {
        select(default_channel);
        pin_IN::init(DigitalIO::Mode::OUTPUT);
    }

    /*!
     * Function sets desired mux channel.
     * @param channel Channel to set active mux channel
     */
    void select(Channel channel) const {
        pin_IN::write(static_cast<bool>(channel));
    }
};

}  // namespace hal

#endif  // HAL_DEVICES_ADG849_H_
