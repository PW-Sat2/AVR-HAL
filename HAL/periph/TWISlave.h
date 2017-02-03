#ifndef HAL_PERIPH_TWISLAVE_H_
#define HAL_PERIPH_TWISLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "array.h"
#include "mcu.h"

#include "board.h"
#include "Serial.h"

namespace hal {

extern "C" void TWI_vect();

class TWISlave {
 public:
    TWISlave() = delete;
    ~TWISlave() = delete;
    // static_assert(address < 128, "I2C address have to be lower than 128!");

    static void init(uint8_t address) {
        DigitalIO pin_sda { mcu::pin_sda }, pin_scl { mcu::pin_scl };

        pin_sda.init(DigitalIO::INPUT_PULLUP);
        pin_scl.init(DigitalIO::INPUT_PULLUP);

        TWAR = (address << 1);
        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    }

    static void disable() {
        TWCR = 0;
    }

    static volatile uint8_t tx_buffer_cnt;
    static volatile uint8_t tx_buffer[200];

    static volatile uint8_t rx_buffer_cnt;
    static volatile uint8_t rx_buffer[200];

 private:
    friend void TWI_vect();
    static void callbackRx();
    static void callbackTx();
};

volatile uint8_t TWISlave::tx_buffer_cnt;
volatile uint8_t TWISlave::tx_buffer[200];

volatile uint8_t TWISlave::rx_buffer_cnt;
volatile uint8_t TWISlave::rx_buffer[200];

ISR(TWI_vect) {
    volatile uint8_t twsr = (TWSR & 0xF8);
    char now = TWDR;

    switch (twsr) {
    case TW_SR_SLA_ACK:
        TWISlave::rx_buffer_cnt = 0;
        break;
    case TW_SR_DATA_ACK:
        // [TODO]: implement buffer overflow and sending NACK
        TWISlave::rx_buffer[TWISlave::rx_buffer_cnt++] = now;
        break;
    case TW_SR_STOP:
        TWISlave::callbackRx();
        break;

    case TW_ST_SLA_ACK:
        TWISlave::tx_buffer_cnt = 0;
        [[fallthrough]];
    case TW_ST_DATA_ACK:
        // [TODO]: implement buffer overflow checking
        TWDR = TWISlave::tx_buffer[TWISlave::tx_buffer_cnt++];
        break;
    case TW_ST_DATA_NACK:
        TWISlave::callbackTx();
        break;

    default:
        // unexpected situation. should be checked!
        cli();
        hal::Serial0.print_string("TWI Slave error!\r\n");
        while (true) {
            hal::Serial0.print_byte(twsr);
        }
    }

    TWCR |= (1 << TWINT);
}

}  // namespace hal

#endif  // HAL_PERIPH_TWISLAVE_H_
