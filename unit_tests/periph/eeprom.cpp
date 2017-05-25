#include <avr/io.h>

#include "tests.h"

using namespace hal;

static EepromStorage<bool> var_bool;
static EepromStorage<char> var_char;
static EepromStorage<float> var_float;
static EepromStorage<int16_t> var_int16;
static EepromStorage<uint16_t> var_uint16;
static EepromStorage<int32_t> var_int32;

TEST_GROUP(eeprom);

TEST(eeprom, simple) {
    var_bool = false;
    var_char = 127;
    var_float = 9583.1;
    var_int16 = -32761;
    var_uint16 = 65487;
    var_int32 = 2139029471L;

    TEST_ASSERT_EQUAL(var_bool,    false);
    TEST_ASSERT_EQUAL(var_char,    127);
    TEST_ASSERT_EQUAL_FLOAT(var_float, 9583.1);
    TEST_ASSERT_EQUAL(var_int16,   -32761);
    TEST_ASSERT_EQUAL(var_uint16,  65487);
    TEST_ASSERT_EQUAL(var_int32,   2139029471L);

    var_bool = true;
    var_char = -128;
    var_float = 11183.7;
    var_int16 = 32767;
    var_uint16 = 0;
    var_int32 = 458898752L;

    TEST_ASSERT_EQUAL(var_bool,        true);
    TEST_ASSERT_EQUAL(var_char,        -128);
    TEST_ASSERT_EQUAL_FLOAT(var_float, 11183.7);
    TEST_ASSERT_EQUAL(var_int16,       32767);
    TEST_ASSERT_EQUAL(var_uint16,      0);
    TEST_ASSERT_EQUAL(var_int32,       458898752L);
}
