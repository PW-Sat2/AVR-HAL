#include "tests.h"

TEST_GROUP(ADC);

using namespace hal;

using pin        = DigitalIO::GPIO<mcu::pin_sck>;
using analogGPIO = Analog::AnalogGPIO<Analog::InternalADC::Input::ADC0>;

TEST(ADC, just_pullup) {
    pin::init(DigitalIO::Mode::INPUT_PULLUP);
    Analog::InternalADC::init(Analog::InternalADC::Prescaler::DIV_128,
                              Analog::InternalADC::Reference::AVcc);

    if (analogGPIO::read() < 800) {
        TEST_FAIL();
    }
}

TEST(ADC, output) {
    pin::init(DigitalIO::Mode::OUTPUT);

    Analog::InternalADC::init(Analog::InternalADC::Prescaler::DIV_128,
                              Analog::InternalADC::Reference::AVcc);

    pin::set();
    if (analogGPIO::read() < 800) {
        TEST_FAIL();
    }

    pin::reset();
    if (analogGPIO::read() > 300) {
        TEST_FAIL();
    }
}
