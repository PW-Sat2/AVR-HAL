/*
 * TWI.h
 *
 * Created: 2015-12-25 01:15:06
 *  Author: Michal Gumiela
 */ 


#ifndef HAL_AVR_TWI_H_
#define HAL_AVR_TWI_H_

#include <avr/io.h>
#include <stdint.h>
#include "GPIO.h"

struct TWIPinDescr_t {
    uint8_t pinSDA, pinSCL;
};

class TWI_t {
 private:
    GPIOPin_t SDA, SCL;
 public:
    enum Action_t {
        START_WRITE = 0,
        START_READ = 1
    };

    void init(void);
    void speed(const uint32_t speed);
    bool start(uint8_t address, const Action_t start_action);
    void stop(void);
    bool write(uint8_t data);
    uint8_t read(bool ACK);
};

extern TWI_t TWI;

#endif /* HAL_AVR_TWI_H_ */
