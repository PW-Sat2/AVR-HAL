#include <mocks/SPI.h>
#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(DAC121);

using namespace hal;
using namespace hal::libs;
using namespace hal::drivers;

struct DAC121Mock : public EmptySPIMock {
    void write(gsl::span<const uint8_t> in) override {
        uint16_t word;
        TEST_ASSERT_EQUAL_INT(2, in.size());

        Reader reader_in{in};
        word = reader_in.ReadWordBE();

        mode = word >> 12;
        value = word & 0xFFF;
    }

    uint16_t value;
    uint8_t mode;
};

TEST(DAC121, modes) {
    DAC121Mock mock;
    DAC121 dac121(mock);

    // 2 cases for Normal Operation
    dac121.SetMode(DAC121::Mode::NormalOperation);
    dac121.WriteToOutput(111);
    TEST_ASSERT_EQUAL_INT(0x0, mock.mode);

    dac121.SetMode(DAC121::Mode::NormalOperation);
    dac121.WriteToOutput(0);
    TEST_ASSERT_EQUAL_INT(0x0, mock.mode);

    // 2 cases for 1k to GND
    dac121.SetMode(DAC121::Mode::PowerDown_1kToGnd);
    dac121.WriteToOutput(551);
    TEST_ASSERT_EQUAL_INT(0x1, mock.mode);

    dac121.SetMode(DAC121::Mode::PowerDown_1kToGnd);
    dac121.WriteToOutput(0);
    TEST_ASSERT_EQUAL_INT(0x1, mock.mode);

    // 2 cases for 100k to GND
    dac121.SetMode(DAC121::Mode::PowerDown_100kToGnd);
    dac121.WriteToOutput(336);
    TEST_ASSERT_EQUAL_INT(0x2, mock.mode);

    dac121.SetMode(DAC121::Mode::PowerDown_100kToGnd);
    dac121.WriteToOutput(0);
    TEST_ASSERT_EQUAL_INT(0x2, mock.mode);

    // 2 cases for HiZ
    dac121.SetMode(DAC121::Mode::PowerDown_HiZ);
    dac121.WriteToOutput(4000);
    TEST_ASSERT_EQUAL_INT(0x3, mock.mode);

    dac121.SetMode(DAC121::Mode::PowerDown_HiZ);
    dac121.WriteToOutput(0);
    TEST_ASSERT_EQUAL_INT(0x3, mock.mode);
}

TEST(DAC121, edgeCases) {
    DAC121Mock mock;
    DAC121 dac121(mock);

    dac121.SetMode(DAC121::Mode::NormalOperation);
    dac121.WriteToOutput(4095);
    TEST_ASSERT_EQUAL_INT(4095, mock.value);

    dac121.SetMode(DAC121::Mode::NormalOperation);
    dac121.WriteToOutput(0);
    TEST_ASSERT_EQUAL_INT(0, mock.value);
}

TEST(DAC121, fullRange) {
    DAC121Mock mock;
    DAC121 dac121(mock);

    dac121.SetMode(DAC121::Mode::NormalOperation);

    for (uint16_t i = 0; i < 4096; ++i) {
        dac121.WriteToOutput(i);
        TEST_ASSERT_EQUAL_INT(i, mock.value);
    }
}
