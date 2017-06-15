#include "tests.h"
#include "unity.h"

#include "mocks/SPI.h"

TEST_GROUP(AD5641);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

struct MockAD5641 {
    static uint16_t expect;

    static void write(gsl::span<const uint8_t> output) {
        TEST_ASSERT_EQUAL(2, output.size());
        Reader reader{output};
        TEST_ASSERT_EQUAL(expect, reader.ReadWordBE());
    }
};
uint16_t MockAD5641::expect;


void AD5641test(uint16_t value) {
    using mock   = MockAD5641;
    using ad5641 = AD5641<mock>;

    mock::expect = value;
    ad5641::write(value);
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
    using ad5641 = AD5641<MockAD5641>;

    MockAD5641::expect = 0, ad5641::write(0x4000);
    MockAD5641::expect = 0x3FFF, ad5641::write(0xFFFF);
}
