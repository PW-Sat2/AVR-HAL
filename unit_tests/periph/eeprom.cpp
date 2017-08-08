#include <avr/io.h>

#include "tests.h"

using namespace hal;

bool EEMEM eeprom_var_bool{true};
EepromWrapper<bool> var_bool{eeprom_var_bool};

char EEMEM eeprom_var_char{0x76};
EepromWrapper<char> var_char{eeprom_var_char};

float EEMEM eeprom_var_float{-123.48174};
EepromWrapper<float> var_float{eeprom_var_float};

int16_t EEMEM eeprom_var_int16{-4365};
EepromWrapper<int16_t> var_int16{eeprom_var_int16};

uint16_t EEMEM eeprom_var_uint16{64123};
EepromWrapper<uint16_t> var_uint16{eeprom_var_uint16};

int32_t EEMEM eeprom_var_int32{0x12FFFFFF};
EepromWrapper<int32_t> var_int32{eeprom_var_int32};

TEST_GROUP(eeprom);

TEST(eeprom, default_values) {
    TEST_ASSERT_EQUAL(true, var_bool);
    TEST_ASSERT_EQUAL(0x76, var_char);
    TEST_ASSERT_EQUAL_FLOAT(-123.48174, var_float);
    TEST_ASSERT_EQUAL(-4365, var_int16);
    TEST_ASSERT_EQUAL(64123, var_uint16);
    TEST_ASSERT_EQUAL(0x12FFFFFF, var_int32);
}

TEST(eeprom, simple) {
    var_bool   = false;
    var_char   = 127;
    var_float  = 9583.1;
    var_int16  = -32761;
    var_uint16 = 65487;
    var_int32  = 2139029471L;

    TEST_ASSERT_EQUAL(var_bool, false);
    TEST_ASSERT_EQUAL(var_char, 127);
    TEST_ASSERT_EQUAL_FLOAT(var_float, 9583.1);
    TEST_ASSERT_EQUAL(var_int16, -32761);
    TEST_ASSERT_EQUAL(var_uint16, 65487);
    TEST_ASSERT_EQUAL(var_int32, 2139029471L);

    var_bool   = true;
    var_char   = -128;
    var_float  = 11183.7;
    var_int16  = 32767;
    var_uint16 = 0;
    var_int32  = 458898752L;

    TEST_ASSERT_EQUAL(var_bool, true);
    TEST_ASSERT_EQUAL(var_char, -128);
    TEST_ASSERT_EQUAL_FLOAT(var_float, 11183.7);
    TEST_ASSERT_EQUAL(var_int16, 32767);
    TEST_ASSERT_EQUAL(var_uint16, 0);
    TEST_ASSERT_EQUAL(var_int32, 458898752L);
}

TEST(eeprom, read_write) {
    var_bool.write(false);

    TEST_ASSERT_EQUAL(var_bool.read(), false);

    var_bool.write(true);

    TEST_ASSERT_EQUAL(var_bool.read(), true);
}
