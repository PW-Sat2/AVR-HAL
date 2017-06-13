#include "tests.h"

TEST_GROUP(DigtalIO);

using namespace hal;
using namespace hal::DigitalIO;

using mosi = GPIO<mcu::pin_mosi>;
using miso = GPIO<mcu::pin_miso>;

static void reset() {
    mosi.init(Mode::INPUT);
    miso.init(Mode::INPUT);
}

TEST(DigitalIO, pullups) {
    mosi.init(Mode::INPUT);
    miso.init(Mode::INPUT_PULLUP);
    _delay_ms(10);

    TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    TEST_ASSERT_EQUAL_UINT8(true, miso.read());

    mosi.init(Mode::INPUT_PULLUP);
    miso.init(Mode::INPUT);
    _delay_ms(10);

    TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    TEST_ASSERT_EQUAL_UINT8(true, miso.read());

    reset();
}

TEST(DigitalIO, mosi_as_output) {
    miso.init(Mode::INPUT);
    mosi.init(Mode::OUTPUT);

    mosi.set(), TEST_ASSERT_EQUAL_UINT8(true, miso.read());
    mosi.reset(), TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.write(0), TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.write(1), TEST_ASSERT_EQUAL_UINT8(true, miso.read());
    mosi.toggle(), TEST_ASSERT_EQUAL_UINT8(false, miso.read());
    mosi.toggle(), TEST_ASSERT_EQUAL_UINT8(true, miso.read());

    reset();
}

TEST(DigitalIO, miso_as_output) {
    mosi.init(Mode::INPUT);
    miso.init(Mode::OUTPUT);

    miso.set(), TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    miso.reset(), TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.write(0), TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.write(1), TEST_ASSERT_EQUAL_UINT8(true, mosi.read());
    miso.toggle(), TEST_ASSERT_EQUAL_UINT8(false, mosi.read());
    miso.toggle(), TEST_ASSERT_EQUAL_UINT8(true, mosi.read());

    reset();
}
