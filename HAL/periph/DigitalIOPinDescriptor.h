#ifndef HAL_PERIPH_DIGITALIOPINDESCRIPTOR_H_
#define HAL_PERIPH_DIGITALIOPINDESCRIPTOR_H_

#include <stdint.h>

struct DigitalIOPinDescriptor {
    int DDRx, PORTx, PINx;
    uint8_t pin;
};

#endif  // HAL_PERIPH_DIGITALIOPINDESCRIPTOR_H_
