#include "tests.h"
#include "mocks/DigitalIO.h"

TEST_GROUP(ADG849);

using namespace hal;
using namespace hal::libs;

struct ADG849Mock : public DigtalIOMock {
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

void set_expect(ADG849Mock& in, uint8_t output) {
    if (output == 0xFF) {
        in.expect = 0;
    } else {
        in.expect = hal::libs::read_bit<0>(output);
    }
}

TEST(ADG849, set_channel) {
    ADG849Mock in;

    set_expect(in, 0xFF);
    hal::ADG849 adg(in);

    set_expect(in, 0);
    adg.select(hal::ADG849::Channel::S1);

    set_expect(in, 1);
    adg.select(hal::ADG849::Channel::S2);
}
