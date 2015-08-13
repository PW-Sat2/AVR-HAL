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

    void begin(uint32_t _b) {
        /* Set baud rate */
        uint16_t ubrr;
        ubrr = static_cast<uint16_t>((
               static_cast<float>(
               static_cast<float>(F_CPU / 16.)/ (_b))) - 0.5);

        UBRR0H = static_cast<uint8_t>(ubrr >> 8);
        UBRR0L = static_cast<uint8_t>(ubrr);
        REGGEN(UBRR0H) = (uint8_t) (ubrr >> 8);
        REGGEN(UBRR0L) = (uint8_t) ubrr;

        /* Enable receiver and transmitter */
        REGGEN(UCSR0B) = (1 << REGGEN(RXEN0)) | (1 << REGGEN(TXEN0));
        /* Set frame format: 8data, 1stop bit */
        REGGEN(UCSR0C) = (1 << REGGEN(UCSZ01)) | (1 << REGGEN(UCSZ00));
    }
    void newline() {
        this->put((uint8_t) '\r');
        this->put((uint8_t) '\n');
    }

    void put(uint8_t data) {
        while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
        }
        REGGEN(UDR0) = data;
    }
    void put(char data) {
        while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
        }
        REGGEN(UDR0) = data;
    }
    void print(char data) {
        this->put(data);
    }
    void println(char data) {
        this->put(data);
        this->newline();
    }
    void print(uint8_t data) {
        this->put(data);
    }
    void println(uint8_t data) {
        this->put(data);
        this->newline();
    }
    void print(char * out) {
        while (*out) {
            /* Wait for empty transmit buffer */
            while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
            }
            /* Put data into buffer, sends the data */
            REGGEN(UDR0) = *out;
            out++;
        }
    }
    void print(char * out, uint16_t len) {
        uint8_t i = 0;
        while (i != len) {
            /* Wait for empty transmit buffer */
            while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0)))) {
            }
            /* Put data into buffer, sends the data */
            REGGEN(UDR0) = *out;
            ++out;
            ++i;
        }
    }
    void println(char * out) {
        this->print(out);
        this->newline();
    }
    void print(uint16_t data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
    }
    void print(int data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
    }
    void println(int16_t data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
        this->newline();
    }
    void println(uint16_t data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
        this->newline();
    }
    void print(uint32_t data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
    }
    void print(int32_t data) {
        sprintf(this->buffer, "%ld", data);
        this->print(this->buffer);
    }
    void println(int32_t data) {
        sprintf(this->buffer, "%ld", data);
        this->print(this->buffer);
        this->newline();
    }
    void println(uint32_t data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
        this->newline();
    }
    void print(float data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
    }
    void println(float data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
        this->newline();
    }
    void print(double data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
    }
    void println(double data) {
        itoa(data, this->buffer, 10);
        this->print(this->buffer);
        this->newline();
    }
    bool available() {
        return ((REGGEN(UCSR0A) & (1 << REGGEN(RXC0)))) {
        }
    }
    uint8_t read() {
        /* Wait for data to be received */
        while (!(REGGEN(UCSR0A) & (1 << REGGEN(RXC0)))) {
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
