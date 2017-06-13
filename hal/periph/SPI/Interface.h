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

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_INTERFACE_H_
