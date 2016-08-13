#ifndef HAL_PERIPH_TWISLAVE_H_
#define HAL_PERIPH_TWISLAVE_H_

#include <avr/io.h>

template<uint8_t address>
class TWISlave {
 public:
    TWISlave() = delete;
    static_assert(address < 128, "I2C address have to be lower than 128!");

    static void init() {
        TWAR = (address << 1);
        TWCR = (1 << TWEN);
    }
};



#endif  // HAL_PERIPH_TWISLAVE_H_
