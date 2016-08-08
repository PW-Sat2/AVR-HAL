/*
 * Example of multi-channel readings from Analog Devices AD7714 Analog-to-Digital converter.
 * Author: Micha³ Gumiela
 */ 

#if __AVR__
#include <avr/io.h>
#endif

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "GPIO.h"
#include "AD7714.h"
#include "Serial.h"

int main(void) {
    Serial1.begin(9600);

    SPI.init({SPI_t::SPI_idle_low, SPI_t::SPI_trailing_sample, SPI_t::SPI_MSB_First, SPI_t::SPI_Clk_Div_128});

    AD7714_t SUPER_ADC({36, 37, 33, 34, 35});
    SUPER_ADC.power_mode(AD7714_t::ON);
    SUPER_ADC.buffer(AD7714_t::ON);

    while (1) {
        SUPER_ADC.changeChannel(AD7714_t::AIN1_2_CH);
        SUPER_ADC.setFilter(AD7714_t::unipolar, AD7714_t::Data_24bit, 20);
        SUPER_ADC.writeToModeReg(AD7714_t::SelfCalib, AD7714_t::Gain_1);

        // Now you may read this channel in loop if you wish. Or just take one sample.
        uint32_t data_AIN1_2_CH = SUPER_ADC.read_data();

        /* -------------------------------------------- */

        SUPER_ADC.changeChannel(AD7714_t::AIN3_4_CH);
        SUPER_ADC.setFilter(AD7714_t::unipolar, AD7714_t::Data_24bit, 20);
        SUPER_ADC.writeToModeReg(AD7714_t::SelfCalib, AD7714_t::Gain_1);

        // Now you may read this channel in loop if you wish. Or just take one sample.
        uint32_t data_AIN3_4_CH = SUPER_ADC.read_data();

        /* -------------------------------------------- */

        Serial1.printf("AIN1_2_CH: %lu; AIN3_4_CH: %lu\r\n", data_AIN1_2_CH, data_AIN3_4_CH);
    }
}


