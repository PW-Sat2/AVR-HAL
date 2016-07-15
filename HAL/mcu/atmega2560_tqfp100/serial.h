#ifndef HAL_SERIAL_PORT_H_
#define HAL_SERIAL_PORT_H_

#include <stdint.h>

class SerialX_;

struct UART_descriptor {
	int UBRRnH, UBRRnL, UCSRnA, UCSRnB, UCSRnC, UDRn;
};

constexpr static UART_descriptor UART_map[] {
	{(int)&UBRR0H, (int)&UBRR0L, (int)&UCSR0A, (int)&UCSR0B, (int)&UCSR0C, (int)&UDR0},
	{(int)&UBRR1H, (int)&UBRR1L, (int)&UCSR1A, (int)&UCSR1B, (int)&UCSR1C, (int)&UDR1},
	{(int)&UBRR2H, (int)&UBRR2L, (int)&UCSR2A, (int)&UCSR2B, (int)&UCSR2C, (int)&UDR2},
	{(int)&UBRR3H, (int)&UBRR3L, (int)&UCSR3A, (int)&UCSR3B, (int)&UCSR3C, (int)&UDR3}
};

extern int BAD_SERIAL_NUMBER;

class SerialImpl {
	friend class SerialX_;
	
	
	constexpr SerialImpl(int i) : serial_nr(i >= 0 ? i < 4 ? i : BAD_SERIAL_NUMBER : BAD_SERIAL_NUMBER), 
                                  UBRRnH(UART_map[i].UBRRnH != 0 ? UART_map[i].UBRRnH : BAD_SERIAL_NUMBER ),
                                  UBRRnL(UART_map[i].UBRRnL), UCSRnA(UART_map[i].UCSRnA), 
                                  UCSRnB(UART_map[i].UCSRnB), UCSRnC(UART_map[i].UCSRnC), UDRn(UART_map[i].UDRn)
	{}
	
	constexpr uint16_t baud_to_ubrr(const uint32_t baud) {
		return (((F_CPU / 16.)/ (baud)) - 0.5);
	}
	
	void _init(const uint32_t baudrate) const __attribute__((always_inline)) {
		write(UBRRnH, baud_to_ubrr(baudrate) >> 8);
        write(UBRRnL, baud_to_ubrr(baudrate) & 0xFF);

        write(UCSRnC, (1 << UCSZ01) | (1 << UCSZ00));
        write(UCSRnB, (1 << RXEN0) | (1 << TXEN0));
	}
	
	void _send(const char byte) const __attribute__((always_inline)) {
		write(UDRn, byte);
        while (!(read(UCSRnA) & (1 << UDRE0))) {}
	}
	
	bool _available() const __attribute__((always_inline)) {
        return ((read(UCSRnA) & (1 << RXC0)));
    }

    uint8_t _read_byte() const __attribute__((always_inline)) {
        while (!this->_available()) {}
        return read(UDRn);
    }

	void write(const int addr, int val) const __attribute__((always_inline)) {
		*((volatile uint8_t *)(addr)) = val;
	}
	
	uint8_t read(const int addr) const __attribute__((always_inline)) {
		return *((volatile uint8_t *)(addr));
	}
	
	const int serial_nr;
	const int UBRRnH, UBRRnL, UCSRnA, UCSRnB, UCSRnC, UDRn;
};

#endif  // HAL_SERIAL_PORT_H_
