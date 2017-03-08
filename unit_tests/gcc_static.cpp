#include "tests.h"

namespace gcc_static {
char x;
void set(int i) {
    x = i;
}

char test() {
    set(42);
    static char bar = x;
    return bar++;
}
}  // namespace gcc_static


TEST(gcc_static, init_and_increase) {
    EXPECT_EQ(gcc_static::test(), 42);
    EXPECT_EQ(gcc_static::test(), 43);
    EXPECT_EQ(gcc_static::test(), 44);
}


DEFINE_TESTSUITE(gcc_static);
