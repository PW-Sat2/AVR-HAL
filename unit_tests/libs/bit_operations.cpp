#include "../tests.h"
#include "unity.h"

#include <math.h>
#include <limits>
#include <numeric>

using namespace hal::libs;

TEST_GROUP(bit_operations);

TEST(bit_operations, set_bit) {
    uint32_t val = 0;
    for (int i = 0; i < 32; ++i) {
        val = 0;
        set_bit(val, i);
        TEST_ASSERT_EQUAL(val, (1UL << i));
    }
    val = 0;
    for (int i = 0; i < 32; ++i) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0xFFFFFFFF);

    val = 0;
    for (int i = 0; i < 32; i += 2) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0x55555555);

    val = 0;
    for (int i = 1; i < 32; i += 2) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0xAAAAAAAA);

    val = 0;
    set_bit(val, 0);
    set_bit(val, 3);
    set_bit(val, 5);
    set_bit(val, 7);
    TEST_ASSERT_EQUAL(val, 0xA9);

    set_bit(val, 0 + 8);
    set_bit(val, 3 + 8);
    set_bit(val, 5 + 8);
    set_bit(val, 7 + 8);
    TEST_ASSERT_EQUAL(val, 0xA9A9);

    set_bit(val, 0 + 16);
    set_bit(val, 3 + 16);
    set_bit(val, 5 + 16);
    set_bit(val, 7 + 16);
    TEST_ASSERT_EQUAL(val, 0xA9A9A9);

    set_bit(val, 0 + 24);
    set_bit(val, 3 + 24);
    set_bit(val, 5 + 24);
    set_bit(val, 7 + 24);
    TEST_ASSERT_EQUAL(val, 0xA9A9A9A9);
}

TEST(bit_operations, set_bit_ptr) {
    uint32_t value = 0;
    uint32_t* val  = &value;
    for (int i = 0; i < 32; ++i) {
        *val = 0;
        set_bit(val, i);
        TEST_ASSERT_EQUAL(*val, (1ULL << i));
    }
    *val = 0;
    for (int i = 0; i < 32; ++i) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0xFFFFFFFF);

    *val = 0;
    for (int i = 0; i < 32; i += 2) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0x55555555);

    *val = 0;
    for (int i = 1; i < 32; i += 2) {
        set_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0xAAAAAAAA);

    *val = 0;
    set_bit(val, 0);
    set_bit(val, 3);
    set_bit(val, 5);
    set_bit(val, 7);
    TEST_ASSERT_EQUAL(*val, 0xA9);

    set_bit(val, 0 + 8);
    set_bit(val, 3 + 8);
    set_bit(val, 5 + 8);
    set_bit(val, 7 + 8);
    TEST_ASSERT_EQUAL(*val, 0xA9A9);

    set_bit(val, 0 + 16);
    set_bit(val, 3 + 16);
    set_bit(val, 5 + 16);
    set_bit(val, 7 + 16);
    TEST_ASSERT_EQUAL(*val, 0xA9A9A9);

    set_bit(val, 0 + 24);
    set_bit(val, 3 + 24);
    set_bit(val, 5 + 24);
    set_bit(val, 7 + 24);
    TEST_ASSERT_EQUAL(*val, 0xA9A9A9A9);
}

TEST(bit_operations, clear_bit) {
    uint32_t val   = 0xFFFFFFFF;
    const auto MAX = std::numeric_limits<decltype(val)>::max();
    for (int i = 0; i < 32; ++i) {
        val = 0xFFFFFFFF;
        clear_bit(val, i);
        TEST_ASSERT_EQUAL(val, 0xFFFFFFFF - (1UL << i));
    }
    val = MAX;
    for (int i = 0; i < 32; ++i) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0);

    val = MAX;
    for (int i = 0; i < 32; i += 2) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0xAAAAAAAA);

    val = MAX;
    for (int i = 1; i < 32; i += 2) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(val, 0x55555555);

    val = MAX;
    clear_bit(val, 1);
    clear_bit(val, 2);
    clear_bit(val, 4);
    clear_bit(val, 6);
    TEST_ASSERT_EQUAL(val, 0xFFFFFFA9);

    clear_bit(val, 1 + 8);
    clear_bit(val, 2 + 8);
    clear_bit(val, 4 + 8);
    clear_bit(val, 6 + 8);
    TEST_ASSERT_EQUAL(val, 0xFFFFA9A9);

    clear_bit(val, 1 + 16);
    clear_bit(val, 2 + 16);
    clear_bit(val, 4 + 16);
    clear_bit(val, 6 + 16);
    TEST_ASSERT_EQUAL(val, 0xFFA9A9A9);

    clear_bit(val, 1 + 24);
    clear_bit(val, 2 + 24);
    clear_bit(val, 4 + 24);
    clear_bit(val, 6 + 24);
    TEST_ASSERT_EQUAL(val, 0xA9A9A9A9);
}

