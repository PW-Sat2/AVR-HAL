#ifndef HAL_PERIPH_SPI_INTERFACE_H_
#define HAL_PERIPH_SPI_INTERFACE_H_

#include <avr/io.h>
#include "hal/libs/array.h"
#include "hal/libs/bit_operations.h"
#include "hal/mcu.h"
#include "hal/periph/DigitalIO/Interface.h"

namespace hal {
namespace SPI {

class Interface {
 public:
    virtual uint8_t transfer(const uint8_t output) = 0;
    virtual void
    transfer(libs::span<const uint8_t> output, libs::span<uint8_t> input)  = 0;
    virtual void write(libs::span<const uint8_t> output)                   = 0;
    virtual void read(libs::span<uint8_t> input, uint8_t output_value = 0) = 0;
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_INTERFACE_H_
