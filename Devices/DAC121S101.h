/*
 * DAC121S101.h
 *
 * Created: 2016-05-08 19:29:59
 *  Author: Piotr Kuligowski
 */ 

#ifndef DAC121S101_H_
#define DAC121S101_H_

#include "SPI.h"
#include "GPIO.h"

class DAC121S101_t {
 public:
	 enum DAC_Mode {
		 NORMAL_OPERATION = 0,
		 POWER_DOWN_1K_TO_GND = 1,
		 POWER_DOWN_100K_TO_GND = 2,
		 POWER_DOWN_HIGH_IMPEDANCE = 3
	 };

    /*
     * @brief Initialization of the device with selected CS_PIN.
     * @param InitStruct: Contains all information needed for device initialization.
     * @retval None
     */
    void init(uint8_t cs_pin);

    /*
     * @brief Set DAC's output value.
     * @param value: New value at output. Range 0-4095.
     * @retval None
     */
    void setOutput(uint16_t value);
	
	/*
     * @brief Set mode of operation.
     * @param mode: New mode.
     * @retval None
     */
	void setMode(DAC_Mode mode);
	
	explicit DAC121S101_t();
	
 private:
	 DAC_Mode actual_mode;
	 GPIOPin_t cs_dac;
};

#endif /* DAC121S101_H_ */