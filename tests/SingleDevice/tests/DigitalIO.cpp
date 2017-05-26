#include "tests.h"

TEST_GROUP(DigtalIO);

using namespace hal;
using namespace hal::DigitalIO;

GPIO<mcu::pin_mosi> mosi_;
Interface& mosi = mosi_;

GPIO<mcu::pin_miso> miso_;
Interface& miso = miso_;

static void reset() {
    mosi.init(Interface::Mode::INPUT);
    miso.init(Interface::Mode::INPUT);
}

TEST(DigitalIO, pullups) {
    mosi.init(Interface::Mode::INPUT);
    miso.init(Interface::Mode::INPUT_PULLUP);
    _delay_ms(10);

    TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    TEST_ASSERT_EQUAL_UINT8(true, miso.read());

    mosi.init(Interface::Mode::INPUT_PULLUP);
    miso.init(Interface::Mode::INPUT);
    _delay_ms(10);

    TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    TEST_ASSERT_EQUAL_UINT8(true, miso.read());

    reset();
}

TEST(DigitalIO, mosi_as_output) {
    miso.init(Interface::Mode::INPUT);
    mosi.init(Interface::Mode::OUTPUT);

    mosi.set();    TEST_ASSERT_EQUAL_UINT8(true,  miso.read());
    mosi.reset();  TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.write(0); TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.write(1); TEST_ASSERT_EQUAL_UINT8(true,  miso.read());
    mosi.toggle(); TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.toggle(); TEST_ASSERT_EQUAL_UINT8(true,  miso.read());

    reset();
}

TEST(DigitalIO, miso_as_output) {
    mosi.init(Interface::Mode::INPUT);
    miso.init(Interface::Mode::OUTPUT);

    miso.set();    TEST_ASSERT_EQUAL_UINT8(true,  mosi.read());
    miso.reset();  TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.write(0); TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.write(1); TEST_ASSERT_EQUAL_UINT8(true,  mosi.read());
    miso.toggle(); TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.toggle(); TEST_ASSERT_EQUAL_UINT8(true,  mosi.read());

    reset();
}

