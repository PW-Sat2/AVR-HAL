#include "FPF270x.h"

FPF270x_t::FPF270x_t() {
}

FPF270x_t::FPF270x_t(const InitTypeDef_t & InitStruct) {
    this->init(InitStruct);
}

void FPF270x_t::init(const FPF270x_t::InitTypeDef_t & InitStruct) {
    this->pin_on.init({InitStruct.pin_on, GPIOPin_t::output});
    this->pin_flag.init({InitStruct.pin_flag, GPIOPin_t::input_pullup});
    this->pin_pgood.init({InitStruct.pin_pgood, GPIOPin_t::input_pullup});
}

void FPF270x_t::on() {
    this->pin_on.reset();
}

void FPF270x_t::off() {
    this->pin_on.set();
}

bool FPF270x_t::error_occured() {
    return this->pin_flag.read();
}

bool FPF270x_t::powergood() {
    return this->pin_pgood.read();
}
