#include "tests.h"
#include <cstring>

TEST_GROUP(fifo);

using hal::libs::FIFO_data;

TEST(fifo, simple) {
    FIFO_data<int, 10> fifo;
    fifo.append(1);
    TEST_ASSERT_EQUAL(fifo.get(), 1);
}

struct foo {
    foo() : i{0} {}
    // explicit foo(int val) : i{val} {
    // }
    int i;
};

TEST(fifo, struct) {
    FIFO_data<foo, 10> fifo;
    foo f;
    f.i = 1;
    fifo.append(f);
    TEST_ASSERT_EQUAL(fifo.get().i, 1);
    TEST_ASSERT_EQUAL(fifo.get().i, 0);
}

TEST(fifo, fill) {
    FIFO_data<int, 10> fifo;
    TEST_ASSERT_FALSE(fifo.isFull());
    TEST_ASSERT_EQUAL(fifo.getLength(), 0);
    TEST_ASSERT_TRUE(fifo.isEmpty());
    TEST_ASSERT_FALSE(fifo.isNotEmpty());
    TEST_ASSERT_EQUAL(fifo.getSize(), 10);
    TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 10);


    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT_FALSE(fifo.isFull());

        TEST_ASSERT_TRUE(fifo.append(i));

        TEST_ASSERT_EQUAL(fifo.getLength(), i+1);
        TEST_ASSERT_FALSE(fifo.isEmpty());
        TEST_ASSERT_TRUE(fifo.isNotEmpty());
        TEST_ASSERT_EQUAL(fifo.getSize(), 10);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 10-i-1);
    }
    TEST_ASSERT_TRUE(fifo.isFull());
    TEST_ASSERT_EQUAL(fifo.getLength(), 10);
    TEST_ASSERT_FALSE(fifo.isEmpty());
    TEST_ASSERT_TRUE(fifo.isNotEmpty());
    TEST_ASSERT_EQUAL(fifo.getSize(), 10);
    TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 0);

    TEST_ASSERT_FALSE(fifo.append(100));

    TEST_ASSERT_TRUE(fifo.isFull());
    TEST_ASSERT_EQUAL(fifo.getLength(), 10);
    TEST_ASSERT_FALSE(fifo.isEmpty());
    TEST_ASSERT_TRUE(fifo.isNotEmpty());
    TEST_ASSERT_EQUAL(fifo.getSize(), 10);
    TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 0);

    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT_FALSE(fifo.isEmpty());
        TEST_ASSERT_TRUE(fifo.isNotEmpty());

        TEST_ASSERT_EQUAL(fifo.get(), i);

        TEST_ASSERT_FALSE(fifo.isFull());
        TEST_ASSERT_EQUAL(fifo.getLength(), 10-1-i);
        TEST_ASSERT_EQUAL(fifo.getSize(), 10);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), i+1);
    }

    TEST_ASSERT_FALSE(fifo.isFull());
    TEST_ASSERT_EQUAL(fifo.getLength(), 0);
    TEST_ASSERT_TRUE(fifo.isEmpty());
    TEST_ASSERT_FALSE(fifo.isNotEmpty());
    TEST_ASSERT_EQUAL(fifo.getSize(), 10);
    TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 10);
}



TEST(fifo, pingpong) {
    FIFO_data<int, 11> fifo;
    TEST_ASSERT_FALSE(fifo.isFull());
    TEST_ASSERT_EQUAL(fifo.getLength(), 0);
    TEST_ASSERT_TRUE(fifo.isEmpty());
    TEST_ASSERT_FALSE(fifo.isNotEmpty());
    TEST_ASSERT_EQUAL(fifo.getSize(), 11);
    TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 11);

    int c_w = 0, c_r = 0;

    for (int t = 0; t < 100; ++t) {
        for (int i = 0; i < 7; ++i) {
            fifo.append(c_w++);
        }

        TEST_ASSERT_FALSE(fifo.isFull());
        TEST_ASSERT_EQUAL(fifo.getLength(), 7);
        TEST_ASSERT_FALSE(fifo.isEmpty());
        TEST_ASSERT_TRUE(fifo.isNotEmpty());
        TEST_ASSERT_EQUAL(fifo.getSize(), 11);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 4);

        for (int i = 0; i < 7; ++i) {
            TEST_ASSERT_EQUAL(fifo.get(), c_r++);
        }

        TEST_ASSERT_FALSE(fifo.isFull());
        TEST_ASSERT_EQUAL(fifo.getLength(), 0);
        TEST_ASSERT_TRUE(fifo.isEmpty());
        TEST_ASSERT_FALSE(fifo.isNotEmpty());
        TEST_ASSERT_EQUAL(fifo.getSize(), 11);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 11);
    }
}

TEST(fifo, arrays) {
    FIFO_data<int, 11> fifo;

    int c_w = 0, c_r = 0;
    int data_w[7];
    int data_r[7];

    for (int t = 0; t < 100; ++t) {
        for (int i = 0; i < 7; ++i) {
            data_w[i] = c_w++;
        }
        fifo.write(data_w, 7);

        TEST_ASSERT_FALSE(fifo.isFull());
        TEST_ASSERT_EQUAL(fifo.getLength(), 7);
        TEST_ASSERT_FALSE(fifo.isEmpty());
        TEST_ASSERT_TRUE(fifo.isNotEmpty());
        TEST_ASSERT_EQUAL(fifo.getSize(), 11);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 4);

        fifo.read(data_r, 7);
        for (int i = 0; i < 7; ++i) {
            TEST_ASSERT_EQUAL(data_r[i], c_r++);
        }

        TEST_ASSERT_FALSE(fifo.isFull());
        TEST_ASSERT_EQUAL(fifo.getLength(), 0);
        TEST_ASSERT_TRUE(fifo.isEmpty());
        TEST_ASSERT_FALSE(fifo.isNotEmpty());
        TEST_ASSERT_EQUAL(fifo.getSize(), 11);
        TEST_ASSERT_EQUAL(fifo.getFreeSpace(), 11);
    }
}
