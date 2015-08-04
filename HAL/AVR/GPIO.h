#ifndef HAL_AVR_GPIO_H_
#define HAL_AVR_GPIO_H_

#include <stdint.h>



struct GPIOPinDescr_t {
    volatile uint8_t *DDRx, *PORTx, *PINx;
    uint8_t pin;
};

class GPIOPin_t {
private:
    GPIOPinDescr_t pin_reg;
public:
    enum  GPIO_Mode {
        input,
        output,
        input_pullup
    };
    struct InitTypeDef_t {
        uint8_t pin_nr;
        GPIO_Mode mode;
    };
    GPIOPin_t();
    explicit GPIOPin_t(GPIOPin_t::InitTypeDef_t InitStruct);
    void init(GPIOPin_t::InitTypeDef_t InitStruct);

    void set();
    void reset();
    void write(bool value);
    bool read();
};


#endif  // HAL_AVR_GPIO_H_
