#ifndef HAL_MCU_ATMEGA328P_TQFP32_SERIAL_H_
#define HAL_MCU_ATMEGA328P_TQFP32_SERIAL_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define SERIALs 4

constexpr static UART_descriptor UART_map[SERIALs] {
	{(int)&UBRR0H, (int)&UBRR0L, (int)&UCSR0A, (int)&UCSR0B, (int)&UCSR0C, (int)&UDR0}
};

}
}

#endif  // HAL_MCU_ATMEGA328P_TQFP32_SERIAL_H_
