#include <cmath>
#include <cstdio>
#include <queue>

#include "../tests.h"
#include "unity.h"

TEST_GROUP(compile_time);

using namespace hal::libs;

template<int base, int exp>
struct test {
    static const bool value = ((power<base, exp>::value == std::pow(base, exp)) &&
                               test<base, exp - 1>::value);
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
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<0>), 1);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<8>), 1);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<9>), 2);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<16>), 2);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<17>), 4);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<32>), 4);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<33>), 8);
    TEST_ASSERT_EQUAL_INT(sizeof(type_with_bits<64>), 8);
}

template<int start, int length>
void bit_maskTest(uint8_t size, uint64_t value) {
    constexpr auto res = bit_mask<start, length>();
    TEST_ASSERT_EQUAL(size, sizeof(res));
    TEST_ASSERT_EQUAL(value, res);

    TEST_ASSERT_EQUAL(value, bit_mask(start, length));
}

TEST(compile_time, bit_mask_at_zero) {
    bit_maskTest<0, 0>(1, 0);
    bit_maskTest<0, 3>(1, 0b111);
    bit_maskTest<0, 4>(1, 0b1111);
    bit_maskTest<0, 8>(1, 0xFFU);
    bit_maskTest<0, 16>(2, 0xFFFF);
    bit_maskTest<0, 24>(4, 0xFFFFFF);
    bit_maskTest<0, 32>(4, 0xFFFFFFFF);
    bit_maskTest<0, 40>(8, 0xFFFFFFFFFFULL);
    bit_maskTest<0, 48>(8, 0xFFFFFFFFFFFFULL);
    bit_maskTest<0, 56>(8, 0xFFFFFFFFFFFFFFULL);
    bit_maskTest<0, 64>(8, 0xFFFFFFFFFFFFFFFFULL);
}

