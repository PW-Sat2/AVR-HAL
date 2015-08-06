#include <avr/io.h>
#include "GPIO.h"
#include "bit_operations.h"
#include "pins.h"
#include "avr/pgmspace.h"


GPIOPin_t::GPIOPin_t() {
}

GPIOPin_t::GPIOPin_t(GPIOPin_t::InitTypeDef_t InitTypeDef) {
    this->init(InitTypeDef);
}

void GPIOPin_t::init(GPIOPin_t::InitTypeDef_t InitTypeDef) {
    this->pin_reg.pin = pgm_read_byte(&(GPIOPin_t_descr[InitTypeDef.pin_nr].pin));
    this->pin_reg.DDRx = reinterpret_cast<volatile uint8_t*>pgm_read_byte(&(GPIOPin_t_descr[InitTypeDef.pin_nr].DDRx));
    this->pin_reg.PINx = reinterpret_cast<volatile uint8_t*>pgm_read_byte(&(GPIOPin_t_descr[InitTypeDef.pin_nr].PINx));
    this->pin_reg.PORTx = reinterpret_cast<volatile uint8_t*>pgm_read_byte(&(GPIOPin_t_descr[InitTypeDef.pin_nr].PORTx));

    if (InitTypeDef.mode == input) {
        cbi((*this->pin_reg.DDRx), this->pin_reg.pin);
        cbi((*this->pin_reg.PORTx), this->pin_reg.pin);
    } else if (InitTypeDef.mode == input_pullup) {
        cbi((*this->pin_reg.DDRx), this->pin_reg.pin);
        sbi((*this->pin_reg.PORTx), this->pin_reg.pin);
    } else {
        sbi((*this->pin_reg.DDRx), this->pin_reg.pin);
        cbi((*this->pin_reg.PORTx), this->pin_reg.pin);
    }
}

void GPIOPin_t::set() {
    sbi((*this->pin_reg.PORTx), this->pin_reg.pin);
}

void GPIOPin_t::reset() {
    cbi((*this->pin_reg.PORTx), this->pin_reg.pin);
}

void GPIOPin_t::write(bool value) {
    if (value) {
        this->set();
    } else {
        this->reset();
    }
}

bool GPIOPin_t::read() {
    if (bit_is_clear((*this->pin_reg.PINx), this->pin_reg.pin)) {
        return true;
    }
    return false;
}


