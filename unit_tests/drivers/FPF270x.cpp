#include "tests.h"
#include "mocks/DigitalIO.h"

TEST_GROUP(FPF270x);

using namespace hal;
using namespace hal::libs;

struct FPF270xMock : public DigtalIOMock {
    Mode mode;
    bool value;

    void init(const Mode mode_) override {
        mode = mode_;
    }

    void write(bool value_) override {
        value = value_;
    }

    bool read() override {
        return value;
    }
};

FPF270xMock on, flag, pgood;

TEST(FPF270x, init) {
    hal::devices::FPF270x fpf{on, flag, pgood};
    on.mode = flag.mode = pgood.mode = DigitalIO::Interface::Mode::INPUT;

    fpf.init();
    TEST_ASSERT_EQUAL(DigitalIO::Interface::Mode::OUTPUT, on.mode);
    TEST_ASSERT_EQUAL(DigitalIO::Interface::Mode::INPUT_PULLUP, flag.mode);
    TEST_ASSERT_EQUAL(DigitalIO::Interface::Mode::INPUT_PULLUP, pgood.mode);
}

TEST(FPF270x, on_off) {
    hal::devices::FPF270x fpf{on, flag, pgood};

    on.value = true;
    fpf.on();
    TEST_ASSERT_FALSE(on.value);

    fpf.off();
    TEST_ASSERT_TRUE(on.value);

    fpf.on();
    TEST_ASSERT_FALSE(on.value);
}

TEST(FPF270x, error) {
    hal::devices::FPF270x fpf{on, flag, pgood};

    flag.value = true;
    TEST_ASSERT_TRUE(fpf.error_occured());

    flag.value = false;
    TEST_ASSERT_FALSE(fpf.error_occured());
}

TEST(FPF270x, power_good) {
    hal::devices::FPF270x fpf{on, flag, pgood};

    pgood.value = true;
    TEST_ASSERT_TRUE(fpf.power_good());

    pgood.value = false;
    TEST_ASSERT_FALSE(fpf.power_good());
}
