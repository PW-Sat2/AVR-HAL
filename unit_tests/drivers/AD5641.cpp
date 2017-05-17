#include "unity.h"
#include "tests.h"

#include <math.h>

using namespace hal;
using namespace hal::libs;

struct TestSPI : public SPI::ISPI {
    static array<uint8_t, 100> data_buffer;
    static uint8_t length;

    span<uint8_t> data_exchanged() {
        auto ret =  make_span(data_buffer.begin(), length);
        length = 0;
        return ret;
    }

    uint8_t shift(const uint8_t data) override {
        auto from_buf = data_buffer[length];
        data_buffer[length++] = data;
        return from_buf;
    }
};

array<uint8_t, 100> TestSPI::data_buffer;
uint8_t TestSPI::length;

TEST(AD5641, init) {
    TestSPI spi;
    DigitalIO<2> pin;
    SPI::Device dev{spi, pin};
    AD5641 ad5641{dev};  // pin 2 on ATMEGA2560 is PE0

    DDRE = 0;
    PORTE = 0;
    ad5641.init();
    EXPECT_EQ(DDRE, 1);
    EXPECT_EQ(PORTE, 1);

    DDRE = 1;
    PORTE = 1;
    ad5641.init();
    EXPECT_EQ(DDRE, 1);
    EXPECT_EQ(PORTE, 1);

    DDRE = 0xFF;
    PORTE = 0;
    ad5641.init();
    EXPECT_EQ(DDRE, 0xFF);
    EXPECT_EQ(PORTE, 1);

    DDRE = 0xFE;
    PORTE = 0xA2;
    ad5641.init();
    EXPECT_EQ(DDRE, 0xFF);
    EXPECT_EQ(PORTE, 0xA3);
}

template<typename T>
void AD5641test(AD5641 ad5641, T spi, uint16_t value) {
    ad5641.write(value);
    auto x = spi.data_exchanged();
    auto sp = array<uint8_t, 2>{read_mask<8, 8>(value),
                                read_mask<0, 8>(value)};
    EXPECT_TRUE(x == sp);
}

TEST(AD5641, writeLowByte) {
    TestSPI spi;
    DigitalIO<2> pin;
    SPI::Device dev{spi, pin};
    AD5641 ad5641{dev};

    for (size_t i = 0; i < power_of_two<14>(); i += 100) {
        AD5641test(ad5641, spi, i);
    }
}

TEST(AD5641, edge_cases) {
    TestSPI spi;
    DigitalIO<2> pin;
    SPI::Device dev{spi, pin};
    AD5641 ad5641{dev};

    AD5641test(ad5641, spi, 0);
    AD5641test(ad5641, spi, 0x3FFF);
}

TEST(AD5641, overflow) {
    TestSPI spi;
    DigitalIO<2> pin;
    SPI::Device dev{spi, pin};
    AD5641 ad5641{dev};

    ad5641.write(0x4000);
    auto x = spi.data_exchanged();
    auto sp = array<uint8_t, 2>{0, 0};
    EXPECT_TRUE(x == sp);

    ad5641.write(0xFFFF);
    x = spi.data_exchanged();
    sp = array<uint8_t, 2>{0x3F, 0xFF};
    EXPECT_TRUE(x == sp);
}

DEFINE_TESTSUITE(AD5641);
