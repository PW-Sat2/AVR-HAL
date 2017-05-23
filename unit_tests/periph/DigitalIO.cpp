#include <hal/hal>

#include "tests.h"

using namespace hal;

template<int pin_>
struct PinTest {
    volatile uint8_t& DDRx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].DDRx);
    volatile uint8_t& PORTx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].PORTx);
    volatile uint8_t& PINx = *(volatile uint8_t*)(hal::mcu::DigitalIOPinMap[pin_].PINx);
    int pin = hal::mcu::DigitalIOPinMap[pin_].pin;
};

TEST_GROUP(DigitalIO);

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

#define CHECK_DDR(ddr_val) \
        TEST_ASSERT_BIT_## ddr_val(pinTest.pin, pinTest.DDRx);

    pin.init(DigitalIO::Interface::Mode::INPUT);
    CHECK_DDR(LOW);
    pin.set(); CHECK_DDR(LOW);
    pin.reset(); CHECK_DDR(LOW);
    pin.write(false); CHECK_DDR(LOW);
    pin.write(true); CHECK_DDR(LOW);
    pin.toggle(); CHECK_DDR(LOW);
    pin.read(); CHECK_DDR(LOW);

    pin.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    CHECK_DDR(LOW);
    pin.set(); CHECK_DDR(LOW);
    pin.reset(); CHECK_DDR(LOW);
    pin.write(false); CHECK_DDR(LOW);
    pin.write(true); CHECK_DDR(LOW);
    pin.toggle(); CHECK_DDR(LOW);
    pin.read(); CHECK_DDR(LOW);

    pin.init(DigitalIO::Interface::Mode::OUTPUT);
    CHECK_DDR(HIGH);
    pin.set(); CHECK_DDR(HIGH);
    pin.reset(); CHECK_DDR(HIGH);
    pin.write(false); CHECK_DDR(HIGH);
    pin.write(true); CHECK_DDR(HIGH);
    pin.toggle(); CHECK_DDR(HIGH);
    pin.read(); CHECK_DDR(HIGH);

#undef CHECK_DDR
}
