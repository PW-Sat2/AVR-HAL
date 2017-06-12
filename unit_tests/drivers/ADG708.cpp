#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG708);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

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
    ADG708 adg(a0, a1, a2, en);

    set_expect(a0, a1, a2, en, 0xFF);
    adg.disable();

    adg.select(ADG708::Channel::S1);
    adg.select(ADG708::Channel::S2);
    adg.select(ADG708::Channel::S3);
    adg.select(ADG708::Channel::S4);
    adg.select(ADG708::Channel::S5);
    adg.select(ADG708::Channel::S6);
    adg.select(ADG708::Channel::S7);
    adg.select(ADG708::Channel::S8);
}

TEST(ADG708, enabled) {
    ADG708Mock a0, a1, a2, en;
    set_expect(a0, a1, a2, en, 0xFF);

    ADG708 adg(a0, a1, a2, en);

    set_expect(a0, a1, a2, en, 0);

    adg.enable();

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S1));
    adg.select(ADG708::Channel::S1);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S2));
    adg.select(ADG708::Channel::S2);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S3));
    adg.select(ADG708::Channel::S3);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S4));
    adg.select(ADG708::Channel::S4);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S5));
    adg.select(ADG708::Channel::S5);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S6));
    adg.select(ADG708::Channel::S6);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S7));
    adg.select(ADG708::Channel::S7);

    set_expect(a0, a1, a2, en, static_cast<uint8_t>(ADG708::Channel::S8));
    adg.select(ADG708::Channel::S8);
}
