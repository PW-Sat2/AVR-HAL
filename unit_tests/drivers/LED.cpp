#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(LED);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

struct LEDMock : public DigtalIOMock<LEDMock> {
    static void init(const DigitalIO::Mode mode) {
        TEST_ASSERT_EQUAL(mode, DigitalIO::Mode::OUTPUT);
    }

    static uint8_t expect;

    static void toggle() {
        TEST_ASSERT_EQUAL(0xFF, expect);
    }

    static void write(bool value) {
        TEST_ASSERT_EQUAL(expect, value);
    }
};
uint8_t LEDMock::expect;

TEST(LED, write) {
    LED<LEDMock> led;
    LEDMock::expect = 0, led.write(false);
    LEDMock::expect = 1, led.write(true);
}

TEST(LED, setReset) {
    LED<LEDMock> led;
    LEDMock::expect = 0, led.write(false);
    LEDMock::expect = 1, led.on();
    LEDMock::expect = 0, led.off();
}

TEST(LED, toggle) {
    LED<LEDMock> led;
    LEDMock::expect = 0, led.write(false);
    LEDMock::expect = 0xFF, led.toggle();
    LEDMock::expect = 0xFF, led.toggle();
    LEDMock::expect = 0xFF, led.toggle();
}
