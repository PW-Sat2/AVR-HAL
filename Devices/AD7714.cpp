/*
 * AD7714.cpp
 *
 * Created: 2015-07-30 17:43:59
 *  Author: begreen
 */ 

#include <util/delay.h>
#include "GPIO.h"
#include "SPI.h"
#include "AD7714.h"

SPI_Device_t AD7714_SPI;

AD7714_t::AD7714_t() {
}

AD7714_t::AD7714_t(AD7714_t::InitTypeDef_t InitStruct) {
    this->init(InitStruct);
}


uint8_t AD7714_t::changeChannel(ADC_Channels channel) {
    actual_channel = channel;
    writeToCommReg(COMM_REG, true);
    this->waitForDRDY();
    return AD7714_SPI.data_transfer(0);
}


bool AD7714_t::data_available(void) {
    return (!(this->DRDY_pin.read()));
}

void AD7714_t::waitForDRDY(void) {
    while (!data_available()) {}
}


void AD7714_t::init(AD7714_t::InitTypeDef_t InitStruct) {
    this->AD7714_SPI.init(InitStruct.CS_pin_nr);

    this->DRDY_pin.init({InitStruct.DRDY_pin_nr, GPIOPin_t::input});
    this->RESET_pin.init({InitStruct.RESET_pin_nr, GPIOPin_t::output});
    this->STANDBY_pin.init({InitStruct.STANDBY_pin_nr, GPIOPin_t::output});
    this->BUFFER_pin.init({InitStruct.BUFFER_pin_nr, GPIOPin_t::output});

    this->reset();
    this->buffer(ON);
    this->power_mode(OFF);
}

void AD7714_t::reset(void) {
    this->RESET_pin.reset();
    _delay_ms(10);
    this->RESET_pin.set();
    _delay_ms(10);
}

void AD7714_t::power_mode(Control_State status) {
    STANDBY_pin.write(static_cast<bool>(status));
    _delay_ms(10);
}

void AD7714_t::buffer(Control_State buff_stat) {
    BUFFER_pin.write(static_cast<bool>(buff_stat));
}

void AD7714_t::writeToCommReg(ADC_Registers reg, bool read) {
    uint8_t out = (reg << 4) | (read << 3) | (actual_channel);
    AD7714_SPI.data_transfer(out);
}

uint32_t AD7714_t::read_data() {
    waitForDRDY();
    writeToCommReg(DATA_REG, true);
    AD7714_SPI.enable();
    uint32_t tmp = AD7714_SPI.shift(0);

    uint32_t read = 0;

    if ( dataLen == Data_16bit ) {
        read = (tmp << 8);
        tmp = AD7714_SPI.shift(0);
        read |= (tmp);
        } else {
        read = (tmp << 16);
        tmp = AD7714_SPI.shift(0);
        read |= (tmp << 8);
        tmp = AD7714_SPI.shift(0);
        read |= (tmp);
    }

    AD7714_SPI.disable();

    return read;
}

void AD7714_t::writeToModeReg(ADC_Modes mode, ADC_Gain gain) {
    writeToCommReg(MODE_REG, false);
    uint8_t data = (mode << 5) | (gain << 2);
    AD7714_SPI.data_transfer(data);
    this->waitForDRDY();
}


void AD7714_t::setFilter(Polarity set_polarity, DataLength data_length, uint16_t filter) {
    //  filter: 19-4000
    //  f notch = fclk/128/filter
    dataLen = data_length;
    writeToCommReg(FILTER_HIGH_REG, false);
    uint8_t val = (static_cast<bool>(set_polarity) << 7) | (data_length << 6) | (1 << 5) | (filter >> 8);
    AD7714_SPI.data_transfer(val);
    writeToCommReg(FILTER_LOW_REG, false);
    val = (filter & 0xFF);
    AD7714_SPI.data_transfer(val);
}
