#ifndef HAL_DEVICES_ADC12X_H_
#define HAL_DEVICES_ADC12X_H_

#include "hal/periph.h"
#include "hal/libs.h"

namespace hal {
namespace drivers {
namespace details {

enum class Channels_ADC124 : uint8_t {
    IN0 = 0 << 3,
    IN1 = 1 << 3,
    IN2 = 2 << 3,
    IN3 = 3 << 3
};

enum class Channels_ADC128 : uint8_t {
    IN0 = 0 << 3,
    IN1 = 1 << 3,
    IN2 = 2 << 3,
    IN3 = 3 << 3,
    IN4 = 4 << 3,
    IN5 = 5 << 3,
    IN6 = 6 << 3,
    IN7 = 7 << 3
};

template<typename Channel_>
class ADC12x {
 public:
    /*!
     * Default ctor.
     * @param spi_dev SPI interface to use. Interface must support chip select transactions.
     */
    explicit ADC12x(SPI::Interface &spi_dev)
            : spi_dev(spi_dev) {
    }

    /*!
     * Channel for current device.
     * 4-channel enum for ADC124, 8-channel for ADC128.
     * Channels are named IN0..INx.
     */
    using Channel = Channel_;

    /*!
     * Function to retrieve data from sensor.
     * It reads data from previously-chosen channel (for first time it is IN0),
     * then sets the channel to use during next readout.
     * @param channel Channel to set after current read operation
     * @return Measurement of previously selected channel
     */
    uint16_t readAndChangeChannel(Channel channel) {
        const libs::array<uint8_t, 2> data_out = {
                static_cast<uint8_t>(channel),
                0
        };
        libs::array<uint8_t, 2> data_read;

        spi_dev.transfer(data_out, data_read);

        libs::Reader reader{data_read};
        auto word = reader.ReadWordBE();

        return word & libs::bit_mask<0, 12>();
    }

 private:
    SPI::Interface &spi_dev;
};

}  // namespace details

using ADC124 = details::ADC12x<details::Channels_ADC124>;
using ADC128 = details::ADC12x<details::Channels_ADC128>;


}  // namespace drivers
}  // namespace hal

#endif  // HAL_DEVICES_ADC12X_H_
