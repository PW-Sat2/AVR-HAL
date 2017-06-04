#include "tests.h"

TEST_GROUP(array);

TEST(array, refs) {
    uint32_t XXX = 73923874, YYY = 2938481092;
    std::array<uint32_t, 10> arr;
    arr[0] = XXX;
    arr[9] = YYY;
    const std::array<uint32_t, 10> arr2(arr);
    TEST_ASSERT_EQUAL(arr == arr2, true);
    TEST_ASSERT_EQUAL(arr.begin(), arr.data());
    TEST_ASSERT_EQUAL(arr2.begin(), arr2.data());

    TEST_ASSERT_EQUAL(arr.end(), arr.data() + 10);
    TEST_ASSERT_EQUAL(arr2.end(), arr2.data() + 10);

    TEST_ASSERT_EQUAL(XXX, arr.front());
    TEST_ASSERT_EQUAL(XXX, arr2.front());
    TEST_ASSERT_EQUAL(YYY, arr.back());
    TEST_ASSERT_EQUAL(YYY, arr2.back());

    TEST_ASSERT_EQUAL(arr.size(), 10);
    TEST_ASSERT_EQUAL(arr2.size(), 10);
    TEST_ASSERT_EQUAL(arr.empty(), false);
}

TEST(array, at) {
    std::array<int, 20> arr;
    int* val = arr.data();
    for (int i = 0; i < 20; ++i) {
        *(val++) = i;
    }
    const std::array<int, 20> arr2(arr);

    TEST_ASSERT_EQUAL(arr == arr2, true);

    for (int i = 0; i < 20; ++i) {
        TEST_ASSERT_EQUAL(arr[i], i);
        TEST_ASSERT_EQUAL(arr2[i], i);

        TEST_ASSERT_EQUAL(arr.at(i), i);
        TEST_ASSERT_EQUAL(arr2.at(i), i);
    }

    int i = 0;
    for (const auto& x : arr) {
        TEST_ASSERT_EQUAL(x, i++);
    }
    i = 0;
    for (const auto& x : arr2) {
        TEST_ASSERT_EQUAL(x, i++);
    }
}

TEST(array, swap) {
    std::array<int, 5> arr  = {1, 1, 1, 1, 1};
    std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
    arr                     = arr2;
    TEST_ASSERT_EQUAL(arr == arr2, true);

    for (int i = 0; i < 5; ++i) {
        arr[i]  = i;
        arr2[i] = 5 - i;
    }

    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL(arr[i], i);
        TEST_ASSERT_EQUAL(arr2[i], 5 - i);
    }

    TEST_ASSERT_EQUAL(arr == arr2, false);
    std::swap(arr, arr2);
    TEST_ASSERT_EQUAL(arr == arr2, false);

    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL(arr[i], 5 - i);
        TEST_ASSERT_EQUAL(arr2[i], i);
    }

    std::swap(arr, arr2);
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL(arr[i], i);
        TEST_ASSERT_EQUAL(arr2[i], 5 - i);
    }
}
