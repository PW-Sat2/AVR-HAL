#ifndef HAL_MCU_ATMEGA128A_TQFP64_SERIAL_H_
#define HAL_MCU_ATMEGA128A_TQFP64_SERIAL_H_

#include <stdint.h>


struct UART_descriptor {
	int UBRRnH, UBRRnL, UCSRnA, UCSRnB, UCSRnC, UDRn;
};

#define SERIALs 2

constexpr static UART_descriptor UART_map[SERIALs] {
	{(int)&UBRR0H, (int)&UBRR0L, (int)&UCSR0A, (int)&UCSR0B, (int)&UCSR0C, (int)&UDR0}
};


#define READ_REG(reg) (*((volatile uint8_t *)(UART_map[serial_num].reg)))
#define WRITE_REG(reg, val) (*((volatile uint8_t *)(UART_map[serial_num].reg)) = val)

template<int serial_num>
class SerialImpl {
 public:
	static_assert(serial_num >= 0, "Bad Serial number!");
	static_assert(serial_num < SERIALs, "Bad Serial number!");

	constexpr static uint16_t baud_to_ubrr(const uint32_t baud) {
		return (((F_CPU / 16.)/ (baud)) - 0.5);
	}
	
	void init(const uint32_t baudrate) const __attribute__((always_inline)) {
		const uint32_t ubrr = baud_to_ubrr(baudrate);
		WRITE_REG(UBRRnH, ubrr >> 8);
        WRITE_REG(UBRRnL, ubrr & 0xFF);

        WRITE_REG(UCSRnC, (1 << UCSZ01) | (1 << UCSZ00));
        WRITE_REG(UCSRnB, (1 << RXEN0) | (1 << TXEN0));
	}
	
	void print_byte(const char byte) const __attribute__((always_inline)) {
		WRITE_REG(UDRn, byte);
        while (!(READ_REG(UCSRnA) & (1 << UDRE0))) {}
	}
	
	bool available() const __attribute__((always_inline)) {
        return ((READ_REG(UCSRnA) & (1 << RXC0)));
    }

    uint8_t read_byte() const __attribute__((always_inline)) {
        while (!this->available()) {}
        return READ_REG(UDRn);
    }
};


#endif  // HAL_MCU_ATMEGA128A_TQFP64_SERIAL_H_
