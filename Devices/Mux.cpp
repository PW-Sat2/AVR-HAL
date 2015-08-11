#include "Mux.h"

Mux_t::Mux_t() {
}

Mux_t::Mux_t(Mux_t::InitTypeDef_t InitStruct) {
    this->init(InitStruct);
}

void Mux_t::init(InitTypeDef_t InitStruct) {
    this->A0.init({InitStruct.pin_A0, GPIOPin_t::output});
    this->A1.init({InitStruct.pin_A1, GPIOPin_t::output});
    this->EN.init({InitStruct.pin_EN, GPIOPin_t::output});
    this->disable();
}

void Mux_t::enable() {
    this->EN.write(1);
}

void Mux_t::disable() {
    this->EN.write(0);
}

void Mux_t::select(uint8_t channel) {
    this->A0.write(static_cast<bool>(channel & 0b01));
    this->A1.write(static_cast<bool>(channel & 0b10));
}


