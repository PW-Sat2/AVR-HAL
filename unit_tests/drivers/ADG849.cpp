#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADG849);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

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
    using adg = ADG849::ADG849<ADG849Mock>;

    adg::init(ADG849::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, ADG849Mock::value_written);

    adg::init(ADG849::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, ADG849Mock::value_written);

    adg::select(ADG849::Channel::S1);
    TEST_ASSERT_EQUAL_INT(false, ADG849Mock::value_written);

    adg::select(ADG849::Channel::S2);
    TEST_ASSERT_EQUAL_INT(true, ADG849Mock::value_written);
}
