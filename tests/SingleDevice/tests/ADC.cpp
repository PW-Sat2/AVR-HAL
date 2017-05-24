#include "tests.h"

TEST_GROUP(ADC);

using namespace hal;

DigitalIO::GPIO<mcu::pin_sck> pin;

TEST(ADC, just_pullup) {
    pin.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    Analog::InternalADC::init(Analog::InternalADC::Prescaler::DIV_128,
                              Analog::InternalADC::Reference::AVcc);
    Analog::AnalogGPIO analogGPIO(Analog::InternalADC::Input::ADC0);

    if (analogGPIO.read() < 800) {
        TEST_FAIL();
    }
}

TEST(ADC, output) {
    pin.init(DigitalIO::Interface::Mode::OUTPUT);

    Analog::InternalADC::init(Analog::InternalADC::Prescaler::DIV_128,
                              Analog::InternalADC::Reference::AVcc);
    Analog::AnalogGPIO analogGPIO(Analog::InternalADC::Input::ADC0);

    pin.set();
    if (analogGPIO.read() < 800) {
        TEST_FAIL();
    }

    pin.reset();
    if (analogGPIO.read() > 300) {
        TEST_FAIL();
    }
}