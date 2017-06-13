#ifndef HAL_PERIPH_I2C_INTERFACE_H_
#define HAL_PERIPH_I2C_INTERFACE_H_

namespace hal {
namespace I2C {

using Address = uint8_t;

// Interface for I2C:
//   void write(uint8_t address, gsl::span<const uint8_t> data);
//   void read(uint8_t address, gsl::span<uint8_t> data);
//   virtual void write_read(uint8_t address, gsl::span<const uint8_t> output,
//   gsl::span<uint8_t> input)

}  // namespace I2C
}  // namespace hal

#endif  // HAL_PERIPH_I2C_INTERFACE_H_
