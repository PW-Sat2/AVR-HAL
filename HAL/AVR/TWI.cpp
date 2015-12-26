/*
 * TWI.cpp
 *
 * Created: 2015-12-25 01:14:16
 *  Author: Michal Gumiela
 */ 

#include <util/twi.h>
#include "GPIO.h"
#include "TWI.h"
#include "pins.h"
#include "Serial.h"

void TWI_t::init(void) {
    // Make sure that SDA and SCL are set as output
    this->SDA.init({TWIPin_t_descr.pinSDA, GPIOPin_t::output});
    this->SCL.init({TWIPin_t_descr.pinSCL, GPIOPin_t::output});

    // configure clock
    this->speed(100000UL);

    // enable TWI
    TWCR = (1 << TWEN);
}

void TWI_t::speed(uint32_t speed) {
        TWSR = 0;
        uint8_t calc_TWBR = ((F_CPU/speed)-16)/2;
        if (calc_TWBR > 10) {
            TWBR = calc_TWBR;
        } else {
            TWBR = 36;
        }
}

bool TWI_t::start(uint8_t address, const TWI_t::Action_t start_action) {
    uint8_t twst;
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {}
    twst = TW_STATUS;
    if ((twst != TW_START) && (twst != TW_REP_START)) {
        return 0;
    }
    TWDR = (address << 1) | start_action;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {}
    twst = TW_STATUS;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) {
        return 0;
    }
    return 1;
}

void TWI_t::stop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    while (TWCR & (1 << TWSTO)) {}
}

bool TWI_t::write(uint8_t data) {
    uint8_t twst;

    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))) {}

    twst = TW_STATUS;
    if (twst != TW_MT_DATA_ACK) {
        return 1;
    }

    return 0;
}

uint8_t TWI_t::read(bool ACK) {
    TWCR =  (1 << TWINT) | (1 << TWEN) | (ACK << TWEA);
    while (!(TWCR &  (1 << TWINT))) {}

    return TWDR;
}

TWI_t TWI;
