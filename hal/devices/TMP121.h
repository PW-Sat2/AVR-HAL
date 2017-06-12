#ifndef HAL_DEVICES_TMP121_H_
#define HAL_DEVICES_TMP121_H_

#include "hal/periph.h"

namespace hal {

/*!
 * TMP121 temperature sensor driver.
 */
class TMP121 {
 public:
    /*!
     * Default ctor.
     * SPI device have to support idle-high chip select.
     * @param spi SPI device to operate on.
     */
    constexpr TMP121(SPI::Interface& spi) : spi(spi) {
    }

    /*!
     * Reads data from the sensor in raw integer format.
     * After conversion de-asserts the device and puts it in free-running mode.
     * @return Read data from the device (13 bit value)
     */
    int16_t read() {
        std::array<uint8_t, 2> arr;
        spi.read(arr);

        libs::Reader reader{arr};
        uint16_t sensor_data = reader.ReadWordBE();
        sensor_data >>= 3;

        uint16_t mask = libs::power_of_two<12>();

        return -(sensor_data & mask) + (sensor_data & ~mask);
    }

    /*!
     * Reads temperature from the device and converts it to Celsius degrees.
     * @see #read
     * @return Converted temperature to Celsius.
     */
    float read_celsius() {
        return static_cast<float>(read()) * 0.0625;
    }

 private:
    SPI::Interface& spi;
};

}  // namespace hal

#endif  // HAL_DEVICES_TMP121_H_
