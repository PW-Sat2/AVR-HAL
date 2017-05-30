#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(LED);

using namespace hal;
using namespace hal::libs;

struct LEDMock : public DigtalIOMock {
    void init(const Mode mode) override {
        TEST_ASSERT_EQUAL(mode, Mode::OUTPUT);
    }

    uint8_t expect;

    void toggle() override {
        TEST_ASSERT_EQUAL(0xFF, expect);
    }

    void write(bool value) override {
        TEST_ASSERT_EQUAL(expect, value);
    }
};

TEST(LED, write) {
    LEDMock mock;
    LED led{mock};
    mock.expect = 0, led.write(false);
    mock.expect = 1, led.write(true);
}

TEST(LED, setReset) {
    LEDMock mock;
    LED led{mock};
    mock.expect = 0, led.write(false);
    mock.expect = 1, led.on();
    mock.expect = 0, led.off();
}

TEST(LED, toggle) {
    LEDMock mock;
    LED led{mock};
    mock.expect = 0, led.write(false);
    mock.expect = 0xFF, led.toggle();
    mock.expect = 0xFF, led.toggle();
    mock.expect = 0xFF, led.toggle();
}
