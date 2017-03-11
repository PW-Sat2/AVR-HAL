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
    void write(uint8_t addr, const libs::span<const uint8_t> arr) const {
        i2cdevice.write_register(addr, arr);
    }

    void read(uint8_t addr, libs::span<uint8_t> dest) const {
        i2cdevice.read_register(addr, dest);
    }

 private:
    const I2C_Device<I2C> i2cdevice{0x50};
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
