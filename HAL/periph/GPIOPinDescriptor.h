#ifndef HAL_GPIO_PIN_DESCRIPTOR_H_
#define HAL_GPIO_PIN_DESCRIPTOR_H_

#include <stdint.h>

struct GPIOPinDescriptor {
    volatile uint8_t *DDRx, *PORTx, *PINx;
    uint8_t pin;
};

#endif  // HAL_GPIO_PIN_DESCRIPTOR_H_
