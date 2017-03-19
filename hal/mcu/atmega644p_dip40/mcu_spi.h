#ifndef HAL_MCU_ATMEGA644P_DIP40_MCU_SPI_H_
#define HAL_MCU_ATMEGA644P_DIP40_MCU_SPI_H_

#include "PeriphDescriptors.h"
#include "DigitalIO.h"

namespace hal {
namespace mcu {

constexpr static int pin_sck = 8;   // PB7
constexpr static int pin_mosi = 6;  // PB5
constexpr static int pin_miso = 7;  // PB6
constexpr static int pin_ss = 5;    // PB4

}
}

#endif  // HAL_MCU_ATMEGA644P_DIP40_MCU_SPI_H_
