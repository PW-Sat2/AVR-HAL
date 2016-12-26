#ifndef HAL_MCU_ATMEGA2560_TQFP100_MCU_SPI_H_
#define HAL_MCU_ATMEGA2560_TQFP100_MCU_SPI_H_

#include "PeriphDescriptors.h"
#include "DigitalIO.h"

namespace hal {
namespace mcu {

constexpr static int pin_sck = 20;
constexpr static int pin_mosi = 21;
constexpr static int pin_miso = 22;
constexpr static int pin_ss = 19;

}
}

#endif /* HAL_MCU_ATMEGA2560_TQFP100_MCU_SPI_H_ */
