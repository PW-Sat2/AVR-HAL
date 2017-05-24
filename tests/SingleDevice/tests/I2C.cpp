#include "tests.h"

TEST_GROUP(I2C);

using namespace hal;

I2C::Hardware hw;

struct I2CTest : public I2C::details::_Interface {
    using StartAction = StartAction;
};

TEST(I2C, NACKwhenNoDevice) {
    hw.init<100000>();
    hw.enable_internal_pullups();

    TEST_ASSERT_FALSE(hw.start(0, I2CTest::StartAction::write));
    TEST_ASSERT_FALSE(hw.start(0, I2CTest::StartAction::read));
}
