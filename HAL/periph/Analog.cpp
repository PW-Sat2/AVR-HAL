#include "Analog.h"

void (*hal::InternalADC::handler)(int) = nullptr;

ISR(ADC_vect) {
    hal::InternalADC::handler(ADC);
}
