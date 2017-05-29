#include "unity.h"
#include "tests.h"

#include "mocks/SPI.h"

TEST_GROUP(TMP121);

using namespace hal;
using namespace hal::libs;

struct MockTMP121 : public EmptySPIMock {
    uint16_t data;

    void read(hal::libs::span<uint8_t> in, uint8_t output_value) override {
        TEST_ASSERT_EQUAL(2, in.size());
        in[0] = data >> 8;
        in[1] = data & 0xFF;
    }
};


TEST(TMP121, ConversionTableFromDatasheet) {
    MockTMP121 mock;
    TMP121 tmp{mock};


    mock.data = 0x4B00;
    TEST_ASSERT_EQUAL_INT(2400, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(150.0, tmp.readCelsius());

    mock.data = 0x3E80;
    TEST_ASSERT_EQUAL_INT(2000, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(125.0, tmp.readCelsius());

    mock.data = 0x0C80;
    TEST_ASSERT_EQUAL_INT(400, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(25.0, tmp.readCelsius());

    mock.data = 0x0008;
    TEST_ASSERT_EQUAL_INT(1, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(0.0625, tmp.readCelsius());

    mock.data = 0x0;
    TEST_ASSERT_EQUAL_INT(0, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(0, tmp.readCelsius());

    mock.data = 0xFFF8;
    TEST_ASSERT_EQUAL_INT(-1, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(-0.0625, tmp.readCelsius());

    mock.data = 0xF380;
    TEST_ASSERT_EQUAL_INT(-400, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(-25, tmp.readCelsius());

    mock.data = 0xE480;
    TEST_ASSERT_EQUAL_INT(-880, tmp.read());
    TEST_ASSERT_EQUAL_FLOAT(-55, tmp.readCelsius());
}

TEST(TMP121, UnknownBitsShouldNotChangeValue) {
    MockTMP121 mock;
    TMP121 tmp{mock};

    uint16_t data = 0x4B00;
    for (int i = 0; i <= 0b111; ++i) {
        mock.data = data + i;
        TEST_ASSERT_EQUAL_INT(2400, tmp.read());
        TEST_ASSERT_EQUAL_FLOAT(150, tmp.readCelsius());
    }

    data = 0x0;
    for (int i = 0; i <= 0b111; ++i) {
        mock.data = data + i;
        TEST_ASSERT_EQUAL_INT(0, tmp.read());
        TEST_ASSERT_EQUAL_FLOAT(0, tmp.readCelsius());
    }

    data = 0xE480;
    for (int i = 0; i <= 0b111; ++i) {
        mock.data = data + i;
        TEST_ASSERT_EQUAL_INT(-880, tmp.read());
        TEST_ASSERT_EQUAL_FLOAT(-55, tmp.readCelsius());
    }
}
