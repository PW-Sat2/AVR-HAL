/*
 * main.cpp
 *
 * Created: 2016-05-08 14:01:02
 * Author : Piotr Kuligowski
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "Serial.h"

#include "DAC121S101.h"

DAC121S101_t DAC121;
uint16_t dac_value=0;

#define MPPT_DAC_CS 5

int main(void)
{
    Serial0.begin(9600);
	
	DAC121.init(MPPT_DAC_CS);
	DAC121.setMode(DAC121S101_t::NORMAL_OPERATION);
	
	while(1) {
		DAC121.setOutput(dac_value);
		Serial0.printf("DAC = %u\n", dac_value);
		
		dac_value = dac_value + 128;
		
		if(dac_value>4095)
			dac_value = 4095;
		
		_delay_ms(1000);
	}
}
