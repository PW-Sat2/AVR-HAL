#ifndef HAL_MCU_ATMEGA328P_TQFP32_MCU_SERIAL_H_
#define HAL_MCU_ATMEGA328P_TQFP32_MCU_SERIAL_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define SERIALs 1

#define SERIAL_DEF(nr) { reinterpret_cast<int>(&UBRR ## nr ## H),    \
                         reinterpret_cast<int>(&UBRR ## nr ## L),    \
                         reinterpret_cast<int>(&UCSR ## nr ## A),    \
                         reinterpret_cast<int>(&UCSR ## nr ## B),    \
                         reinterpret_cast<int>(&UCSR ## nr ## C),    \
                         reinterpret_cast<int>(&UDR ## nr) }

constexpr static UART_descriptor UART_map[SERIALs] = {
    SERIAL_DEF(0)
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA328P_TQFP32_MCU_SERIAL_H_
