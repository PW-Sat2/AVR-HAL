#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG709);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

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
    ADG709 adg(a0, a1, en);

    set_expect(a0, a1, en, 0xFF);
    adg.disable();
    
    adg.select(ADG709::Channel::S1);
    adg.select(ADG709::Channel::S2);
    adg.select(ADG709::Channel::S3);
    adg.select(ADG709::Channel::S4);
}

TEST(ADG709, enabled) {
    ADG709Mock a0, a1, en;
    set_expect(a0, a1, en, 0xFF);

    ADG709 adg(a0, a1, en);

    set_expect(a0, a1, en, 0);

    adg.enable();

    set_expect(a0, a1, en,static_cast<uint8_t>(ADG708::Channel::S1));
    adg.select(ADG709::Channel::S1);

    set_expect(a0, a1, en,static_cast<uint8_t>(ADG708::Channel::S2));
    adg.select(ADG709::Channel::S2);

    set_expect(a0, a1, en,static_cast<uint8_t>(ADG708::Channel::S3));
    adg.select(ADG709::Channel::S3);

    set_expect(a0, a1, en,static_cast<uint8_t>(ADG708::Channel::S4));
    adg.select(ADG709::Channel::S4);
}
