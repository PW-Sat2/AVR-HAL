#include "FPF270x.h"

LCL_t::LCL_t() {
}

LCL_t::LCL_t(const InitTypeDef_t & InitStruct) {
    this->init(InitStruct);
}

void LCL_t::init(const LCL_t::InitTypeDef_t & InitStruct) {
    this->pin_on.init({InitStruct.pin_on, GPIOPin_t::output});
    this->pin_flag.init({InitStruct.pin_flag, GPIOPin_t::input_pullup});
    this->pin_pgood.init({InitStruct.pin_pgood, GPIOPin_t::input_pullup});
}

void LCL_t::on() {
    this->pin_on.reset();
}

void LCL_t::off() {
    this->pin_on.set();
}

bool LCL_t::overload() {
    return this->pin_flag.read();
}

bool LCL_t::powergood() {
    return this->pin_pgood.read();
}
