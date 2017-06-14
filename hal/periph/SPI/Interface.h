#ifndef HAL_PERIPH_SPI_INTERFACE_H_
#define HAL_PERIPH_SPI_INTERFACE_H_

#include "hal/libs.h"

namespace hal {
namespace SPI {

// Interface for SPI:
//   uint8_t transfer(const uint8_t output);
//   void transfer(gsl::span<const uint8_t> output, gsl::span<uint8_t> input);
//   void write(gsl::span<const uint8_t> output);
//   void read(gsl::span<uint8_t> input, uint8_t output_value);

enum class Polarity : int {
    idle_low  = 0,
    idle_high = 1,
};

enum class Phase : int {
    leading_sample  = 0,
    trailing_sample = 1,
};

enum class DataOrder : int {
    MSB_first = 0,
    LSB_first = 1,
};

enum class HardwareClockDivisor {
    SPIHard_DIV_4   = 0,
    SPIHard_DIV_16  = 1,
    SPIHard_DIV_64  = 2,
    SPIHard_DIV_128 = 3,
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_INTERFACE_H_
