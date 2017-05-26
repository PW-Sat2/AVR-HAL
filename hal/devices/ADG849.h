#ifndef HAL_DEVICES_ADG849_H_
#define HAL_DEVICES_ADG849_H_

#include "hal/periph.h"

namespace hal {

class ADG849 {
 public:
    enum class Channel : bool {
        S1 = 0,
        S2 = 1
    };

    /*!
     * Default ctor.
     * @param pin_IN DigitalIO interface to use as IN pin of ADG849
     */
    constexpr explicit ADG849(DigitalIO::Interface& pin_IN) : pin_IN{pin_IN} {
    }

    /*!
     * Function to initialize device.
     * It sets DigitalIO IN pin as OUTPUT.
     * @param default_channel sets multiplexer channel after initialization
     */
    void init(Channel default_channel) const {
        this->select(default_channel);
        this->pin_IN.init(DigitalIO::Interface::Mode::OUTPUT);
    }

    /*!
     * Function sets desired mux channel.
     * @param channel Channel to set active mux channel
     */
    void select(Channel channel) const {
        this->pin_IN.write(static_cast<bool>(channel));
    }

 private:
    DigitalIO::Interface& pin_IN;
};

}  // namespace hal

#endif  // HAL_DEVICES_ADG849_H_
