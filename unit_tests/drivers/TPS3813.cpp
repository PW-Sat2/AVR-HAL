#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(TPS3813);

using namespace hal;
using namespace hal::libs;

struct TPS3813Mock : public DigtalIOMock {
    DigitalIO::Interface::Mode mode_buffer[10];
    FIFO<DigitalIO::Interface::Mode> mode{mode_buffer, 10};

    bool val_buffer[10];
    FIFO<bool> value{val_buffer, 10};

    void init(const Mode mode_) override {
        mode.append(mode_);
    }

    void write(bool value_) override {
        value.append(value_);
    }
};

TPS3813Mock wdi;
constexpr int pulse_time = 10;

TEST(TPS3813, init) {
    hal::devices::TPS3813<pulse_time> watchdog{wdi};

    watchdog.init();

    TEST_ASSERT_EQUAL(DigitalIO::Interface::Mode::OUTPUT, wdi.mode.get());
    TEST_ASSERT_TRUE(wdi.mode.isEmpty());

    TEST_ASSERT_FALSE(wdi.value.get());
    TEST_ASSERT_TRUE(wdi.value.isEmpty());
}

TEST(TPS3813, kick) {
    hal::devices::TPS3813<pulse_time> watchdog{wdi};

    watchdog.init();
    TEST_ASSERT_EQUAL(DigitalIO::Interface::Mode::OUTPUT, wdi.mode.get());
    TEST_ASSERT_TRUE(wdi.mode.isEmpty());

    TEST_ASSERT_FALSE(wdi.value.get());
    TEST_ASSERT_TRUE(wdi.value.isEmpty());


    watchdog.kick();
    TEST_ASSERT_TRUE(wdi.value.isNotEmpty());

    TEST_ASSERT_TRUE(wdi.value.get());
    TEST_ASSERT_TRUE(wdi.value.isNotEmpty());

    TEST_ASSERT_FALSE(wdi.value.get());
    TEST_ASSERT_TRUE(wdi.value.isEmpty());
}
