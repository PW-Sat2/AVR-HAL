#include "tests.h"
#include "unity.h"

#include "mocks/SPI.h"

TEST_GROUP(AD5641);

using namespace hal;
using namespace hal::libs;

struct MockAD5641 : public EmptySPIMock {
    uint16_t expect;

    void write(gsl::span<const uint8_t> output) override {
        TEST_ASSERT_EQUAL(2, output.size());
        Reader reader{output};
        TEST_ASSERT_EQUAL(expect, reader.ReadWordBE());
    }
};

void AD5641test(uint16_t value) {
    MockAD5641 mock;
    AD5641 ad5641{mock};

    mock.expect = value;
    ad5641.write(value);
}

TEST(AD5641, writeLowByte) {
    for (size_t i = 0; i < power_of_two<14>(); i += 100) {
        AD5641test(i);
    }
}

TEST(AD5641, edge_cases) {
    AD5641test(0);
    AD5641test(0x3FFF);
}

TEST(AD5641, overflow) {
    MockAD5641 mock;
    AD5641 ad5641{mock};

    mock.expect = 0x3FFF, ad5641.write(0x4000);
    mock.expect = 0x3FFF, ad5641.write(0xFFFF);
}
