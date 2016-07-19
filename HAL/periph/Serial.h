#ifndef HAL_PERIPH_SERIAL_H_
#define HAL_PERIPH_SERIAL_H_

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include "mcu/mcu.h"

namespace hal {

#define READ_REG(reg) (*((volatile uint8_t *)(mcu::UART_map[serial_num].reg)))
#define WRITE_REG(reg, val) (*((volatile uint8_t *)(mcu::UART_map[serial_num].reg)) = val)


template<int serial_num>
class SerialX_ {
public:
	static_assert(serial_num >= 0, "Bad Serial number!");
	static_assert(serial_num < SERIALs, "Bad Serial number!");

	void init(const uint32_t baudrate) const __attribute__((always_inline)) {
		const uint32_t ubrr = baud_to_ubrr(baudrate);
		WRITE_REG(UBRRnH, ubrr >> 8);
		WRITE_REG(UBRRnL, ubrr & 0xFF);

		WRITE_REG(UCSRnC, (1 << UCSZ01) | (1 << UCSZ00));
		WRITE_REG(UCSRnB, (1 << RXEN0) | (1 << TXEN0));
	}

	void print_byte(const char byte) const __attribute__((always_inline)) {
		WRITE_REG(UDRn, byte);
		while (!(READ_REG(UCSRnA) & (1 << UDRE0))) {
		}
	}

	bool available() const __attribute__((always_inline)) {
		return ((READ_REG(UCSRnA) & (1 << RXC0)));
	}

	uint8_t read_byte() const __attribute__((always_inline)) {
		while (!this->available()) {
		}
		return READ_REG(UDRn);
	}

	void printf(const char* format, ...) const {
		va_list aptr;
		va_start(aptr, format);
		vsnprintf(buffer, BUFFER_SIZE, format, aptr);
		va_end(aptr);

		this->print_buffer();
	}

	void print_byte_array(const uint8_t * data, uint8_t len) const {
		while (len--) {
			this->print_byte(*data);
			data++;
		}
	}

	void print_string(const char * data) const {
		while (*data) {
			this->print_byte(*data);
			data++;
		}
	}

	void read_byte_array(uint8_t * out_data, uint8_t length) const {
		while (length--) {
			(*out_data) = this->read_byte();
			out_data++;
		}
	}

	uint8_t read_byte_array_until_term(uint8_t * out_data,
			const uint8_t terminator, uint8_t max_length) const {
		uint8_t counter = 0;
		while (max_length--) {
			uint8_t now = this->read_byte();
			(*out_data) = now;
			out_data++;
			counter++;
			if (now == terminator) {
				break;
			}
		}
		return counter;
	}

private:
	constexpr static int BUFFER_SIZE = 50;
	static char buffer[BUFFER_SIZE];

	void print_buffer() const {
		this->print_string(buffer);
	}

	constexpr static uint16_t baud_to_ubrr(const uint32_t baud) {
		return (((F_CPU / 16.) / (baud)) - 0.5);
	}

};

#undef READ_REG
#undef WRITE_REG

template<int serial_num>
char SerialX_<serial_num>::buffer[] = { 0 };

#if SERIALs > 0
constexpr static SerialX_<0> Serial0;
#endif

#if SERIALs > 1
constexpr static SerialX_<1> Serial1;
#endif

#if SERIALs > 2
constexpr static SerialX_<2> Serial2;
#endif

#if SERIALs > 3
constexpr static SerialX_<3> Serial3;
#endif

}

#endif  //  HAL_PERIPH_SERIAL_H_
