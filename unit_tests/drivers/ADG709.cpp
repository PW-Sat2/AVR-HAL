#include "tests.h"
#include "mocks/DigitalIO.h"

TEST_GROUP(ADG709);

using namespace hal;
using namespace hal::libs;

struct ADG709Mock : public DigtalIOMock {
    void init(const Mode mode) override {
        TEST_ASSERT_EQUAL(mode, Mode::OUTPUT);
    }

    // 0xFF for don't care
    uint8_t expect;

    void write(bool value) override {
        if (expect != 0xFF) {
            TEST_ASSERT_EQUAL(expect, value);
        }
    }
};

void set_expect(ADG709Mock& a0, ADG709Mock& a1, ADG709Mock& en, uint8_t output) {
    if (output == 0xFF) {
        en.expect = 0;
        a0.expect = a1.expect = 0xFF;
    } else {
        en.expect = 1;
        a0.expect = hal::libs::read_bit<0>(output);
        a1.expect = hal::libs::read_bit<1>(output);
    }
}

TEST(ADG709, disable) {
    ADG709Mock a0, a1, en;
    hal::ADG709 adg(a0, a1, en);

    set_expect(a0, a1, en, 0xFF);
    adg.disable();

    for (uint16_t x = 0; x <= 0xFF; ++x) {
        adg.select(x);
    }
}

TEST(ADG709, enabled) {
    ADG709Mock a0, a1, en;
    set_expect(a0, a1, en, 0xFF);

    hal::ADG709 adg(a0, a1, en);

    set_expect(a0, a1, en, 0);

    adg.enable();

    for (uint16_t x = 0; x < 4; ++x) {
        set_expect(a0, a1, en, x);

        adg.select(x);
    }
}
