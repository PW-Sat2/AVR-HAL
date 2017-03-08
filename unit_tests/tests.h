#ifndef UNIT_TESTS_AVR_TESTS_H_
#define UNIT_TESTS_AVR_TESTS_H_

#include "unity.h"
#include "fifo.h"


static hal::libs::FIFO_data<void (*)(), 100> data;


#define TEST(a, b)               \
void TEST_ ## a ## b();          \
struct TEST_ ## a ## b ## _str { \
    TEST_ ## a ## b ## _str() {  \
        data.append(TEST_ ## a ## b);   \
    }                            \
} TEST_ ## a ## b ## _str_inst;  \
void TEST_ ## a ## b ()

#define RUN(a, b) RUN_TEST(TEST_ ## a ## b)

#define DEFINE_TESTSUITE(a)         \
bool TEST_ ## a() {                 \
    UNITY_BEGIN();                  \
    while(data.getLength() > 0) {   \
        RUN_TEST(data.get());       \
    }                               \
    return UNITY_END();             \
}

#define RUN_TESTSUITE(a) \
bool TEST_ ## a();       \
TEST_ ## a()

#define EXPECT_EQ TEST_ASSERT_EQUAL
#define EXPECT_NE TEST_ASSERT_NOT_EQUAL
#define EXPECT_FALSE TEST_ASSERT_FALSE
#define EXPECT_TRUE TEST_ASSERT_TRUE
#define EXPECT_FLOAT_EQ TEST_ASSERT_EQUAL_FLOAT
#define EXPECT_STREQ TEST_ASSERT_EQUAL_STRING

#endif  // UNIT_TESTS_AVR_TESTS_H_