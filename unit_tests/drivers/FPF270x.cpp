#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(FPF270x);

using namespace hal;
using namespace hal::libs;

template<int i>
struct FPF270xMock : public DigtalIOMock<FPF270xMock<i>> {
    static DigitalIO::Mode mode;
    static bool value;

    static void init(const DigitalIO::Mode mode_) {
        mode = mode_;
    }

    static void write(bool value_) {
        value = value_;
    }

    static bool read() {
        return value;
    }
};
template<int i>
DigitalIO::Mode FPF270xMock<i>::mode;
template<int i>
bool FPF270xMock<i>::value;


using on    = FPF270xMock<0>;
using flag  = FPF270xMock<1>;
using pgood = FPF270xMock<2>;

TEST(FPF270x, init) {
    using fpf = hal::devices::FPF270x<on, flag, pgood>;
    on::mode = flag::mode = pgood::mode = DigitalIO::Mode::INPUT;

    fpf::init();
    TEST_ASSERT_EQUAL(DigitalIO::Mode::OUTPUT, on::mode);
    TEST_ASSERT_EQUAL(DigitalIO::Mode::INPUT_PULLUP, flag::mode);
    TEST_ASSERT_EQUAL(DigitalIO::Mode::INPUT_PULLUP, pgood::mode);
}

TEST(FPF270x, on_off) {
    using fpf = hal::devices::FPF270x<on, flag, pgood>;

    on::value = true;
    fpf::on();
    TEST_ASSERT_FALSE(on::value);

    fpf::off();
    TEST_ASSERT_TRUE(on::value);

    fpf::on();
    TEST_ASSERT_FALSE(on::value);
}

TEST(FPF270x, error) {
    using fpf = hal::devices::FPF270x<on, flag, pgood>;

    flag::value = true;
    TEST_ASSERT_TRUE(fpf::error_occured());

    flag::value = false;
    TEST_ASSERT_FALSE(fpf::error_occured());
}

TEST(FPF270x, power_good) {
    using fpf = hal::devices::FPF270x<on, flag, pgood>;

    pgood::value = true;
    TEST_ASSERT_TRUE(fpf::power_good());

    pgood::value = false;
    TEST_ASSERT_FALSE(fpf::power_good());
}
