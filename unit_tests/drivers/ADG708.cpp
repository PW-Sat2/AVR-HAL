#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG708);

using namespace hal;
using namespace hal::libs;

struct ADG708Mock : public DigtalIOMock {
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

void set_expect(ADG708Mock& a0,
                ADG708Mock& a1,
                ADG708Mock& a2,
                ADG708Mock& en,
                uint8_t output) {
    if (output == 0xFF) {
        en.expect = 0;
        a0.expect = a1.expect = a2.expect = 0xFF;
    } else {
        en.expect = 1;
        a0.expect = hal::libs::read_bit<0>(output);
        a1.expect = hal::libs::read_bit<1>(output);
        a2.expect = hal::libs::read_bit<2>(output);
    }
}

TEST(ADG708, disable) {
    ADG708Mock a0, a1, a2, en;
    hal::ADG708 adg(a0, a1, a2, en);

    set_expect(a0, a1, a2, en, 0xFF);
    adg.disable();

    for (uint16_t x = 0; x <= 0xFF; ++x) {
        adg.select(x);
    }
}

TEST(ADG708, enabled) {
    ADG708Mock a0, a1, a2, en;
    set_expect(a0, a1, a2, en, 0xFF);

    hal::ADG708 adg(a0, a1, a2, en);

    set_expect(a0, a1, a2, en, 0);

    adg.enable();

    for (uint16_t x = 0; x < 9; ++x) {
        set_expect(a0, a1, a2, en, x);

        adg.select(x);
    }
}
