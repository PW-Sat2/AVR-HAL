#ifndef HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_SPI_H_
#define HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_SPI_H_

#include "hal/periph/DigitalIO/PeriphDescriptors.h"

namespace hal {
namespace mcu {

constexpr static int pin_sck  = 11;
constexpr static int pin_mosi = 12;
constexpr static int pin_miso = 13;
constexpr static int pin_ss   = 10;

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_AT90CAN128_TQFP64_HAL_MCU_SPI_H_
