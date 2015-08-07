#ifndef HAL_AVR_SPI_H_
#define HAL_AVR_SPI_H_

#include <stdint.h>
#include "GPIO.h"


class SPI_t {
private:
    GPIOPin_t pin_mosi, pin_miso, pin_sck;
public:
    struct InitTypeDef_t {
        uint8_t pin_mosi, pin_miso, pin_sck;
    };

    SPI_t();
    explicit SPI_t(SPI_t::InitTypeDef_t InitStruct);
    void init(SPI_t::InitTypeDef_t InitStruct);
	uint8_t shift(uint8_t data);
};

extern SPI_t SPI;


class SPI_Device_t {

private:

    GPIOPin_t pin_cs;
	
public:
	
	SPI_Device_t();
	
	explicit SPI_Device_t(uint8_t cs_pin);
    void enable(void);
    void disable(void);
    uint8_t shift(uint8_t data);
    uint8_t data_transfer(uint8_t data);
	void init(uint8_t cs_pin);
};

#endif  // HAL_AVR_SPI_H_
