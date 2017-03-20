#include <limits>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include "tests.h"

#define DATA_ASSERT(type, size) \
    static_assert(sizeof(type) == (size), #type );

#define TEST_NUMERIC(bits)                        \
    DATA_ASSERT(uint ## bits ##_t, bits/8)        \
    DATA_ASSERT(std::uint ## bits ##_t, bits/8)   \
    DATA_ASSERT(int ## bits ##_t, bits/8)         \
    DATA_ASSERT(std::int ## bits ##_t, bits/8)    \

class TestDataTypes {
    TEST_NUMERIC(8);
    TEST_NUMERIC(16);
    TEST_NUMERIC(32);
    TEST_NUMERIC(64);

    DATA_ASSERT(bool, 1);
    DATA_ASSERT(char, 1);
    DATA_ASSERT(unsigned char, 1);

    DATA_ASSERT(int, 2);
    DATA_ASSERT(unsigned int, 2);

    DATA_ASSERT(long int, 4);
    DATA_ASSERT(unsigned long int, 4);

    DATA_ASSERT(long, 4);
    DATA_ASSERT(unsigned long, 4);

    DATA_ASSERT(long long, 8);
    DATA_ASSERT(unsigned long long, 8);


    DATA_ASSERT(std::size_t, 2);
    DATA_ASSERT(void *, 2);
} testDataTypes;

#define NUM_TEST(var, type, mini, maxi)                        \
    EXPECT_EQ(mini, std::numeric_limits<type>::min());    \
    EXPECT_EQ(maxi, std::numeric_limits<type>::max());    \
    EXPECT_TRUE(std::numeric_limits<type>::min() < std::numeric_limits<type>::max()); \
    type var ##_a = std::numeric_limits<type>::max(); \
    type var ##_b = var ##_a+1; \
    EXPECT_TRUE(var ##_a > var ##_b);

TEST(data_types, numeric_limits) {
    NUM_TEST(b, char,                                   -128, 127);
    NUM_TEST(c, int8_t,                                 -128, 127);
    NUM_TEST(d, unsigned char,                             0, 255);
    NUM_TEST(e, uint8_t,                                   0, 255);
    NUM_TEST(f, int,                                  -32768, 32767);
    NUM_TEST(g, int16_t,                              -32768, 32767);
    NUM_TEST(h, unsigned int,                              0, 65535);
    NUM_TEST(i, uint16_t,                                  0, 65535);
    NUM_TEST(j, long,                           -2147483648L, 2147483647);
    NUM_TEST(k, int32_t,                        -2147483648L, 2147483647);
    NUM_TEST(l, unsigned long,                            0L, 4294967295);
    NUM_TEST(m, uint32_t,                                 0L, 4294967295);
    NUM_TEST(n, uint64_t,                               0ULL, 18446744073709551615ULL);
    NUM_TEST(o, unsigned long long,                     0ULL, 18446744073709551615ULL);
    NUM_TEST(p, long long,            -9223372036854775808LL, 9223372036854775807LL);
    NUM_TEST(r, int64_t,              -9223372036854775808LL, 9223372036854775807LL);
}

DEFINE_TESTSUITE(data_types);
