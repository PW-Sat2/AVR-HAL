#include "gtest.h"

#include "bit_operations.h"

TEST(bit_operations, read_bit) {
    int val = 0;
    for(int i = 0; i < 32; ++i) {
        EXPECT_EQ(hal::read_bit(val, i), 0);
    }
    val = 0xFFFFFFFF;
    for(int i = 0; i < 32; ++i) {
        EXPECT_EQ(hal::read_bit(val, i), 1);
    }
    val = 0xAAAAAAAA;
    for(int i = 0; i < 32; ++i) {
        EXPECT_EQ(hal::read_bit(val, i), (i % 2));
    }
    val = 0x55555555;
    for(int i = 0; i < 32; ++i) {
        EXPECT_EQ(hal::read_bit(val, i), !(i % 2));
    }

    for(int set = 0; set < 32; ++set) {
        val = (1 << set);
        for(int i = 0; i < 32; ++i) {
            EXPECT_EQ(hal::read_bit(val, i), (i == set));
        }
    }

    uint8_t val2 = 0xA9;
    EXPECT_EQ(hal::read_bit(val2, 0), 1);
    EXPECT_EQ(hal::read_bit(val2, 1), 0);
    EXPECT_EQ(hal::read_bit(val2, 2), 0);
    EXPECT_EQ(hal::read_bit(val2, 3), 1);
    EXPECT_EQ(hal::read_bit(val2, 4), 0);
    EXPECT_EQ(hal::read_bit(val2, 5), 1);
    EXPECT_EQ(hal::read_bit(val2, 6), 0);
    EXPECT_EQ(hal::read_bit(val2, 7), 1);
}
