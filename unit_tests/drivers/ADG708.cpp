#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG708);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

template<int i>
struct ADG708Mock {
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

    static void set() {
        write(1);
    }

    static void reset() {
        write(0);
    }
};
template<int i>
uint8_t ADG708Mock<i>::expect;

using a0 = ADG708Mock<0>;
using a1 = ADG708Mock<1>;
using a2 = ADG708Mock<2>;
using en = ADG708Mock<3>;

static void set_expect(uint8_t output) {
    if (output == 0xFF) {
        en::expect = 0;
        a0::expect = a1::expect = a2::expect = 0xFF;
    } else {
        en::expect = 1;
        a0::expect = hal::libs::read_bit<0>(output);
        a1::expect = hal::libs::read_bit<1>(output);
        a2::expect = hal::libs::read_bit<2>(output);
    }
}

TEST(ADG708, disable) {
    using adg = ADG708::ADG708<a0, a1, a2, en>;

    set_expect(0xFF);
    adg::disable();

    adg::select(ADG708::Channel::S1);
    adg::select(ADG708::Channel::S2);
    adg::select(ADG708::Channel::S3);
    adg::select(ADG708::Channel::S4);
    adg::select(ADG708::Channel::S5);
    adg::select(ADG708::Channel::S6);
    adg::select(ADG708::Channel::S7);
    adg::select(ADG708::Channel::S8);
}

TEST(ADG708, enabled) {
    set_expect(0xFF);

    using adg = ADG708::ADG708<a0, a1, a2, en>;

    set_expect(0);

    adg::enable();

    set_expect(0);
    adg::select(ADG708::Channel::S1);

    set_expect(1);
    adg::select(ADG708::Channel::S2);

    set_expect(2);
    adg::select(ADG708::Channel::S3);

    set_expect(3);
    adg::select(ADG708::Channel::S4);

    set_expect(4);
    adg::select(ADG708::Channel::S5);

    set_expect(5);
    adg::select(ADG708::Channel::S6);

    set_expect(6);
    adg::select(ADG708::Channel::S7);

    set_expect(7);
    adg::select(ADG708::Channel::S8);
}
