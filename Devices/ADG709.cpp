#include "ADG709.h"

ADG709_t::ADG709_t() {
}

ADG709_t::ADG709_t(const ADG709_t::InitTypeDef_t & InitStruct) {
    this->init(InitStruct);
}

void ADG709_t::init(const InitTypeDef_t & InitStruct const ) {
    this->A0.init({InitStruct.pin_A0, GPIOPin_t::output});
    this->A1.init({InitStruct.pin_A1, GPIOPin_t::output});
    this->EN.init({InitStruct.pin_EN, GPIOPin_t::output});
    this->disable();
}

void ADG709_t::enable() {
    this->EN.set();
}

void ADG709_t::disable() {
    this->EN.reset();
}

void ADG709_t::select(const uint8_t channel) {
    this->A0.write(static_cast<bool>(channel & 0b01));
    this->A1.write(static_cast<bool>(channel & 0b10));
}


