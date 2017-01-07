#ifndef HAL_MCU_ATMEGA164P_324P_644P_44_MCU_SPI_H_
#define HAL_MCU_ATMEGA164P_324P_644P_44_MCU_SPI_H_

#include "PeriphDescriptors.h"
#include "DigitalIO.h"

namespace hal {
namespace mcu {

constexpr static int pin_sck = 3;
constexpr static int pin_mosi = 1;
constexpr static int pin_miso = 2;
constexpr static int pin_ss = 44;

}
}

#endif  // HAL_MCU_ATMEGA164P_324P_644P_44_MCU_SPI_H_
