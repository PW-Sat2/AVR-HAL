#ifndef HAL_DEVICES_TMP121_H_
#define HAL_DEVICES_TMP121_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

/*!
 * TMP121 temperature sensor driver.
 */
template<typename SPI>
struct TMP121 : libs::PureStatic {
    /*!
     * Reads data from the sensor in raw format.
     * After conversion de-asserts the device and puts it in free-running mode.
     * @return Read data from the device (13 bit, unsigned,
     * 2's complement form).
     */
    static uint13_t read_raw() {
        std::array<uint8_t, 2> arr;
        SPI::read(arr);

        libs::Reader reader{arr};
        uint16_t sensor_data = reader.ReadWordBE();
        sensor_data >>= 3;

        return sensor_data;
    }

    /*!
     * Reads data from the sensor in raw integer format.
     * After conversion de-asserts the device and puts it in free-running mode.
     * @return Read data from the device (13 bit value, signed,
     * 1 LSB = 0.0625 celsius)
     */
    static int16_t read() {
        uint16_t sensor_data = read_raw();

        uint16_t mask = libs::power_of_two<12>();

        return -(sensor_data & mask) + (sensor_data & ~mask);
    }

    /*!
     * Reads temperature from the device and converts it to Celsius degrees.
     * @see #read
     * @return Converted temperature to Celsius.
     */
    static float read_celsius() {
        return static_cast<float>(read()) * 0.0625;
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_TMP121_H_
