#include <avr/io.h>

#include "tests.h"

using namespace hal;

template<int pin_>
struct PinTest {
    volatile uint8_t& DDRx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].DDRx);
    volatile uint8_t& PORTx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].PORTx);
    volatile uint8_t& PINx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].PINx);
    int pin = hal::mcu::DigitalIOPinMap[pin_].pin;
};

TEST(DigitalIO, init) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.DDRx  = 0xFF;
    pinTest.PORTx = 0xFF;
    pin.init(DigitalIO::Interface::Mode::INPUT);
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.DDRx);
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.PORTx);

    pinTest.DDRx  = 0xFF;
    pinTest.PORTx = 0x00;
    pin.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.DDRx);
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.PORTx);

    pinTest.DDRx  = 0x00;
    pinTest.PORTx = 0x00;
    pin.init(DigitalIO::Interface::Mode::OUTPUT);
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.DDRx);
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.PORTx);

    pinTest.DDRx  = 0x00;
    pinTest.PORTx = 0xFF;
    pin.init(DigitalIO::Interface::Mode::OUTPUT);
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.DDRx);
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.PORTx);
}

TEST(DigitalIO, set) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.PORTx = 0;
    pin.set();
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.PORTx);
}

TEST(DigitalIO, reset) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.PORTx = 0xFF;
    pin.reset();
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.PORTx);
}

TEST(DigitalIO, write) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.PORTx = 0xFF;
    pin.write(false);
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.PORTx);

    pinTest.PORTx = 0x00;
    pin.write(true);
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.PORTx);
}

TEST(DigitalIO, read) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.PORTx = 0xFF;
    TEST_ASSERT_EQUAL(1, pin.read());

    pinTest.PORTx = 0x00;
    TEST_ASSERT_EQUAL(0, pin.read());
}

TEST(DigitalIO, toggle) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

    pinTest.PORTx = 0xFF;
    pin.toggle();
    TEST_ASSERT_BIT_LOW(pinTest.pin, pinTest.PORTx);

    pinTest.PORTx = 0x00;
    pin.toggle();
    TEST_ASSERT_BIT_HIGH(pinTest.pin, pinTest.PORTx);
}

TEST(DigitalIO, operationsDoesNotChangeMode) {
    PinTest<hal::mcu::pin_scl> pinTest;
    DigitalIO::GPIO<hal::mcu::pin_scl> gpio;
    DigitalIO::Interface& pin{gpio};

#define CHECK(ddr_val) \
        TEST_ASSERT_BIT_## ddr_val(pinTest.pin, pinTest.DDRx);

    pin.init(DigitalIO::Interface::Mode::INPUT);
    CHECK(LOW);
    pin.set(); CHECK(LOW);
    pin.reset(); CHECK(LOW);
    pin.write(false); CHECK(LOW);
    pin.write(true); CHECK(LOW);
    pin.toggle(); CHECK(LOW);
    pin.read(); CHECK(LOW);

    pin.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    CHECK(LOW);
    pin.set(); CHECK(LOW);
    pin.reset(); CHECK(LOW);
    pin.write(false); CHECK(LOW);
    pin.write(true); CHECK(LOW);
    pin.toggle(); CHECK(LOW);
    pin.read(); CHECK(LOW);

    pin.init(DigitalIO::Interface::Mode::OUTPUT);
    CHECK(HIGH);
    pin.set(); CHECK(HIGH);
    pin.reset(); CHECK(HIGH);
    pin.write(false); CHECK(HIGH);
    pin.write(true); CHECK(HIGH);
    pin.toggle(); CHECK(HIGH);
    pin.read(); CHECK(HIGH);

#undef CHECK
}

DEFINE_TESTSUITE(DigitalIO);
