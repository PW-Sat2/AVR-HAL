#include <mocks/SPI.h>
#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(DAC121);

using namespace hal;
using namespace hal::libs;
using namespace hal::devices;

struct DAC121Mock : public EmptySPIMock {
    static void write(gsl::span<const uint8_t> in) {
        uint16_t word;
        TEST_ASSERT_EQUAL_INT(2, in.size());

        Reader reader_in{in};
        word = reader_in.ReadWordBE();

        mode  = (word >> 12) & 0xF;
        value = word & 0xFFF;
    }

    static uint16_t value;
    static uint8_t mode;
};
uint16_t DAC121Mock::value;
uint8_t DAC121Mock::mode;

TEST(DAC121, modes) {
    using mock   = DAC121Mock;
    using dac121 = DAC121::DAC121<mock>;

    // 2 cases for Normal Operation
    dac121::write_to_output(111);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(0);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    // Power Down mode with 1k to GND
    dac121::set_power_down_mode(DAC121::PowerDownMode::ToGnd1k);
    TEST_ASSERT_EQUAL_INT(0x1, mock::mode);

    // Power Down mode with 100k to GND
    dac121::set_power_down_mode(DAC121::PowerDownMode::ToGnd100k);
    TEST_ASSERT_EQUAL_INT(0x2, mock::mode);

    // Power Down mode with HiZ
    dac121::set_power_down_mode(DAC121::PowerDownMode::HiZ);
    TEST_ASSERT_EQUAL_INT(0x3, mock::mode);
}

TEST(DAC121, edgeCases) {
    using mock   = DAC121Mock;
    using dac121 = DAC121::DAC121<mock>;

    dac121::write_to_output(4095);
    TEST_ASSERT_EQUAL_INT(4095, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(0);
    TEST_ASSERT_EQUAL_INT(0, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);
}

TEST(DAC121, outOfRange) {
    using mock   = DAC121Mock;
    using dac121 = DAC121::DAC121<mock>;

    dac121::write_to_output(4096);
    TEST_ASSERT_EQUAL_INT(0, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(22403);
    TEST_ASSERT_EQUAL_INT(1923, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(65535);
    TEST_ASSERT_EQUAL_INT(4095, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(-1);
    TEST_ASSERT_EQUAL_INT(4095, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);

    dac121::write_to_output(-3);
    TEST_ASSERT_EQUAL_INT(4093, mock::value);
    TEST_ASSERT_EQUAL_INT(0x0, mock::mode);
}

TEST(DAC121, fullRange) {
    using mock   = DAC121Mock;
    using dac121 = DAC121::DAC121<mock>;

    for (uint16_t i = 0; i < 4096; ++i) {
        dac121::write_to_output(i);
        TEST_ASSERT_EQUAL_INT(i, mock::value);
        TEST_ASSERT_EQUAL_INT(0x0, mock::mode);
    }
}
