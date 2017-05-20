#include <avr/io.h>

#include "tests.h"

using namespace hal;



TEST(DigitalIO, mode) {
    DDRG = 0;
    PORTG = 0;

    hal::DigitalIO::GPIO<1> io;

    io.init(DigitalIO::Interface::Mode::INPUT);
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, 0);

    io.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, (1 << 5));

    io.reset();
    EXPECT_EQ(DDRG, 0);
    EXPECT_EQ(PORTG, 0);

    io.init(DigitalIO::Interface::Mode::OUTPUT);
    EXPECT_EQ(DDRG, (1 << 5));
    EXPECT_EQ(PORTG, 0);

    io.set();
    EXPECT_EQ(DDRG, (1 << 5));
    EXPECT_EQ(PORTG, (1 << 5));

    io.init(DigitalIO::Interface::Mode::OUTPUT);
    EXPECT_EQ(DDRG, (1 << 5));
    EXPECT_EQ(PORTG, (1 << 5));
}

DEFINE_TESTSUITE(DigitalIO);