TEST(bit_operations, clear_bit_ptr) {
    uint32_t value = 0xFFFFFFFF;
    auto val       = &value;
    const auto MAX = std::numeric_limits<decltype(value)>::max();
    for (int i = 0; i < 32; ++i) {
        *val = 0xFFFFFFFF;
        clear_bit(val, i);
        TEST_ASSERT_EQUAL(*val, 0xFFFFFFFF - (1UL << i));
    }
    *val = MAX;
    for (int i = 0; i < 32; ++i) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0);

    *val = MAX;
    for (int i = 0; i < 32; i += 2) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0xAAAAAAAA);

    *val = MAX;
    for (int i = 1; i < 32; i += 2) {
        clear_bit(val, i);
    }
    TEST_ASSERT_EQUAL(*val, 0x55555555);

    *val = MAX;
    clear_bit(val, 1);
    clear_bit(val, 2);
    clear_bit(val, 4);
    clear_bit(val, 6);
    TEST_ASSERT_EQUAL(*val, 0xFFFFFFA9);

    clear_bit(val, 1 + 8);
    clear_bit(val, 2 + 8);
    clear_bit(val, 4 + 8);
    clear_bit(val, 6 + 8);
    TEST_ASSERT_EQUAL(*val, 0xFFFFA9A9);

    clear_bit(val, 1 + 16);
    clear_bit(val, 2 + 16);
    clear_bit(val, 4 + 16);
    clear_bit(val, 6 + 16);
    TEST_ASSERT_EQUAL(*val, 0xFFA9A9A9);

    clear_bit(val, 1 + 24);
    clear_bit(val, 2 + 24);
    clear_bit(val, 4 + 24);
    clear_bit(val, 6 + 24);
    TEST_ASSERT_EQUAL(*val, 0xA9A9A9A9);
}

TEST(bit_operations, read_bit) {
    uint32_t val = 0;
    for (int i = 0; i < 32; ++i) {
        TEST_ASSERT_EQUAL(read_bit(val, i), 0);
    }
    val = 0xFFFFFFFF;
    for (int i = 0; i < 32; ++i) {
        TEST_ASSERT_EQUAL(read_bit(val, i), 1);
    }
    val = 0xAAAAAAAA;
    for (int i = 0; i < 32; ++i) {
        TEST_ASSERT_EQUAL(read_bit(val, i), (i % 2));
    }
    val = 0x55555555;
    for (int i = 0; i < 32; ++i) {
        TEST_ASSERT_EQUAL(read_bit(val, i), !(i % 2));
    }

    for (int set = 0; set < 32; ++set) {
        val = (1UL << set);
        for (int i = 0; i < 32; ++i) {
            TEST_ASSERT_EQUAL(read_bit(val, i), (i == set));
        }
    }

    uint8_t val2 = 0xA9;
    TEST_ASSERT_EQUAL(read_bit(val2, 0), 1);
    TEST_ASSERT_EQUAL(read_bit(val2, 1), 0);
    TEST_ASSERT_EQUAL(read_bit(val2, 2), 0);
    TEST_ASSERT_EQUAL(read_bit(val2, 3), 1);
    TEST_ASSERT_EQUAL(read_bit(val2, 4), 0);
    TEST_ASSERT_EQUAL(read_bit(val2, 5), 1);
    TEST_ASSERT_EQUAL(read_bit(val2, 6), 0);
    TEST_ASSERT_EQUAL(read_bit(val2, 7), 1);
}

TEST(bit_operations, read_bit_template) {
    uint8_t val2 = 0b10101010;
    TEST_ASSERT_EQUAL(read_bit<0>(val2), 0);
    TEST_ASSERT_EQUAL(read_bit<1>(val2), 1);
    TEST_ASSERT_EQUAL(read_bit<2>(val2), 0);
    TEST_ASSERT_EQUAL(read_bit<3>(val2), 1);
    TEST_ASSERT_EQUAL(read_bit<4>(val2), 0);
    TEST_ASSERT_EQUAL(read_bit<5>(val2), 1);
    TEST_ASSERT_EQUAL(read_bit<6>(val2), 0);
    TEST_ASSERT_EQUAL(read_bit<7>(val2), 1);

    uint32_t val3 = 0xFFFFFFF0;
    TEST_ASSERT_EQUAL(read_bit<0>(val3), 0);
    TEST_ASSERT_EQUAL(read_bit<31>(val3), 1);
}

TEST(bit_operations, low_byte) {
    TEST_ASSERT_EQUAL_HEX32(0xBC, low_byte(0xBC));
    TEST_ASSERT_EQUAL_HEX32(0xAD, low_byte(0xBCAD));
    TEST_ASSERT_EQUAL_HEX32(0x12, low_byte(0xBCAD12));
    TEST_ASSERT_EQUAL_HEX32(0x58, low_byte(0xBCAD1258));
    TEST_ASSERT_EQUAL_HEX32(0x47, low_byte(0xBCAD125847));
    TEST_ASSERT_EQUAL_HEX32(0x9F, low_byte(0xBCAD1258479F));
    TEST_ASSERT_EQUAL_HEX32(0xE7, low_byte(0xBCAD1258479FE7));
    TEST_ASSERT_EQUAL_HEX32(0x5A, low_byte(0xBCAD1258479FE75A));

    constexpr uint16_t val = 0x18FB;
    TEST_ASSERT_EQUAL_HEX32(0xFB, low_byte(val));

    constexpr uint32_t val2 = 0x12345678;
    TEST_ASSERT_EQUAL_HEX32(0x78, low_byte(val2));
}

template<typename T, T value, uint8_t result>
void test_high_byte() {
    TEST_ASSERT_EQUAL_HEX32(result, high_byte(value));
}

TEST(bit_operations, high_byte) {
    test_high_byte<uint8_t, 1, 1>();
    test_high_byte<uint8_t, 0x75, 0x75>();

    test_high_byte<uint8_t, 0xBC, 0xBC>();
    test_high_byte<uint16_t, 0xADBC, 0xAD>();
    test_high_byte<uint32_t, 0x12ADBC, 0x00>();
    test_high_byte<uint32_t, 0x5812ADBC, 0x58>();
    test_high_byte<uint64_t, 0x475812ADBC, 0x00>();
    test_high_byte<uint64_t, 0xE79F5812ADBC, 0x00>();
    test_high_byte<uint64_t, 0x4BE79F5812ADBC, 0x00>();
    test_high_byte<uint64_t, 0x5A4BE79F5812ADBC, 0x5A>();
}
