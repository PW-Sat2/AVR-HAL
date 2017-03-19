#ifndef HAL_PERIPH_GPIO_PERIPHDESCRIPTORS_H_
#define HAL_PERIPH_GPIO_PERIPHDESCRIPTORS_H_

struct DigitalIOPinDescriptor {
    int DDRx, PORTx, PINx;
    uint8_t pin;
};

#endif  // HAL_PERIPH_GPIO_PERIPHDESCRIPTORS_H_
