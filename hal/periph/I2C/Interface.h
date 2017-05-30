#ifndef HAL_PERIPH_I2C_INTERFACE_H_
#define HAL_PERIPH_I2C_INTERFACE_H_

#include <type_traits>
#include <utility>

#include "hal/libs.h"

namespace hal {
namespace I2C {

class Interface {
 public:
    using Address = uint8_t;

    virtual void write(uint8_t address, libs::span<const uint8_t> data) = 0;
    virtual void read(uint8_t address, libs::span<uint8_t> data)        = 0;
    virtual void writeRead(uint8_t address,
                           libs::span<const uint8_t> output,
                           libs::span<uint8_t> input)                   = 0;
};

}  // namespace I2C
}  // namespace hal

#endif  // HAL_PERIPH_I2C_INTERFACE_H_
