#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include <stdlib.h>
#include "I2C.h"
#include "array.h"
#include "array_view.h"

namespace hal {


template<typename I2C>
class AT24C02 {
public:
    using i2cdevice = I2C_Device_t<I2C, 0x50>;

    template<typename T>
    void write(uint8_t addr, libs::array_view<T> & arr) const {
        i2cdevice::write_register(addr, arr);
    }

    template<typename T>
    void read(uint8_t addr, libs::array_view<T> & dest) const {
        i2cdevice::read_register(addr, dest);
    }

    template<typename T, size_t N>
    void write(uint8_t addr, libs::array<T, N> & arr) const {
        i2cdevice::write_register(addr, arr.as_array_view());
    }

    template<typename T, size_t N>
    void read(uint8_t addr, libs::array<T, N> & dest) const {
        i2cdevice::read_register(addr, dest.as_array_view());
    }
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
