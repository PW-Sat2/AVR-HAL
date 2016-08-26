#ifndef HAL_PERIPH_TWISLAVE_H_
#define HAL_PERIPH_TWISLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "array.h"
#include "mcu.h"

#include "boards.h"
#include "Serial.h"

namespace hal {

extern "C" void TWI_vect();

class TWISlave {
public:
    TWISlave() = delete;
    ~TWISlave() = delete;
    //static_assert(address < 128, "I2C address have to be lower than 128!");

    static void init(uint8_t address, void callback(libs::array_view<uint8_t> &&)) {
        DigitalIO pin_sda { mcu::pin_sda }, pin_scl { mcu::pin_scl };

        pin_sda.init(DigitalIO::INPUT_PULLUP);
        pin_scl.init(DigitalIO::INPUT_PULLUP);

        TWISlave::callback = callback;
        TWAR = (address << 1);
        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    }

    static void disable() {
        TWCR = 0;
    }

    static libs::array<uint8_t, 100> tx_buffer;

 private:
    static uint8_t buffer_address;
    static libs::array<uint8_t, 100> rx_buffer;
    static void (*callback)(libs::array_view<uint8_t> &&);

    friend void TWI_vect();
};

uint8_t TWISlave::buffer_address;
libs::array<uint8_t, 100> TWISlave::tx_buffer;
libs::array<uint8_t, 100> TWISlave::rx_buffer;
void (*TWISlave::callback)(libs::array_view<uint8_t> &&);

ISR(TWI_vect) {
    uint8_t twsr = (TWSR & 0xF8);

    if (twsr == TW_SR_SLA_ACK) {
        TWISlave::buffer_address = 0;
    } else if (twsr == TW_SR_DATA_ACK) {
        TWISlave::rx_buffer[TWISlave::buffer_address++] = TWDR;
    } else if (twsr == TW_SR_STOP) {
        TWISlave::callback(libs::make_array_view(TWISlave::rx_buffer.data(),
                                                 TWISlave::buffer_address));
    } else if (twsr == TW_ST_SLA_ACK) {
        TWDR = TWISlave::tx_buffer[0];
        TWISlave::buffer_address = 1;
    } else if (twsr == TW_ST_DATA_ACK || twsr == TW_ST_DATA_NACK) {
        TWDR = TWISlave::tx_buffer[TWISlave::buffer_address++];
    } else {
        // unexpected situation. should be checked!
        hal::Serial0.print_string("TWI Slave error!\r\n");
        while (true) {
            hal::Serial0.print_byte(twsr);
        }
    }

    TWCR |= (1 << TWIE) | (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
}

}  // namespace hal

#endif  // HAL_PERIPH_TWISLAVE_H_
