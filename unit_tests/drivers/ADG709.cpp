#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG709);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

template<int i>
struct ADG709Mock : public DigtalIOMock<ADG709Mock<i>> {
    static void init(const DigitalIO::Mode mode) {
        TEST_ASSERT_EQUAL(mode, DigitalIO::Mode::OUTPUT);
    }

    // 0xFF for don't care
    static uint8_t expect;

    static void write(bool value) {
        if (expect != 0xFF) {
            TEST_ASSERT_EQUAL(expect, value);
        }
    }
};
template<int i>
uint8_t ADG709Mock<i>::expect;

using a0 = ADG709Mock<0>;
using a1 = ADG709Mock<1>;
using en = ADG709Mock<2>;

static void set_expect(uint8_t output) {
    if (output == 0xFF) {
        en::expect = 0;
        a0::expect = a1::expect = 0xFF;
    } else {
        en::expect = 1;
        a0::expect = hal::libs::read_bit<0>(output);
        a1::expect = hal::libs::read_bit<1>(output);
    }
}


TEST(ADG709, disable) {
    using adg = ADG709::ADG709<a0, a1, en>;

    set_expect(0xFF);
    adg::disable();

    adg::select(ADG709::Channel::S1);
    adg::select(ADG709::Channel::S2);
    adg::select(ADG709::Channel::S3);
    adg::select(ADG709::Channel::S4);
}

TEST(ADG709, enabled) {
    set_expect(0xFF);
    using adg = ADG709::ADG709<a0, a1, en>;

    set_expect(0);

    adg::enable();

    set_expect(0);
    adg::select(ADG709::Channel::S1);

    set_expect(1);
    adg::select(ADG709::Channel::S2);

    set_expect(2);
    adg::select(ADG709::Channel::S3);

    set_expect(3);
    adg::select(ADG709::Channel::S4);
}
