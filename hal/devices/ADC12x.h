#ifndef HAL_DEVICES_ADC12X_H_
#define HAL_DEVICES_ADC12X_H_

#include "hal/libs.h"
#include "hal/periph.h"

namespace hal {
namespace drivers {

struct ADC124_ {
    enum class Channel : uint8_t {
        IN0 = 0 << 3,
        IN1 = 1 << 3,
        IN2 = 2 << 3,
        IN3 = 3 << 3
    };
};

struct ADC128_ {
    enum class Channel : uint8_t {
        IN0 = 0 << 3,
        IN1 = 1 << 3,
        IN2 = 2 << 3,
        IN3 = 3 << 3,
        IN4 = 4 << 3,
        IN5 = 5 << 3,
        IN6 = 6 << 3,
        IN7 = 7 << 3
    };
};

namespace details {

template<typename Channel, typename SPI>
class ADC12x {
 public:
    /*!
     * Function to retrieve data from sensor.
     * It reads data from previously-chosen channel (for first time it is IN0),
     * then sets the channel to use during next readout.
     * @param channel Channel to set after current read operation
     * @return Measurement of previously selected channel
     */
    uint16_t read_and_change_channel(Channel channel) {
        const std::array<uint8_t, 2> data_out = {static_cast<uint8_t>(channel), 0};
        std::array<uint8_t, 2> data_read;

        SPI::transfer(data_out, data_read);

        libs::Reader reader{data_read};
        auto word = reader.ReadWordBE();

        return word & libs::bit_mask<0, 12>();
    }
};

}  // namespace details

template<typename SPI>
using ADC124 = details::ADC12x<ADC124_::Channel, SPI>;

template<typename SPI>
using ADC128 = details::ADC12x<ADC128_::Channel, SPI>;

}  // namespace drivers
}  // namespace hal

#endif  // HAL_DEVICES_ADC12X_H_
