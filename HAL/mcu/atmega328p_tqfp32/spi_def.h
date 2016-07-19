#ifndef HAL_MCU_ATMEGA328P_TQFP32_SPI_DEF_H_
#define HAL_MCU_ATMEGA328P_TQFP32_SPI_DEF_H_

#include "periph/DigitalIO.h"

namespace hal {

namespace mcu {

constexpr static hal::DigitalIO::Pin pin_sck = 1;
constexpr static hal::DigitalIO::Pin pin_mosi = 1;
constexpr static hal::DigitalIO::Pin pin_ss = 1;

}

}

#endif /* HAL_MCU_ATMEGA328P_TQFP32_SPI_DEF_H_ */
