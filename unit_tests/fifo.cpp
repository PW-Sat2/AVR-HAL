#include "tests.h"
#include <cstring>

#include "fifo.h"


using hal::libs::FIFO_data;

TEST(fifo, simple) {
    FIFO_data<int, 10> fifo;
    fifo.append(1);
    EXPECT_EQ(fifo.get(), 1);
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
    EXPECT_EQ(fifo.get().i, 1);
    EXPECT_EQ(fifo.get().i, 0);
}

TEST(fifo, fill) {
    FIFO_data<int, 10> fifo;
    EXPECT_FALSE(fifo.isFull());
    EXPECT_EQ(fifo.getLength(), 0);
    EXPECT_TRUE(fifo.isEmpty());
    EXPECT_FALSE(fifo.isNotEmpty());
    EXPECT_EQ(fifo.getSize(), 10);
    EXPECT_EQ(fifo.getFreeSpace(), 10);


    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(fifo.isFull());

        EXPECT_TRUE(fifo.append(i));

        EXPECT_EQ(fifo.getLength(), i+1);
        EXPECT_FALSE(fifo.isEmpty());
        EXPECT_TRUE(fifo.isNotEmpty());
        EXPECT_EQ(fifo.getSize(), 10);
        EXPECT_EQ(fifo.getFreeSpace(), 10-i-1);
    }
    EXPECT_TRUE(fifo.isFull());
    EXPECT_EQ(fifo.getLength(), 10);
    EXPECT_FALSE(fifo.isEmpty());
    EXPECT_TRUE(fifo.isNotEmpty());
    EXPECT_EQ(fifo.getSize(), 10);
    EXPECT_EQ(fifo.getFreeSpace(), 0);

    EXPECT_FALSE(fifo.append(100));

    EXPECT_TRUE(fifo.isFull());
    EXPECT_EQ(fifo.getLength(), 10);
    EXPECT_FALSE(fifo.isEmpty());
    EXPECT_TRUE(fifo.isNotEmpty());
    EXPECT_EQ(fifo.getSize(), 10);
    EXPECT_EQ(fifo.getFreeSpace(), 0);

    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(fifo.isEmpty());
        EXPECT_TRUE(fifo.isNotEmpty());

        EXPECT_EQ(fifo.get(), i);

        EXPECT_FALSE(fifo.isFull());
        EXPECT_EQ(fifo.getLength(), 10-1-i);
        EXPECT_EQ(fifo.getSize(), 10);
        EXPECT_EQ(fifo.getFreeSpace(), i+1);
    }

    EXPECT_FALSE(fifo.isFull());
    EXPECT_EQ(fifo.getLength(), 0);
    EXPECT_TRUE(fifo.isEmpty());
    EXPECT_FALSE(fifo.isNotEmpty());
    EXPECT_EQ(fifo.getSize(), 10);
    EXPECT_EQ(fifo.getFreeSpace(), 10);
}



TEST(fifo, pingpong) {
    FIFO_data<int, 11> fifo;
    EXPECT_FALSE(fifo.isFull());
    EXPECT_EQ(fifo.getLength(), 0);
    EXPECT_TRUE(fifo.isEmpty());
    EXPECT_FALSE(fifo.isNotEmpty());
    EXPECT_EQ(fifo.getSize(), 11);
    EXPECT_EQ(fifo.getFreeSpace(), 11);

    int c_w = 0, c_r = 0;

    for (int t = 0; t < 100; ++t) {
        for (int i = 0; i < 7; ++i) {
            fifo.append(c_w++);
        }

        EXPECT_FALSE(fifo.isFull());
        EXPECT_EQ(fifo.getLength(), 7);
        EXPECT_FALSE(fifo.isEmpty());
        EXPECT_TRUE(fifo.isNotEmpty());
        EXPECT_EQ(fifo.getSize(), 11);
        EXPECT_EQ(fifo.getFreeSpace(), 4);

        for (int i = 0; i < 7; ++i) {
            EXPECT_EQ(fifo.get(), c_r++);
        }

        EXPECT_FALSE(fifo.isFull());
        EXPECT_EQ(fifo.getLength(), 0);
        EXPECT_TRUE(fifo.isEmpty());
        EXPECT_FALSE(fifo.isNotEmpty());
        EXPECT_EQ(fifo.getSize(), 11);
        EXPECT_EQ(fifo.getFreeSpace(), 11);
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

        EXPECT_FALSE(fifo.isFull());
        EXPECT_EQ(fifo.getLength(), 7);
        EXPECT_FALSE(fifo.isEmpty());
        EXPECT_TRUE(fifo.isNotEmpty());
        EXPECT_EQ(fifo.getSize(), 11);
        EXPECT_EQ(fifo.getFreeSpace(), 4);

        fifo.read(data_r, 7);
        for (int i = 0; i < 7; ++i) {
            EXPECT_EQ(data_r[i], c_r++);
        }

        EXPECT_FALSE(fifo.isFull());
        EXPECT_EQ(fifo.getLength(), 0);
        EXPECT_TRUE(fifo.isEmpty());
        EXPECT_FALSE(fifo.isNotEmpty());
        EXPECT_EQ(fifo.getSize(), 11);
        EXPECT_EQ(fifo.getFreeSpace(), 11);
    }
}

DEFINE_TESTSUITE(fifo);
