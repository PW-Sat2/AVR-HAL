#include <avr/io.h>
#include "SPI.h"
#include "pins.h"

SPI_t::SPI_t() {
}


void SPI_t::init(SPI_t::InitTypeDef_t InitStruct) {
    pin_mosi.init({SPIPin_t_descr.pin_mosi, GPIOPin_t::output});
    pin_miso.init({SPIPin_t_descr.pin_miso, GPIOPin_t::input});
    pin_sck.init({SPIPin_t_descr.pin_sck, GPIOPin_t::output});
    pin_ss.init({SPIPin_t_descr.pin_ss, GPIOPin_t::output});

    SPCR = (1 << SPE) | (1 << MSTR) | (InitStruct.clk_divisor) |
           (InitStruct.phase << CPHA) | (InitStruct.polarity << CPOL) |
           (InitStruct.data_order << DORD);
}


uint8_t SPI_t::shift(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF))) {
    }
    return SPDR;
}

SPI_t SPI;


SPI_Device_t::SPI_Device_t() {
}

SPI_Device_t::SPI_Device_t(uint8_t cs_pin) {
    this->init(cs_pin);
}

void SPI_Device_t::init(uint8_t cs_pin) {
    this->pin_cs.init({cs_pin, GPIOPin_t::output});
}

void SPI_Device_t::enable() {
    this->pin_cs.reset();
}

void SPI_Device_t::disable() {
    this->pin_cs.set();
}

uint8_t SPI_Device_t::shift(uint8_t data) {
    return SPI.shift(data);
}

uint8_t SPI_Device_t::data_transfer(uint8_t data) {
    this->enable();
    uint8_t x = SPI.shift(data);
    this->disable();
    return x;
}

void SPI_Device_t::data_transfer(uint8_t *in_data, uint8_t *out_data, uint8_t len) {
    this->enable();
    uint8_t tmp;
    while(len--) {
        tmp = SPI.shift(*in_data);
        (*out_data) = tmp;
        in_data++;
        out_data++;
    }
    this->disable();
}