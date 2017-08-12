#include "tests.h"
#include "unity.h"

#include "mocks/SPI.h"

TEST_GROUP(TMP121);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

struct MockTMP121 : public EmptySPIMock {
    static uint16_t data;

    static void read(gsl::span<uint8_t> in, uint8_t output_value = 0) {
        TEST_ASSERT_EQUAL(2, in.size());
        in[0] = data >> 8;
        in[1] = data & 0xFF;
    }
};
uint16_t MockTMP121::data;

using mock = MockTMP121;
using tmp  = TMP121<mock>;

TEST(TMP121, raw_read) {
    for (uint16_t i :
         {0xFFFFu, 0x4B00u, 0x3E80u, 0x0C80u, 0x0008u, 0u, 0xFFF8u, 0xF380u, 0xE480u}) {
        mock::data = i;
        TEST_ASSERT_EQUAL_INT(i >> 3, tmp::read_raw());
    }
}

TEST(TMP121, ConversionTableFromDatasheet) {
    mock::data = 0x4B00;
    TEST_ASSERT_EQUAL_INT(2400, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(150.0, tmp::read_celsius());

    mock::data = 0x3E80;
    TEST_ASSERT_EQUAL_INT(2000, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(125.0, tmp::read_celsius());

    mock::data = 0x0C80;
    TEST_ASSERT_EQUAL_INT(400, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(25.0, tmp::read_celsius());

    mock::data = 0x0008;
    TEST_ASSERT_EQUAL_INT(1, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(0.0625, tmp::read_celsius());

    mock::data = 0x0;
    TEST_ASSERT_EQUAL_INT(0, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(0, tmp::read_celsius());

    mock::data = 0xFFF8;
    TEST_ASSERT_EQUAL_INT(-1, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(-0.0625, tmp::read_celsius());

    mock::data = 0xF380;
    TEST_ASSERT_EQUAL_INT(-400, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(-25, tmp::read_celsius());

    mock::data = 0xE480;
    TEST_ASSERT_EQUAL_INT(-880, tmp::read());
    TEST_ASSERT_EQUAL_FLOAT(-55, tmp::read_celsius());
}

TEST(TMP121, UnknownBitsShouldNotChangeValue) {
    uint16_t data = 0x4B00;
    for (int i = 0; i <= 0b111; ++i) {
        mock::data = data + i;
        TEST_ASSERT_EQUAL_INT(2400, tmp::read());
        TEST_ASSERT_EQUAL_FLOAT(150, tmp::read_celsius());
    }

    data = 0x0;
    for (int i = 0; i <= 0b111; ++i) {
        mock::data = data + i;
        TEST_ASSERT_EQUAL_INT(0, tmp::read());
        TEST_ASSERT_EQUAL_FLOAT(0, tmp::read_celsius());
    }

    data = 0xE480;
    for (int i = 0; i <= 0b111; ++i) {
        mock::data = data + i;
        TEST_ASSERT_EQUAL_INT(-880, tmp::read());
        TEST_ASSERT_EQUAL_FLOAT(-55, tmp::read_celsius());
    }
}
