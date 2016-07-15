#ifndef HAL_INC_SERIAL_H_
#define HAL_INC_SERIAL_H_

#include <stdlib.h>
#include <stdio.h>

#include "mcu/mcu.h"

constexpr static int BUFFER_SIZE = 50;

template<int serial_num>
class SerialX_ : public SerialImpl<serial_num> {
public:
	
    static char buffer[BUFFER_SIZE];

    void init(const uint32_t baudrate) const __attribute__((always_inline)) {
		this->_init(baudrate);
    }

    void print_byte(const uint8_t byte) const __attribute__((always_inline)) {
        this->_send(byte);
    }

    void print_byte_array(const uint8_t * data, uint8_t len) const {
        while (len--) {
            this->print_byte(*data);
            data++;
        }
    }

    void print_string(const char * data) const __attribute__((always_inline)) {
        while (*data) {
            this->print_byte(*data);
            data++;
        }
    }

    void printf(const char* format, ...) const {
        va_list aptr;
        va_start(aptr, format);
        vsnprintf(buffer, BUFFER_SIZE, format, aptr);
        va_end(aptr);

        this->print_string(buffer);
    }

    bool available() const __attribute__((always_inline)) {
		return this->_available();
    }

    uint8_t read_byte() const __attribute__((always_inline)) {
		return this->_read_byte();
    }

    void read_byte_array(uint8_t * out_data, uint8_t length) const {
        while (length--) {
            (*out_data) = this->read_byte();
            out_data++;
        }
    }

    uint8_t read_byte_array_until_term(uint8_t * out_data, const uint8_t terminator, uint8_t max_length) const {
        uint8_t counter = 0;
        while (max_length--) {
            uint8_t now = this->read_byte();
            (*out_data) = now;
            out_data++;
            counter++;
            if ( now == terminator ) {
                break;
            }
        }
        return counter;
    }
};
template<int serial_num>
char SerialX_<serial_num>::buffer[] = {0};

#endif  //  HAL_INC_SERIAL_H_