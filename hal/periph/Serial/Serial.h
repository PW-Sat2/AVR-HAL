#ifndef HAL_PERIPH_SERIAL_SERIAL_H_
#define HAL_PERIPH_SERIAL_SERIAL_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "Serial_device.h"
#include "hal/mcu.h"

namespace hal {

namespace details {
template<int nr>
int uart_putchar(char x, FILE* stream);

template<int nr>
int uart_getchar(FILE* stream);
}  // namespace details

template<int nr>
class Serial {
 public:
    static_assert(nr >= 0, "Bad Serial number!");
    static_assert(nr < MCU_NR_OF_SERIALS, "Bad Serial number!");

    void init(const uint32_t baudrate) const __attribute__((always_inline)) {
        const uint16_t ubrr = baud_to_ubrr(baudrate);
        UBRRnH<nr>()        = (ubrr >> 8);
        UBRRnL<nr>()        = (ubrr & 0xFF);

        UCSRnC<nr>() = (1 << UCSZ01) | (1 << UCSZ00);
        UCSRnB<nr>() = (1 << RXEN0) | (1 << TXEN0);
    }

    void redirect_stdio() const {
        static FILE uart_output;
        uart_output.put   = details::uart_putchar<nr>;
        uart_output.get   = details::uart_getchar<nr>;
        uart_output.flags = _FDEV_SETUP_RW;
        stdout            = &uart_output;
        stdin             = &uart_output;
        stderr            = &uart_output;
    }

    void redirect_stderr() const {
        static FILE uart_output;
        uart_output.put   = details::uart_putchar<nr>;
        uart_output.flags = _FDEV_SETUP_WRITE;
        stderr            = &uart_output;
    }

    void print_byte(const char byte) const __attribute__((always_inline)) {
        UDRn<nr>() = byte;
        while (!libs::read_bit(UCSRnA<nr>(), UDRE0)) {
        }
    }

    bool available() const __attribute__((always_inline)) {
        return UCSRnA<nr>() & (1 << RXC0);
    }

    uint8_t read_byte() const __attribute__((always_inline)) {
        while (!this->available()) {
        }
        return read_byte_nowait();
    }

    uint8_t read_byte_nowait() const __attribute__((always_inline)) {
        return UDRn<nr>();
    }

    void printf(const char* format, ...) const {
        va_list aptr;
        va_start(aptr, format);
        vsnprintf(buffer, BUFFER_SIZE, format, aptr);
        va_end(aptr);

        this->print_buffer();
    }

    void print_byte_array(const uint8_t* data, uint8_t len) const {
        while (len--) {
            this->print_byte(*data);
            data++;
        }
    }

    void print_string(const char* data) const {
        while (*data) {
            this->print_byte(*data);
            data++;
        }
    }

    void read_byte_array(uint8_t* out_data, uint8_t length) const {
        while (length--) {
            (*out_data) = this->read_byte();
            out_data++;
        }
    }

    uint8_t read_byte_array_until_term(uint8_t* out_data,
                                       const uint8_t terminator,
                                       uint8_t max_length) const {
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

    void enable_rx_interrupt() const {
        UCSRnB<nr>() |= (1 << RXCIE0);
    }

 private:
    constexpr static int BUFFER_SIZE = 200;
    static char buffer[BUFFER_SIZE];

    void print_buffer() const {
        this->print_string(buffer);
    }

    constexpr static uint16_t baud_to_ubrr(const uint32_t baud) {
        return (((F_CPU / 16.) / (baud)) - 0.5);
    }
};

#if MCU_NR_OF_SERIALS > 0
constexpr Serial<0> Serial0;
#endif

#if MCU_NR_OF_SERIALS > 1
constexpr Serial<1> Serial1;
#endif

#if MCU_NR_OF_SERIALS > 2
constexpr Serial<2> Serial2;
#endif

#if MCU_NR_OF_SERIALS > 3
constexpr Serial<3> Serial3;
#endif

template<int nr>
char Serial<nr>::buffer[] = {0};

namespace details {
template<int nr>
int uart_putchar(char x, __attribute__((unused)) FILE* stream) {
#if MCU_NR_OF_SERIALS > 0
    if (nr == 0) {
        Serial0.print_byte(x);
    }
#endif

#if MCU_NR_OF_SERIALS > 1
    if (nr == 1) {
        Serial1.print_byte(x);
    }
#endif

#if MCU_NR_OF_SERIALS > 2
    if (nr == 2) {
        Serial2.print_byte(x);
    }
#endif

#if MCU_NR_OF_SERIALS > 3
    if (nr == 3) {
        Serial3.print_byte(x);
    }
#endif
    return 1;
}

template<int nr>
int uart_getchar(__attribute__((unused)) FILE* stream) {
#if MCU_NR_OF_SERIALS > 0
    if (nr == 0) {
        return Serial0.read_byte();
    }
#endif

#if MCU_NR_OF_SERIALS > 1
    if (nr == 1) {
        return Serial1.read_byte();
    }
#endif

#if MCU_NR_OF_SERIALS > 2
    if (nr == 2) {
        return Serial2.read_byte();
    }
#endif

#if MCU_NR_OF_SERIALS > 3
    if (nr == 3) {
        return Serial3.read_byte();
    }
#endif
}
}  // namespace details

}  // namespace hal

#endif  //  HAL_PERIPH_SERIAL_SERIAL_H_
