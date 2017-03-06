#include <gtest/gtest.h>
#include "array.h"

TEST(array, refs) {
    int XXX = 73923874, YYY = 2938481092;
    hal::libs::array<int, 10> arr;
    arr[0] = XXX;
    arr[9] = YYY;
    const hal::libs::array<int, 10> arr2(arr);
    EXPECT_EQ(arr == arr2, true);
    EXPECT_EQ(arr.begin(), arr.data());
    EXPECT_EQ(arr2.begin(), arr2.data());

    EXPECT_EQ(arr.end(), arr.data() + 10);
    EXPECT_EQ(arr2.end(), arr2.data() + 10);

    EXPECT_EQ(XXX, arr.front());
    EXPECT_EQ(XXX, arr2.front());
    EXPECT_EQ(YYY, arr.back());
    EXPECT_EQ(YYY, arr2.back());

    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr2.size(), 10);
    EXPECT_EQ(arr.empty(), false);
}

TEST(array, at) {
    hal::libs::array<int, 20> arr;
    int * val = arr.data();
    for (int i = 0; i < 20; ++i) {
        *(val++) = i;
    }
    const hal::libs::array<int, 20> arr2(arr);

    EXPECT_EQ(arr == arr2, true);

    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
        EXPECT_EQ(arr2[i], i);

        EXPECT_EQ(arr.at(i), i);
        EXPECT_EQ(arr2.at(i), i);
    }

    int i = 0;
    for (const auto &x : arr) {
        EXPECT_EQ(x, i++);
    }
    i = 0;
    for (const auto &x : arr2) {
        EXPECT_EQ(x, i++);
    }
}

TEST(array, swap) {
    hal::libs::array<int, 20> arr;
    hal::libs::array<int, 20> arr2;
    arr = arr2;
    EXPECT_EQ(arr == arr2, true);

    for (int i = 0; i < 20; ++i) {
        arr[i] = i;
        arr2[i] = 20 - i;
    }

    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
        EXPECT_EQ(arr2[i], 20 - i);
    }

    EXPECT_EQ(arr == arr2, false);
    swap(arr, arr2);
    EXPECT_EQ(arr == arr2, false);

    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], 20 - i);
        EXPECT_EQ(arr2[i], i);
    }
}

TEST(array, assign) {
    hal::libs::array<unsigned char, 20> arr;
    arr.assign(3);

    for (const auto &x : arr) {
        EXPECT_EQ(x, 3);
    }
}
