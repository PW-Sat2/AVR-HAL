#ifndef HAL_PERIPH_DIGITALIO_PERIPHDESCRIPTORS_H_
#define HAL_PERIPH_DIGITALIO_PERIPHDESCRIPTORS_H_

struct DigitalIOPinDescriptor {
    int DDRx, PORTx, PINx;
    uint8_t pin;
};

// clang-format off
#define PIN_DEF(port, pin) {reinterpret_cast<int>(&DDR ## port),      \
                            reinterpret_cast<int>(&PORT ## port),     \
                            reinterpret_cast<int>(&PIN ## port), pin}
// clang-format on

#endif  // HAL_PERIPH_DIGITALIO_PERIPHDESCRIPTORS_H_
