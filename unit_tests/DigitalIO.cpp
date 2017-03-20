#include <avr/io.h>

#include "tests.h"

using namespace hal;



TEST(DigitalIO, mode) {
    DDRG = 0;
    PORTG = 0;

    constexpr hal::DigitalIO io{1};

    io.init(DigitalIO::INPUT);
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, 0);

    io.init(DigitalIO::INPUT_PULLUP);
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, (1 << 5));

    io.reset();
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, 0);

    io.init(DigitalIO::OUTPUT);
    EXPECT_EQ(DDRG, (1 << 5));
    EXPECT_EQ(PORTG, 0);

    io.set();
    EXPECT_EQ(DDRG, (1 << 5));
    EXPECT_EQ(PORTG, (1 << 5));

    io.init(DigitalIO::OUTPUT);
    EXPECT_EQ(PORTG, (1 << 5));
    EXPECT_EQ(PORTG, (1 << 5));
}

DEFINE_TESTSUITE(DigitalIO);