TEST(compile_time, bit_mask) {
    bit_maskTest<1, 1>(1, 0b10);
    bit_maskTest<1, 2>(1, 0b110);
    bit_maskTest<5, 2>(1, 0b110'0000);
    bit_maskTest<5, 3>(1, 0b1110'0000);
    bit_maskTest<7, 3>(2, 0b11'1000'0000);
    bit_maskTest<13, 2>(2, 0b110'0000'0000'0000);
    bit_maskTest<13, 3>(2, 0b1110'0000'0000'0000);
    bit_maskTest<13, 4>(4, 0b1'1110'0000'0000'0000);
    bit_maskTest<14, 3>(4, 0b1'1100'0000'0000'0000);
    bit_maskTest<14, 10>(4, 0b1111'1111'1100'0000'0000'0000);
    bit_maskTest<17, 10>(4, 0b111'1111'1110'0000'0000'0000'0000);
    bit_maskTest<17, 15>(4, 0b1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<17, 16>(8, 0b1'1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<18, 15>(8, 0b1'1111'1111'1111'1100'0000'0000'0000'0000UL);
    bit_maskTest<17, 20>(8, 0b1'1111'1111'1111'1111'1110'0000'0000'0000'0000UL);
    bit_maskTest<18, 21>(8, 0b111'1111'1111'1111'1111'1100'0000'0000'0000'0000UL);
}

template<int start, int length, int size>
void test_read_with_bit_mask(uint64_t value, uint64_t result) {
    auto read = read_mask<start, length>(value);
    TEST_ASSERT_EQUAL(size, sizeof(read));
    TEST_ASSERT_EQUAL(result, read);

    TEST_ASSERT_EQUAL(result, read_mask(start, length, value));
}

TEST(compile_time, read_with_bit_mask) {
    constexpr uint32_t x = 0b01011101101011110100010000111010;

    test_read_with_bit_mask<0, 0, 1>(x, 0);
    test_read_with_bit_mask<1, 0, 1>(x, 0);
    test_read_with_bit_mask<2, 0, 1>(x, 0);
    test_read_with_bit_mask<3, 0, 1>(x, 0);
    test_read_with_bit_mask<4, 0, 1>(x, 0);
    test_read_with_bit_mask<5, 0, 1>(x, 0);
    test_read_with_bit_mask<6, 0, 1>(x, 0);
    test_read_with_bit_mask<7, 0, 1>(x, 0);
    test_read_with_bit_mask<8, 0, 1>(x, 0);
    test_read_with_bit_mask<9, 0, 1>(x, 0);
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
    test_read_with_bit_mask<9, 1, 1>(x, 0);
    test_read_with_bit_mask<8, 1, 1>(x, 0);
    test_read_with_bit_mask<7, 1, 1>(x, 0);
    test_read_with_bit_mask<6, 1, 1>(x, 0);
    test_read_with_bit_mask<5, 1, 1>(x, 1);
    test_read_with_bit_mask<4, 1, 1>(x, 1);
    test_read_with_bit_mask<3, 1, 1>(x, 1);
    test_read_with_bit_mask<2, 1, 1>(x, 0);
    test_read_with_bit_mask<1, 1, 1>(x, 1);
    test_read_with_bit_mask<0, 1, 1>(x, 0);

    test_read_with_bit_mask<0, 5, 1>(x, 0b11010);
    test_read_with_bit_mask<1, 5, 1>(x, 0b11101);
    test_read_with_bit_mask<0, 15, 2>(x, 0b100010000111010);
    test_read_with_bit_mask<1, 15, 2>(x, 0b010001000011101);
    test_read_with_bit_mask<3, 13, 2>(x, 0b0100010000111);

    test_read_with_bit_mask<4, 20, 4>(x, 0b10101111010001000011UL);
    test_read_with_bit_mask<5, 19, 4>(x, 0b1010111101000100001UL);
    test_read_with_bit_mask<5, 21, 4>(x, 0b011010111101000100001UL);
}

template<int start, int size>
void test_write_with_bit_mask(uint32_t& reg, uint32_t value, uint32_t expected) {
    write_mask<start, size>(reg, value);
    TEST_ASSERT_EQUAL(expected, reg);

    uint32_t reg_copy = reg;
    write_mask(start, size, reg_copy, value);
    TEST_ASSERT_EQUAL(expected, reg_copy);
}

TEST(compile_time, write_with_bit_mask) {
    uint32_t x = 0;

    test_write_with_bit_mask<0, 1>(x, 1, 1);

    test_write_with_bit_mask<1, 1>(x, 1, 0b11);

    test_write_with_bit_mask<4, 4>(x, 0b1101, 0b11010011);

    test_write_with_bit_mask<0, 3>(x, 0b101, 0b11010101);

    test_write_with_bit_mask<0, 5>(x, 0b101, 0b11000101);

    test_write_with_bit_mask<8, 5>(x, 0b11101, 0b1110111000101);

    test_write_with_bit_mask<9, 5>(x, 0b11101, 0b11101111000101);

    test_write_with_bit_mask<0, 16>(x, 0, 0);

    test_write_with_bit_mask<31, 1>(x, 1, 0x80000000UL);

    test_write_with_bit_mask<0, 31>(x, 0, 0x80000000UL);

    test_write_with_bit_mask<1, 30>(x, 0, 0x80000000UL);

    test_write_with_bit_mask<1, 5>(x, 0xA, 0x80000014UL);

    test_write_with_bit_mask<3, 29>(x, 0xFFFF01, 0x7FFF80C);
}

TEST(compile_time, write_bit) {
    uint32_t x = 0;

    write_bit<0>(x, 1);
    TEST_ASSERT_EQUAL(1, x);

    write_bit<1>(x, 1);
    TEST_ASSERT_EQUAL(0b11, x);

    write_bit<0>(x, 0);
    TEST_ASSERT_EQUAL(0b10, x);

    write_bit<1>(x, 0);
    TEST_ASSERT_EQUAL(0, x);

    write_bit<1>(x, 0);
    TEST_ASSERT_EQUAL(0, x);

    write_bit<1>(x, 5);
    TEST_ASSERT_EQUAL(0b10, x);

    x = 0xFFFFFFFF;
    write_bit<31>(x, 0);
    TEST_ASSERT_EQUAL(0x7FFFFFFFUL, x);
}

template<typename T, uint64_t value>
void test_type_for_value() {
    static_assert(std::is_same<type_for_value<value>, T>::value,
                  "type_for_value failed!");
}

TEST(compile_time, type_for_value) {
    test_type_for_value<uint8_t, 0>();
    test_type_for_value<uint8_t, 1>();
    test_type_for_value<uint8_t, 0xFF>();

    test_type_for_value<uint16_t, 0x100>();
    test_type_for_value<uint16_t, 0xFFFF>();

    test_type_for_value<uint32_t, 0x10000>();
    test_type_for_value<uint32_t, 0xFFFFFFFF>();

    test_type_for_value<uint64_t, 0x100000000>();
    test_type_for_value<uint64_t, 0xFFFFFFFFFFFFFFFF>();
}


TEST(compile_time, is_specialization_of) {
    static_assert(is_specialization_of<std::tuple<>, std::tuple>::value, "");
    static_assert(is_specialization_of<std::tuple<int>, std::tuple>::value, "");
    static_assert(
        is_specialization_of<std::tuple<int, float>, std::tuple>::value, "");

    static_assert(!is_specialization_of<int, std::tuple>::value, "");
    static_assert(!is_specialization_of<std::true_type, std::tuple>::value, "");

    static_assert(is_specialization_of<std::vector<int>, std::vector>::value, "");

    static_assert(!is_specialization_of<std::vector<float>, std::queue>::value, "");
}

template<int tag>
struct TypeCheckExecution {
    static bool executed;
    static constexpr auto id = tag;
};
template<int tag>
bool TypeCheckExecution<tag>::executed;


struct ExecutorMark {
    static bool status;
    static FIFO_data<int, 5> fifo;

    template<typename T>
    struct Exec {
        static void run() {
            T::executed = status;
            fifo.append(T::id);
        }
    };

    template<typename>
    static void check() {
        TEST_ASSERT_EQUAL(0, fifo.getLength());
    }

    template<typename XX, int Head, int... T>
    static void check() {
        TEST_ASSERT_EQUAL(sizeof...(T) + 1, fifo.getLength());
        TEST_ASSERT_EQUAL(Head, fifo.get());
        check<XX, T...>();
    }

    template<int Head, int... T>
    static void check() {
        TEST_ASSERT_EQUAL(sizeof...(T) + 1, fifo.getLength());
        TEST_ASSERT_EQUAL(Head, fifo.get());
        check<void, T...>();
    }
};
bool ExecutorMark::status;
FIFO_data<int, 5> ExecutorMark::fifo;

TEST(compile_time, for_each_tuple_type) {
    // empty
    for_each_tuple_type<ExecutorMark::Exec, std::tuple<>>();

    // 1 element
    TypeCheckExecution<10>::executed = true;

    ExecutorMark::status = false;
    for_each_tuple_type<ExecutorMark::Exec, std::tuple<TypeCheckExecution<10>>>();

    ExecutorMark::check<10>();
    TEST_ASSERT_FALSE(TypeCheckExecution<0>::executed);

    // 5 elements
    TypeCheckExecution<0>::executed   = true;
    TypeCheckExecution<100>::executed = true;
    TypeCheckExecution<7>::executed   = true;
    TypeCheckExecution<53>::executed  = true;
    TypeCheckExecution<157>::executed = true;

    ExecutorMark::status = false;
    for_each_tuple_type<ExecutorMark::Exec,
                        std::tuple<TypeCheckExecution<0>,
                                   TypeCheckExecution<100>,
                                   TypeCheckExecution<7>,
                                   TypeCheckExecution<53>,
                                   TypeCheckExecution<157>>>();

    ExecutorMark::check<0, 100, 7, 53, 157>();
    TEST_ASSERT_FALSE(TypeCheckExecution<0>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<100>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<7>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<53>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<157>::executed);
}


TEST(compile_time, for_each_type) {
    // 1 element
    TypeCheckExecution<0>::executed = true;

    ExecutorMark::status = false;
    for_each_type<ExecutorMark::Exec, TypeCheckExecution<0>>();

    TEST_ASSERT_FALSE(TypeCheckExecution<0>::executed);
    ExecutorMark::check<0>();

    // 5 elements
    TypeCheckExecution<0>::executed   = true;
    TypeCheckExecution<100>::executed = true;
    TypeCheckExecution<7>::executed   = true;
    TypeCheckExecution<53>::executed  = true;
    TypeCheckExecution<157>::executed = true;

    ExecutorMark::status = false;
    for_each_type<ExecutorMark::Exec,
                  TypeCheckExecution<0>,
                  TypeCheckExecution<100>,
                  TypeCheckExecution<7>,
                  TypeCheckExecution<53>,
                  TypeCheckExecution<157>>();

    ExecutorMark::check<0, 100, 7, 53, 157>();
    TEST_ASSERT_FALSE(TypeCheckExecution<0>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<100>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<7>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<53>::executed);
    TEST_ASSERT_FALSE(TypeCheckExecution<157>::executed);
}
