/*
 * DAC121S101.cpp
 *
 * Created: 2016-05-08 19:29:50
 *  Author: Piotr Kuligowski
 */ 

#include "DAC121S101.h"

DAC121S101_t::DAC121S101_t() {
}

void DAC121S101_t::init(uint8_t cs_pin){
	this->cs_dac.init({cs_pin, GPIOPin_t::output});
	this->cs_dac.set();	
	
	this->setMode(POWER_DOWN_100K_TO_GND);
	this->setOutput(0);
}

void DAC121S101_t::setOutput(uint16_t value){
	static uint8_t	l_byte, h_byte, mask;
	
	SPI.init({SPI_t::SPI_idle_high, SPI_t::SPI_leading_sample, SPI_t::SPI_MSB_First, SPI_t::SPI_Clk_Div_4});
	
	mask = 0xFF;
	h_byte = static_cast<uint8_t>((value >> 8) & mask);
	
	mask = 0x0F;
	h_byte = h_byte & mask;
	
	if (this->actual_mode == POWER_DOWN_1K_TO_GND)
		mask = 1;
	else if (this->actual_mode == POWER_DOWN_100K_TO_GND)
		mask = 2;
	else if (this->actual_mode == POWER_DOWN_HIGH_IMPEDANCE)
		mask = 3;
	else
		mask = 0;
		
	h_byte = h_byte | (mask << 4);
	
	mask = 0xFF;
	l_byte = static_cast<uint8_t>(value & mask);
	
	this->cs_dac.reset();
	SPI.shift(h_byte);
	SPI.shift(l_byte);
	this->cs_dac.set();
}

void DAC121S101_t::setMode(DAC_Mode mode){
	actual_mode = mode;
}