/*
* @brief A driver for Fairchild Semiconductor FPF2700/FPF2701/FPF2702 -- AccuPower(TM) 0.4 ~ 2 A Adjustable Over-Current Protection Load Switches
* @author Grzegorz Gajoch
* @date 2015-07
*/
#ifndef DEVICES_FPF270X_H_
#define DEVICES_FPF270X_H_

#include "GPIO.h"

class LCL_t {
 private:
    GPIOPin_t pin_on, pin_flag, pin_pgood;
 public:
    struct InitTypeDef_t {
        uint8_t pin_on, pin_flag, pin_pgood;
    };
    LCL_t();
    explicit LCL_t(InitTypeDef_t InitStruct);
    void init(InitTypeDef_t InitStruct);
    void on();
    void off();
    bool overload();
    bool powergood();
};

#endif  // DEVICES_FPF270X_H_
