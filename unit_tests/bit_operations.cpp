#include "unity.h"
#include "tests.h"

#include <math.h>
#include "bit_operations.h"
#include <numeric>
#include <limits>

using namespace hal::libs;

TEST(bit_operations, set_bit) {
    uint32_t val = 0;
    for (int i = 0; i < 32; ++i) {
        val = 0;
        set_bit(val, i);
        EXPECT_EQ(val, (1UL << i));
    }
    val = 0;
    for (int i = 0; i < 32; ++i) {
        set_bit(val, i);
    }
    EXPECT_EQ(val, 0xFFFFFFFF);

    val = 0;
    for (int i = 0; i < 32; i += 2) {
        set_bit(val, i);
    }
    EXPECT_EQ(val, 0x55555555);

    val = 0;
    for (int i = 1; i < 32; i += 2) {
        set_bit(val, i);
    }
    EXPECT_EQ(val, 0xAAAAAAAA);

    val = 0;
    set_bit(val, 0);
    set_bit(val, 3);
    set_bit(val, 5);
    set_bit(val, 7);
    EXPECT_EQ(val, 0xA9);

    set_bit(val, 0+8);
    set_bit(val, 3+8);
    set_bit(val, 5+8);
    set_bit(val, 7+8);
    EXPECT_EQ(val, 0xA9A9);

    set_bit(val, 0+16);
    set_bit(val, 3+16);
    set_bit(val, 5+16);
    set_bit(val, 7+16);
    EXPECT_EQ(val, 0xA9A9A9);

    set_bit(val, 0+24);
    set_bit(val, 3+24);
    set_bit(val, 5+24);
    set_bit(val, 7+24);
    EXPECT_EQ(val, 0xA9A9A9A9);
}

TEST(bit_operations, set_bit_ptr) {
    uint32_t value = 0;
    uint32_t * val = &value;
    for (int i = 0; i < 32; ++i) {
        *val = 0;
        set_bit(val, i);
        EXPECT_EQ(*val, (1ULL << i));
    }
    *val = 0;
    for (int i = 0; i < 32; ++i) {
        set_bit(val, i);
    }
    EXPECT_EQ(*val, 0xFFFFFFFF);

    *val = 0;
    for (int i = 0; i < 32; i += 2) {
        set_bit(val, i);
    }
    EXPECT_EQ(*val, 0x55555555);

    *val = 0;
    for (int i = 1; i < 32; i += 2) {
        set_bit(val, i);
    }
    EXPECT_EQ(*val, 0xAAAAAAAA);

    *val = 0;
    set_bit(val, 0);
    set_bit(val, 3);
    set_bit(val, 5);
    set_bit(val, 7);
    EXPECT_EQ(*val, 0xA9);

    set_bit(val, 0+8);
    set_bit(val, 3+8);
    set_bit(val, 5+8);
    set_bit(val, 7+8);
    EXPECT_EQ(*val, 0xA9A9);

    set_bit(val, 0+16);
    set_bit(val, 3+16);
    set_bit(val, 5+16);
    set_bit(val, 7+16);
    EXPECT_EQ(*val, 0xA9A9A9);

    set_bit(val, 0+24);
    set_bit(val, 3+24);
    set_bit(val, 5+24);
    set_bit(val, 7+24);
    EXPECT_EQ(*val, 0xA9A9A9A9);
}

TEST(bit_operations, clear_bit) {
    uint32_t val = 0xFFFFFFFF;
    const auto MAX = std::numeric_limits<decltype(val)>::max();
    for (int i = 0; i < 32; ++i) {
        val = 0xFFFFFFFF;
        clear_bit(val, i);
        EXPECT_EQ(val, 0xFFFFFFFF-(1UL << i));
    }
    val = MAX;
    for (int i = 0; i < 32; ++i) {
        clear_bit(val, i);
    }
    EXPECT_EQ(val, 0);

    val = MAX;
    for (int i = 0; i < 32; i += 2) {
        clear_bit(val, i);
    }
    EXPECT_EQ(val, 0xAAAAAAAA);

    val = MAX;
    for (int i = 1; i < 32; i += 2) {
        clear_bit(val, i);
    }
    EXPECT_EQ(val, 0x55555555);

    val = MAX;
    clear_bit(val, 1);
    clear_bit(val, 2);
    clear_bit(val, 4);
    clear_bit(val, 6);
    EXPECT_EQ(val, 0xFFFFFFA9);

    clear_bit(val, 1+8);
    clear_bit(val, 2+8);
    clear_bit(val, 4+8);
    clear_bit(val, 6+8);
    EXPECT_EQ(val, 0xFFFFA9A9);

    clear_bit(val, 1+16);
    clear_bit(val, 2+16);
    clear_bit(val, 4+16);
    clear_bit(val, 6+16);
    EXPECT_EQ(val, 0xFFA9A9A9);

    clear_bit(val, 1+24);
    clear_bit(val, 2+24);
    clear_bit(val, 4+24);
    clear_bit(val, 6+24);
    EXPECT_EQ(val, 0xA9A9A9A9);
}

