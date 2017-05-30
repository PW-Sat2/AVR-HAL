#include "tests.h"
#include "mocks/DigitalIO.h"

TEST_GROUP(ADG849);

using namespace hal;
using namespace hal::libs;

struct ADG849Mock : public DigtalIOMock {
    void init(const Mode mode) override {
        TEST_ASSERT_EQUAL(mode, Mode::OUTPUT);
    }

    bool value_written;

    void write(bool value) override {
        this->value_written = value;
    }
};

TEST(ADG849, set_channel) {
    ADG849Mock in;
    hal::ADG849 adg(in);

    adg.init(hal::ADG849::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, in.value_written);

    adg.init(hal::ADG849::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, in.value_written);

    adg.select(hal::ADG849::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, in.value_written);

    adg.select(hal::ADG849::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, in.value_written);
}
