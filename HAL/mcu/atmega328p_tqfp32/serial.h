#ifndef HAL_SERIAL_PORT_H_
#define HAL_SERIAL_PORT_H_

#include <stdint.h>


struct UART_descriptor {
	int UBRRnH, UBRRnL, UCSRnA, UCSRnB, UCSRnC, UDRn;
};

constexpr static UART_descriptor UART_map[] {
	{(int)&UBRR0H, (int)&UBRR0L, (int)&UCSR0A, (int)&UCSR0B, (int)&UCSR0C, (int)&UDR0}
};

extern int BAD_SERIAL_NUMBER;

#define READ_REG(reg) (*((volatile uint8_t *)(UART_map[serial_num].reg)))
#define WRITE_REG(reg, val) (*((volatile uint8_t *)(UART_map[serial_num].reg)) = val)

template<int serial_num>
class SerialImpl {
	static_assert(serial_num == 0, "Bad Serial number!");
	//constexpr SerialImpl() {
	//	static_assert(serial_num == 0, "Bad Serial number!");
	//}
 protected:
	constexpr uint16_t baud_to_ubrr(const uint32_t baud) {
		return (((F_CPU / 16.)/ (baud)) - 0.5);
	}
	
	void _init(const uint32_t baudrate) const __attribute__((always_inline)) {
		WRITE_REG(UBRRnH, baud_to_ubrr(baudrate) >> 8);
        WRITE_REG(UBRRnL, baud_to_ubrr(baudrate) & 0xFF);

        WRITE_REG(UCSRnC, (1 << UCSZ01) | (1 << UCSZ00));
        WRITE_REG(UCSRnB, (1 << RXEN0) | (1 << TXEN0));
	}
	
	void _send(const char byte) const __attribute__((always_inline)) {
		WRITE_REG(UDRn, byte);
        while (!(READ_REG(UCSRnA) & (1 << UDRE0))) {}
	}
	
	bool _available() const __attribute__((always_inline)) {
        return ((READ_REG(UCSRnA) & (1 << RXC0)));
    }

    uint8_t _read_byte() const __attribute__((always_inline)) {
        while (!this->_available()) {}
        return READ_REG(UDRn);
    }

	void write(const int addr, int val) const __attribute__((always_inline)) {
		*((volatile uint8_t *)(addr)) = val;
	}
	
	uint8_t read(const int addr) const __attribute__((always_inline)) {
		return *((volatile uint8_t *)(addr));
	}
};

#endif  // HAL_SERIAL_PORT_H_
