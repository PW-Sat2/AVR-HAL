#include <cmath>
#include <cstdio>

#include "unity.h"
#include "tests.h"


using namespace hal::libs;

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
void power_of_twoTest() {
    constexpr auto res = power_of_two<exp>();
    static_assert(res == value, "power_of_two (template) failed!");
    static_assert(sizeof(res) == size, "power_of_two (template) incorrect size!");

    constexpr auto res2 = power_of_two(exp);
    static_assert(res2 == value, "power_of_two (constexpr) failed!");
    static_assert(sizeof(res2) == 8, "power_of_two (constexpr) incorrect size!");
}

TEST(compile_time, power_of_twoTest) {
    power_of_twoTest<0, 1, 1>();
    power_of_twoTest<7, 1, 128>();
    power_of_twoTest<8, 2, 256>();
    power_of_twoTest<15, 2, 32768>();
    power_of_twoTest<16, 4, 65536>();
    power_of_twoTest<31, 4, 2147483648L>();
    power_of_twoTest<32, 8, 4294967296ULL>();
    power_of_twoTest<63, 8, 9223372036854775808ULL>();
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
