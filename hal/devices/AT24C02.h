#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include "hal/periph.h"

namespace hal {

class AT24C02 {
 public:
    AT24C02(II2C& i2c) : i2cdevice{i2c, 0x50} {}
    void write(uint8_t addr, const libs::span<const uint8_t> arr) const {
        i2cdevice.write_register(addr, arr);
    }

    void read(uint8_t addr, libs::span<uint8_t> dest) const {
        i2cdevice.read_register(addr, dest);
    }

 private:
    I2C_Device i2cdevice;
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
