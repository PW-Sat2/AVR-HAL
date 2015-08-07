#ifndef HAL_AVR_SPI_H_
#define HAL_AVR_SPI_H_

#include <stdint.h>
#include "GPIO.h"

struct SPIPinDescr_t {
    uint8_t pin_mosi, pin_miso, pin_sck, pin_ss;
};

class SPI_t {
 private:
    GPIOPin_t pin_mosi, pin_miso, pin_sck, pin_ss;

 public:
    enum SPI_Polarity {
        SPI_idle_low = 0,
        SPI_idle_high = 1
    };

    enum SPI_Phase {
        SPI_leading_sample = 0,
        SPI_trailing_sample = 1
    };

    enum SPI_DataOrder {
        SPI_MSB_First = 0,
        SPI_LSB_First = 1
    };

    enum SPI_Clock_Divisor {
        SPI_Clk_Div_4 = 0,
        SPI_Clk_Div_16 = 1,
        SPI_Clk_Div_64 = 2,
        SPI_Clk_Div_128 = 3,
    };

    struct InitTypeDef_t {
        SPI_Polarity polarity;
        SPI_Phase phase;
        SPI_DataOrder data_order;
        SPI_Clock_Divisor clk_divisor;
    };

    SPI_t();
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
