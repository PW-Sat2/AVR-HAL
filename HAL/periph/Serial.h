#ifndef HAL_PERIPH_SERIAL_H_
#define HAL_PERIPH_SERIAL_H_

#include <stdlib.h>
#include <stdio.h>

#include "mcu/mcu.h"

template<int serial_num>
class SerialX_ : public SerialImpl<serial_num> {
public:
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

private:
    constexpr static int BUFFER_SIZE = 50;
    static char buffer[BUFFER_SIZE];

    void print_buffer() const {
        this->print_string(buffer);
    }
};

template<int serial_num>
char SerialX_<serial_num>::buffer[] = {0};

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

#endif  //  HAL_PERIPH_SERIAL_H_
