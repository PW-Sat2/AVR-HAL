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
    constexpr AT24C02() : i2cdevice(0x50) {
    }

    template<typename T>
    void write(uint8_t addr, libs::array_view<T> & arr) const {
        i2cdevice.write_register(addr, arr.data(), arr.size());
    }

    template<typename T>
    void read(uint8_t addr, libs::array_view<T> & dest) const {
        i2cdevice.read_register(addr, dest.data(), dest.size());
    }

    template<typename T, size_t N>
    void write(uint8_t addr, libs::array<T, N> & arr) const {
        i2cdevice.write_register(addr, arr.data(), arr.size());
    }

    template<typename T, size_t N>
    void read(uint8_t addr, libs::array<T, N> & dest) const {
        i2cdevice.read_register(addr, dest.data(), dest.size());
    }

    I2C_Device_t<I2C> i2cdevice;
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
