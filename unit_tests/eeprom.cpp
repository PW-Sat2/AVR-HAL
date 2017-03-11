#include <avr/io.h>

#include "eeprom.h"
#include "tests.h"

using namespace hal;

static EepromStorage<bool> var_bool;
static EepromStorage<char> var_char;
static EepromStorage<float> var_float;
static EepromStorage<int16_t> var_int16;
static EepromStorage<uint16_t> var_uint16;
static EepromStorage<int32_t> var_int32;

TEST(eeprom, simple) {
    var_bool = false;
    var_char = 127;
    var_float = 9583.1;
    var_int16 = -32761;
    var_uint16 = 65487;
    var_int32 = 2139029471L;

    EXPECT_EQ(var_bool,    false);
    EXPECT_EQ(var_char,    127);
    EXPECT_FLOAT_EQ(var_float, 9583.1);
    EXPECT_EQ(var_int16,   -32761);
    EXPECT_EQ(var_uint16,  65487);
    EXPECT_EQ(var_int32,   2139029471L);

    var_bool = true;
    var_char = -128;
    var_float = 11183.7;
    var_int16 = 32767;
    var_uint16 = 0;
    var_int32 = 458898752L;

    EXPECT_EQ(var_bool,        true);
    EXPECT_EQ(var_char,        -128);
    EXPECT_FLOAT_EQ(var_float, 11183.7);
    EXPECT_EQ(var_int16,       32767);
    EXPECT_EQ(var_uint16,      0);
    EXPECT_EQ(var_int32,       458898752L);
}

DEFINE_TESTSUITE(eeprom);
