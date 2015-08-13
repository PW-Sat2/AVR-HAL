/*
 * Serial.h
 *
 *  Created: 2012-12-29 02:27:29
 *  Author: Grzegorz Gajoch
 */ 

#ifndef HAL_AVR_SERIAL_H_
#define HAL_AVR_SERIAL_H_

#include <stdlib.h>
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

        REGGEN(UBRR0H) = (uint8_t) (ubrr >> 8);
        REGGEN(UBRR0L) = (uint8_t) (ubrr & 0xFF);

        /* Enable receiver and transmitter */
        REGGEN(UCSR0B) = (1 << REGGEN(RXEN0)) | (1 << REGGEN(TXEN0));
        /* Set frame format: 8data, 1stop bit */
        REGGEN(UCSR0C) = (1 << REGGEN(UCSZ01)) | (1 << REGGEN(UCSZ00));
    }

    void print(const char * out) {
        while (*out) {
            /* Wait for empty transmit buffer */
            while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
            }
            /* Put data into buffer, sends the data */
            REGGEN(UDR0) = *out;
            out++;
        }
    }
    void printf(const char* format, ...) {
        va_list aptr;
        va_start(aptr, format);
        vsnprintf(buffer, BUFFER_SIZE, format, aptr);
        va_end(aptr);

        this->print(this->buffer);
    }
    bool available() const {
        return ((REGGEN(UCSR0A) & (1 << REGGEN(RXC0))));
    }
    uint8_t read() const {
        /* Wait for data to be received */
        while (!this->available()) {
        }
        /* Get and return received data from buffer */
        return REGGEN(UDR0);
    }
};


#if SERIAL_NRs > 0
    SerialX_<0> Serial0;
#endif

#if SERIAL_NRs > 1
    SerialX_<1> Serial1;
#endif

#if SERIAL_NRs > 2
    SerialX_<2> Serial2;
#endif

#if SERIAL_NRs > 3
    SerialX_<3> Serial3;
#endif

#endif  //  HAL_AVR_SERIAL_H_
