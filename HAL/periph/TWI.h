#ifndef HAL_PERIPH_TWI_H_
#define HAL_PERIPH_TWI_H_

#include <avr/io.h>
#include <util/twi.h>
#include "mcu.h"
#include "DigitalIO.h"
#include "I2C.h"

namespace hal {

class TWI : public I2C_Base {
 public:
    static void init(uint32_t frequency) {
        speed(frequency);
        TWCR = (1 << TWEN);
    }

    static void enable_internal_pullups() {
        DigitalIO pin_scl{mcu::pin_scl}, pin_sda{mcu::pin_sda};
        pin_scl.init(hal::DigitalIO::INPUT_PULLUP);
        pin_sda.init(hal::DigitalIO::INPUT_PULLUP);
    }

    static void disable() {
        TWCR = 0;
    }

    static void speed(const uint32_t frequency) {
        TWSR = 0;
        uint8_t calc_TWBR = ((F_CPU/frequency)-16)/2;
        if (calc_TWBR <= 10) {
            calc_TWBR = 36;
        }
        TWBR = calc_TWBR;
    }

    static bool start(uint8_t address, const StartAction_t start_action) {
        uint8_t twst;
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        wait_for_finish();
        twst = TW_STATUS;
        if ((twst != TW_START) && (twst != TW_REP_START)) {
            return false;
        }
        TWDR = (address << 1) | start_action;
        TWCR = (1 << TWINT) | (1 << TWEN);
        wait_for_finish();
        twst = TW_STATUS;
        if (((start_action == StartAction_t::START_READ) && (twst != TW_MR_SLA_ACK)) ||
            ((start_action == StartAction_t::START_WRITE) && (twst != TW_MT_SLA_ACK))) {
            return false;
        }
        return true;
    }

    static void stop(void) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
        while (TWCR & (1 << TWSTO)) {}
    }

    static bool write(const uint8_t data) {
        TWDR = data;
        TWCR = (1 << TWINT) | (1 << TWEN);
        wait_for_finish();
        uint8_t twst = TW_STATUS;
        if (twst != TW_MT_DATA_ACK) {
            return 1;
        }

        return 0;
    }

    static void write(const uint8_t * data, uint8_t len) {
        while(len--) {
            write(*data);
            data++;
        }
    }

    static uint8_t read(Acknowledge_t ACK) {
        TWCR =  (1 << TWINT) | (1 << TWEN) | (ACK << TWEA);
        wait_for_finish();
        return TWDR;
    }

    static void read(uint8_t * data, uint8_t len, Acknowledge_t last_byte_ACK) {
        len--;
        while(len--) {
            *data = read(ACK);
            data++;
        }
        *data = read(last_byte_ACK);
    }

 private:
    static void wait_for_finish() {
        while (read_bit(TWCR, TWINT) == false) {}
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_TWI_H_
