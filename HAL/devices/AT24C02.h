#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include <stdlib.h>
#include "I2C.h"
#include "array.h"
#include "span.h"

namespace hal {

template<typename I2C>
class AT24C02 {
 public:
    template<typename T>
    void write(uint8_t addr, const libs::span<const T> & arr) const {
        i2cdevice.write_register(addr, arr);
    }

    template<typename T>
    void read(uint8_t addr, libs::span<T> & dest) const {
        i2cdevice.read_register(addr, dest);
    }

    template<typename T, size_t N>
    void write(uint8_t addr, const libs::array<T, N> & arr) const {
        i2cdevice.write_register(addr, arr.as_span());
    }

    template<typename T, size_t N>
    void read(uint8_t addr, libs::array<T, N> & dest) const {
        i2cdevice.read_register(addr, dest.as_span());
    }

 private:
    const I2C_Device<I2C> i2cdevice{0x50};
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
