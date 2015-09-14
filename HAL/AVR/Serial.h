/*
 * Serial.h
 *
 *  Created: 2012-12-29 02:27:29
 *  Author: Grzegorz Gajoch
 */ 

#ifndef HAL_AVR_SERIAL_H_
#define HAL_AVR_SERIAL_H_

#include <stdlib.h>
#include <stdio.h>
#include "GPIO.h"
#include "pins.h"
#include "serial_mcu.h"

const uint8_t BUFFER_SIZE = 50;


template <int SERIALNUM>
struct SerialX_ {
    char buffer[BUFFER_SIZE];

    void begin(const uint32_t _b) {
        /* Set baud rate */
        uint16_t ubrr;
        ubrr = static_cast<uint16_t>(((F_CPU / 16.)/ (_b)) - 0.5);

        REGGEN(UBRR0H) = static_cast<uint8_t> (ubrr >> 8);
        REGGEN(UBRR0L) = static_cast<uint8_t> (ubrr & 0xFF);

        /* Enable receiver and transmitter */
        REGGEN(UCSR0B) = (1 << REGGEN(RXEN0)) | (1 << REGGEN(TXEN0));
        /* Set frame format: 8data, 1stop bit */
        REGGEN(UCSR0C) = (1 << REGGEN(UCSZ01)) | (1 << REGGEN(UCSZ00));
    }

    void print_byte(const uint8_t byte) {
        /* Put data into buffer, sends the data */
        REGGEN(UDR0) = byte;
        /* Wait for empty transmit buffer */
        while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
        }
    }
    void print_byte_array(const uint8_t * data, uint8_t len) {
        while (len--) {
            this->print_byte(*data);
            data++;
        }
    }
    void print_string(const char * data) {
        while (*data) {
            this->print_byte(*data);
            data++;
        }
    }
    void printf(const char* format, ...) {
        va_list aptr;
        va_start(aptr, format);
        vsnprintf(buffer, BUFFER_SIZE, format, aptr);
        va_end(aptr);

        this->print_string(this->buffer);
    }
    bool available() {
        return ((REGGEN(UCSR0A) & (1 << REGGEN(RXC0))));
    }
    uint8_t read_byte() {
        /* Wait for data to be received */
        while (!this->available()) {
        }
        /* Get and return received data from buffer */
        return REGGEN(UDR0);
    }
    void read_byte_array(uint8_t * out_data, uint8_t length) {
        while (length--) {
            (*out_data) = this->read_byte();
            out_data++;
        }
    }
    uint8_t read_byte_array_until_term(uint8_t * out_data, const uint8_t terminator, uint8_t max_length) {
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


#if SERIAL_NRs > 0
    static SerialX_<0> Serial0;
#endif

#if SERIAL_NRs > 1
    static SerialX_<1> Serial1;
#endif

#if SERIAL_NRs > 2
    static SerialX_<2> Serial2;
#endif

#if SERIAL_NRs > 3
    static SerialX_<3> Serial3;
#endif

#endif  //  HAL_AVR_SERIAL_H_
