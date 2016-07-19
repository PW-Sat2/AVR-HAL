#ifndef HAL_MCU_ATMEGA2560_TQFP100_MCU_SERIAL_H_
#define HAL_MCU_ATMEGA2560_TQFP100_MCU_SERIAL_H_

#include <avr/io.h>
#include "PeriphDescriptors.h"

namespace hal {
namespace mcu {

#define SERIALs 4

constexpr static UART_descriptor UART_map[SERIALs] {
	{(int)&UBRR0H, (int)&UBRR0L, (int)&UCSR0A, (int)&UCSR0B, (int)&UCSR0C, (int)&UDR0},
	{(int)&UBRR1H, (int)&UBRR1L, (int)&UCSR1A, (int)&UCSR1B, (int)&UCSR1C, (int)&UDR1},
	{(int)&UBRR2H, (int)&UBRR2L, (int)&UCSR2A, (int)&UCSR2B, (int)&UCSR2C, (int)&UDR2},
	{(int)&UBRR3H, (int)&UBRR3L, (int)&UCSR3A, (int)&UCSR3B, (int)&UCSR3C, (int)&UDR3}
};

}
}

#endif  // HAL_MCU_ATMEGA2560_TQFP100_MCU_SERIAL_H_
