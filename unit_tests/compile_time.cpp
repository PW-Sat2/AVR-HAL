#include <gtest/gtest.h>
#include "compile_time.h"
#include <cmath>
using hal::libs::power;

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
    EXPECT_EQ(now, true);

    now = test<2, 30>::value;
    EXPECT_EQ(now, true);

    now = test<11, 6>::value;
    EXPECT_EQ(now, true);
}
