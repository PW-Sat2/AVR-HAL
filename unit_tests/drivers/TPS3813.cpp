#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(TPS3813);

using namespace hal;
using namespace hal::libs;

struct TPS3813Mock : public DigtalIOMock<TPS3813Mock> {
    static FIFO_data<DigitalIO::Mode, 10> mode;

    static FIFO_data<bool, 10> value;

    static void init(const DigitalIO::Mode mode_) {
        mode.append(mode_);
    }

    static void write(bool value_) {
        value.append(value_);
    }
};
decltype(TPS3813Mock::mode) TPS3813Mock::mode;
decltype(TPS3813Mock::value) TPS3813Mock::value;


constexpr int pulse_time = 10;

using watchdog = hal::devices::TPS3813<TPS3813Mock, pulse_time>;

TEST(TPS3813, init) {
    watchdog::init();
    TEST_ASSERT_TRUE(TPS3813Mock::mode.isNotEmpty());
    TEST_ASSERT_EQUAL(DigitalIO::Mode::OUTPUT, TPS3813Mock::mode.get());
    TEST_ASSERT_TRUE(TPS3813Mock::mode.isEmpty());

    TEST_ASSERT_TRUE(TPS3813Mock::value.isNotEmpty());
    TEST_ASSERT_FALSE(TPS3813Mock::value.get());
    TEST_ASSERT_TRUE(TPS3813Mock::value.isEmpty());
}

TEST(TPS3813, kick) {
    watchdog::init();

    TEST_ASSERT_TRUE(TPS3813Mock::value.isNotEmpty());
    TEST_ASSERT_FALSE(TPS3813Mock::value.get());
    TEST_ASSERT_TRUE(TPS3813Mock::value.isEmpty());

    watchdog::kick();

    TEST_ASSERT_TRUE(TPS3813Mock::value.isNotEmpty());
    TEST_ASSERT_TRUE(TPS3813Mock::value.get());
    TEST_ASSERT_TRUE(TPS3813Mock::value.isNotEmpty());

    TEST_ASSERT_FALSE(TPS3813Mock::value.get());
    TEST_ASSERT_TRUE(TPS3813Mock::value.isEmpty());

    TEST_ASSERT_TRUE(TPS3813Mock::mode.isNotEmpty());
    TEST_ASSERT_EQUAL(DigitalIO::Mode::OUTPUT, TPS3813Mock::mode.get());
    TEST_ASSERT_TRUE(TPS3813Mock::mode.isEmpty());
}
