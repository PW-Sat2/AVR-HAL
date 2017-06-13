#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG849);

using namespace hal;
using namespace hal::libs;

struct ADG849Mock : public DigtalIOMock<ADG849Mock> {
    static void init(const DigitalIO::Mode mode) {
        TEST_ASSERT_EQUAL(mode, DigitalIO::Mode::OUTPUT);
    }

    static bool value_written;

    static void write(bool value) {
        value_written = value;
    }
};

bool ADG849Mock::value_written;

TEST(ADG849, set_channel) {
    using ADG = hal::ADG849<ADG849Mock>;
    ADG adg;

    adg.init(ADG::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, ADG849Mock::value_written);

    adg.init(ADG::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, ADG849Mock::value_written);

    adg.select(ADG::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, ADG849Mock::value_written);

    adg.select(ADG::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, ADG849Mock::value_written);
}
