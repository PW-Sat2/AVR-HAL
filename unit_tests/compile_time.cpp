#include "unity.h"
#include "tests.h"

#include "compile_time.h"
#include <cmath>
#include <cstdio>
using namespace hal;

template<int base, int exp>
struct test {
    static const bool value = ((power<base, exp>::value == std::pow(base, exp)) && test<base, exp-1>::value);
};

template<int base>
struct test<base, 0> {
    static const bool value = true;
};

TEST(compile_time, pow) {
    auto now = test<1, 10>::value;
    TEST_ASSERT_EQUAL(now, true);

    now = test<2, 30>::value;
    TEST_ASSERT_EQUAL(now, true);

    now = test<11, 6>::value;
    TEST_ASSERT_EQUAL(now, true);
}


template<int exp, int size, uint64_t value>
void powerOfTwoTest() {
    constexpr auto res = powerOfTwo<exp>();
    static_assert(res == value, "powerOfTwo (template) failed!");
    static_assert(sizeof(res) == size, "powerOfTwo (template) incorrect size!");

    constexpr auto res2 = powerOfTwo(exp);
    static_assert(res2 == value, "powerOfTwo (constexpr) failed!");
    static_assert(sizeof(res2) == 8, "powerOfTwo (constexpr) incorrect size!");
}

TEST(compile_time, powerOfTwoTest) {
    powerOfTwoTest<0, 1, 1>();
    powerOfTwoTest<7, 1, 128>();
    powerOfTwoTest<8, 2, 256>();
    powerOfTwoTest<15, 2, 32768>();
    powerOfTwoTest<16, 4, 65536>();
    powerOfTwoTest<31, 4, 2147483648L>();
    powerOfTwoTest<32, 8, 4294967296ULL>();
    powerOfTwoTest<63, 8, 9223372036854775808ULL>();
}

TEST(compile_time, type_with_bits) {
    EXPECT_EQ(sizeof(type_with_bits<0>), 1);
    EXPECT_EQ(sizeof(type_with_bits<8>), 1);
    EXPECT_EQ(sizeof(type_with_bits<9>), 2);
    EXPECT_EQ(sizeof(type_with_bits<16>), 2);
    EXPECT_EQ(sizeof(type_with_bits<17>), 4);
    EXPECT_EQ(sizeof(type_with_bits<32>), 4);
    EXPECT_EQ(sizeof(type_with_bits<33>), 8);
    EXPECT_EQ(sizeof(type_with_bits<64>), 8);
}

DEFINE_TESTSUITE(compile_time);
