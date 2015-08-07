#include <avr/io.h>
#include "SPI.h"
#include "bit_operations.h"

SPI_t::SPI_t() {

}

SPI_t::SPI_t(SPI_t::InitTypeDef_t InitStruct) {
    this->init(InitStruct);
}


void SPI_t::init(SPI_t::InitTypeDef_t InitStruct) {
    pin_mosi.init({InitStruct.pin_mosi, GPIOPin_t::output});
    pin_miso.init({InitStruct.pin_miso, GPIOPin_t::input});
    pin_sck.init({InitStruct.pin_sck, GPIOPin_t::output});

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0) | (1 << CPHA);  // master, fclk = fosc/128
}


uint8_t SPI_t::shift(uint8_t data) {
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
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