TEST(bit_operations, clear_bit_ptr) {
    uint32_t value = 0xFFFFFFFF;
    auto val = &value;
    const auto MAX = std::numeric_limits<decltype(value)>::max();
    for (int i = 0; i < 32; ++i) {
        *val = 0xFFFFFFFF;
        clear_bit(val, i);
        EXPECT_EQ(*val, 0xFFFFFFFF-(1UL << i));
    }
    *val = MAX;
    for (int i = 0; i < 32; ++i) {
        clear_bit(val, i);
    }
    EXPECT_EQ(*val, 0);

    *val = MAX;
    for (int i = 0; i < 32; i += 2) {
        clear_bit(val, i);
    }
    EXPECT_EQ(*val, 0xAAAAAAAA);

    *val = MAX;
    for (int i = 1; i < 32; i += 2) {
        clear_bit(val, i);
    }
    EXPECT_EQ(*val, 0x55555555);

    *val = MAX;
    clear_bit(val, 1);
    clear_bit(val, 2);
    clear_bit(val, 4);
    clear_bit(val, 6);
    EXPECT_EQ(*val, 0xFFFFFFA9);

    clear_bit(val, 1+8);
    clear_bit(val, 2+8);
    clear_bit(val, 4+8);
    clear_bit(val, 6+8);
    EXPECT_EQ(*val, 0xFFFFA9A9);

    clear_bit(val, 1+16);
    clear_bit(val, 2+16);
    clear_bit(val, 4+16);
    clear_bit(val, 6+16);
    EXPECT_EQ(*val, 0xFFA9A9A9);

    clear_bit(val, 1+24);
    clear_bit(val, 2+24);
    clear_bit(val, 4+24);
    clear_bit(val, 6+24);
    EXPECT_EQ(*val, 0xA9A9A9A9);
}

TEST(bit_operations, read_bit) {
    uint32_t val = 0;
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(read_bit(val, i), 0);
    }
    val = 0xFFFFFFFF;
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(read_bit(val, i), 1);
    }
    val = 0xAAAAAAAA;
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(read_bit(val, i), (i % 2));
    }
    val = 0x55555555;
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(read_bit(val, i), !(i % 2));
    }

    for (int set = 0; set < 32; ++set) {
        val = (1UL << set);
        for (int i = 0; i < 32; ++i) {
            EXPECT_EQ(read_bit(val, i), (i == set));
        }
    }

    uint8_t val2 = 0xA9;
    EXPECT_EQ(read_bit(val2, 0), 1);
    EXPECT_EQ(read_bit(val2, 1), 0);
    EXPECT_EQ(read_bit(val2, 2), 0);
    EXPECT_EQ(read_bit(val2, 3), 1);
    EXPECT_EQ(read_bit(val2, 4), 0);
    EXPECT_EQ(read_bit(val2, 5), 1);
    EXPECT_EQ(read_bit(val2, 6), 0);
    EXPECT_EQ(read_bit(val2, 7), 1);
}

TEST(bit_operations, read_bit_template) {
    uint8_t val2 = 0b10101010;
    EXPECT_EQ(read_bit<0>(val2), 0);
    EXPECT_EQ(read_bit<1>(val2), 1);
    EXPECT_EQ(read_bit<2>(val2), 0);
    EXPECT_EQ(read_bit<3>(val2), 1);
    EXPECT_EQ(read_bit<4>(val2), 0);
    EXPECT_EQ(read_bit<5>(val2), 1);
    EXPECT_EQ(read_bit<6>(val2), 0);
    EXPECT_EQ(read_bit<7>(val2), 1);

    uint32_t val3 = 0xFFFFFFF0;
    EXPECT_EQ(read_bit<0>(val3), 0);
    EXPECT_EQ(read_bit<31>(val3), 1);
}

template<int start, int length>
void bit_maskTest(uint8_t size, uint64_t value) {
    constexpr auto res = bit_mask<start, length>();
    EXPECT_EQ(size, sizeof(res));
    EXPECT_EQ(value, res);

    EXPECT_EQ(value, bit_mask(start, length));
}

TEST(compile_time, bit_mask_at_zero) {
    bit_maskTest<0,  0> (1, 0);
    bit_maskTest<0,  3> (1, 0b111);
    bit_maskTest<0,  4> (1, 0b1111);
    bit_maskTest<0,  8> (1, 0xFFU);
    bit_maskTest<0, 16>(2, 0xFFFF);
    bit_maskTest<0, 24>(4, 0xFFFFFF);
    bit_maskTest<0, 32>(4, 0xFFFFFFFF);
    bit_maskTest<0, 40>(8, 0xFFFFFFFFFFULL);
    bit_maskTest<0, 48>(8, 0xFFFFFFFFFFFFULL);
    bit_maskTest<0, 56>(8, 0xFFFFFFFFFFFFFFULL);
    bit_maskTest<0, 64>(8, 0xFFFFFFFFFFFFFFFFULL);
}

TEST(compile_time, bit_mask) {
    bit_maskTest<1,  1> (1,                                                  0b10);
    bit_maskTest<1,  2> (1,                                                 0b110);
    bit_maskTest<5,  2> (1,                                            0b110'0000);
    bit_maskTest<5,  3> (1,                                           0b1110'0000);
    bit_maskTest<7,  3> (2,                                        0b11'1000'0000);
    bit_maskTest<13, 2> (2,                                  0b110'0000'0000'0000);
    bit_maskTest<13, 3> (2,                                 0b1110'0000'0000'0000);
    bit_maskTest<13, 4> (4,                               0b1'1110'0000'0000'0000);
    bit_maskTest<14, 3> (4,                               0b1'1100'0000'0000'0000);
    bit_maskTest<14, 10> (4,                      0b1111'1111'1100'0000'0000'0000);
    bit_maskTest<17, 10> (4,                  0b111'1111'1110'0000'0000'0000'0000);
    bit_maskTest<17, 15> (4,            0b1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<17, 16> (8,          0b1'1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<18, 15> (8,          0b1'1111'1111'1111'1100'0000'0000'0000'0000UL);
    bit_maskTest<17, 20> (8,     0b1'1111'1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<18, 21> (8,   0b111'1111'1111'1111'1111'1100'0000'0000'0000'0000UL);
}

template<int start, int length, int size>
void test_read_with_bit_mask(uint64_t value, uint64_t result) {
    auto read = read_mask<start, length>(value);
    EXPECT_EQ(size, sizeof(read));
    EXPECT_EQ(result, read);

    EXPECT_EQ(result, read_mask(start, length, value));
}

TEST(compile_time, read_with_bit_mask) {
    constexpr uint32_t x = 0b01011101101011110100010000111010;

    test_read_with_bit_mask< 0, 0, 1>(x, 0);
    test_read_with_bit_mask< 1, 0, 1>(x, 0);
    test_read_with_bit_mask< 2, 0, 1>(x, 0);
    test_read_with_bit_mask< 3, 0, 1>(x, 0);
    test_read_with_bit_mask< 4, 0, 1>(x, 0);
    test_read_with_bit_mask< 5, 0, 1>(x, 0);
    test_read_with_bit_mask< 6, 0, 1>(x, 0);
    test_read_with_bit_mask< 7, 0, 1>(x, 0);
    test_read_with_bit_mask< 8, 0, 1>(x, 0);
    test_read_with_bit_mask< 9, 0, 1>(x, 0);
    test_read_with_bit_mask<10, 0, 1>(x, 0);
    test_read_with_bit_mask<11, 0, 1>(x, 0);
    test_read_with_bit_mask<12, 0, 1>(x, 0);
    test_read_with_bit_mask<13, 0, 1>(x, 0);
    test_read_with_bit_mask<14, 0, 1>(x, 0);
    test_read_with_bit_mask<15, 0, 1>(x, 0);
    test_read_with_bit_mask<16, 0, 1>(x, 0);
    test_read_with_bit_mask<17, 0, 1>(x, 0);
    test_read_with_bit_mask<18, 0, 1>(x, 0);
    test_read_with_bit_mask<19, 0, 1>(x, 0);
    test_read_with_bit_mask<20, 0, 1>(x, 0);
    test_read_with_bit_mask<21, 0, 1>(x, 0);
    test_read_with_bit_mask<22, 0, 1>(x, 0);
    test_read_with_bit_mask<23, 0, 1>(x, 0);
    test_read_with_bit_mask<24, 0, 1>(x, 0);
    test_read_with_bit_mask<25, 0, 1>(x, 0);
    test_read_with_bit_mask<26, 0, 1>(x, 0);
    test_read_with_bit_mask<27, 0, 1>(x, 0);
    test_read_with_bit_mask<28, 0, 1>(x, 0);
    test_read_with_bit_mask<29, 0, 1>(x, 0);
    test_read_with_bit_mask<30, 0, 1>(x, 0);
    test_read_with_bit_mask<31, 0, 1>(x, 0);

    test_read_with_bit_mask<31, 1, 1>(x, 0);
    test_read_with_bit_mask<30, 1, 1>(x, 1);
    test_read_with_bit_mask<29, 1, 1>(x, 0);
    test_read_with_bit_mask<28, 1, 1>(x, 1);
    test_read_with_bit_mask<27, 1, 1>(x, 1);
    test_read_with_bit_mask<26, 1, 1>(x, 1);
    test_read_with_bit_mask<25, 1, 1>(x, 0);
    test_read_with_bit_mask<24, 1, 1>(x, 1);
    test_read_with_bit_mask<23, 1, 1>(x, 1);
    test_read_with_bit_mask<22, 1, 1>(x, 0);
    test_read_with_bit_mask<21, 1, 1>(x, 1);
    test_read_with_bit_mask<20, 1, 1>(x, 0);
    test_read_with_bit_mask<19, 1, 1>(x, 1);
    test_read_with_bit_mask<18, 1, 1>(x, 1);
    test_read_with_bit_mask<17, 1, 1>(x, 1);
    test_read_with_bit_mask<16, 1, 1>(x, 1);
    test_read_with_bit_mask<15, 1, 1>(x, 0);
    test_read_with_bit_mask<14, 1, 1>(x, 1);
    test_read_with_bit_mask<13, 1, 1>(x, 0);
    test_read_with_bit_mask<12, 1, 1>(x, 0);
    test_read_with_bit_mask<11, 1, 1>(x, 0);
    test_read_with_bit_mask<10, 1, 1>(x, 1);
    test_read_with_bit_mask< 9, 1, 1>(x, 0);
    test_read_with_bit_mask< 8, 1, 1>(x, 0);
    test_read_with_bit_mask< 7, 1, 1>(x, 0);
    test_read_with_bit_mask< 6, 1, 1>(x, 0);
    test_read_with_bit_mask< 5, 1, 1>(x, 1);
    test_read_with_bit_mask< 4, 1, 1>(x, 1);
    test_read_with_bit_mask< 3, 1, 1>(x, 1);
    test_read_with_bit_mask< 2, 1, 1>(x, 0);
    test_read_with_bit_mask< 1, 1, 1>(x, 1);
    test_read_with_bit_mask< 0, 1, 1>(x, 0);

    test_read_with_bit_mask<0, 5, 1>(x, 0b11010);
    test_read_with_bit_mask<1, 5, 1>(x, 0b11101);
    test_read_with_bit_mask<0, 15, 2>(x, 0b100010000111010);
    test_read_with_bit_mask<1, 15, 2>(x, 0b010001000011101);
    test_read_with_bit_mask<3, 13, 2>(x, 0b0100010000111);

    test_read_with_bit_mask<4, 20, 4>(x, 0b10101111010001000011UL);
    test_read_with_bit_mask<5, 19, 4>(x, 0b1010111101000100001UL);
    test_read_with_bit_mask<5, 21, 4>(x, 0b011010111101000100001UL);
}

TEST(compile_time, write_with_bit_mask) {
    uint32_t x = 0;

    write_mask<0, 1>(x, 1);
    EXPECT_EQ(1, x);

    write_mask<1, 1>(x, 1);
    EXPECT_EQ(0b11, x);

    write_mask<4, 4>(x, 0b1101);
    EXPECT_EQ(0b11010011, x);

    write_mask<0, 3>(x, 0b101);
    EXPECT_EQ(0b11010101, x);

    write_mask<0, 5>(x, 0b101);
    EXPECT_EQ(0b11000101, x);

    write_mask<8, 5>(x, 0b11101);
    EXPECT_EQ(0b1110111000101, x);

    write_mask<9, 5>(x, 0b11101);
    EXPECT_EQ(0b11101111000101, x);

    write_mask<0, 16>(x, 0);
    EXPECT_EQ(0, x);

    write_mask<31, 1>(x, 1);
    EXPECT_EQ(0x80000000UL, x);

    write_mask<0, 31>(x, 0);
    EXPECT_EQ(0x80000000UL, x);

    write_mask<1, 30>(x, 0);
    EXPECT_EQ(0x80000000UL, x);

    write_mask<1, 5>(x, 0xA);
    EXPECT_EQ(0x80000014UL, x);

    write_mask<3, 29>(x, 0xFFFF01);
    EXPECT_EQ(0x7FFF80C, x);
}

TEST(compile_time, write_bit) {
    uint32_t x = 0;

    write_bit<0>(x, 1);
    EXPECT_EQ(1, x);

    write_bit<1>(x, 1);
    EXPECT_EQ(0b11, x);

    write_bit<0>(x, 0);
    EXPECT_EQ(0b10, x);

    write_bit<1>(x, 0);
    EXPECT_EQ(0, x);

    write_bit<1>(x, 0);
    EXPECT_EQ(0, x);

    x = 0xFFFFFFFF;
    write_bit<31>(x, 0);
    EXPECT_EQ(0x7FFFFFFFUL, x);
}
DEFINE_TESTSUITE(bit_operations);
