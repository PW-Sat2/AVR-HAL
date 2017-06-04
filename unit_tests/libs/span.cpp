#include "tests.h"

using namespace hal::libs;

TEST_GROUP(span);

TEST(span, check_values) {
    constexpr int size = 10;
    int tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    span<int> arv(tab);
    const span<int> carv(tab);

    TEST_ASSERT_NOT_EQUAL(arv.data(), nullptr);
    TEST_ASSERT_EQUAL(arv.size(), 10);
    TEST_ASSERT_EQUAL(arv.size_bytes(), 20);

    for (int i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL(arv[i], i);
        TEST_ASSERT_EQUAL(carv[i], i);
        TEST_ASSERT_EQUAL(arv.at(i), i);
        TEST_ASSERT_EQUAL(carv.at(i), i);
    }

    TEST_ASSERT_NOT_EQUAL(arv.data(), nullptr);
    TEST_ASSERT_EQUAL(arv.size(), 10);
    TEST_ASSERT_EQUAL(arv.size_bytes(), 20);

    int i = 0;
    for (auto& x : arv) {
        TEST_ASSERT_EQUAL(x, i++);
    }
    i = 0;
    for (const auto& x : carv) {
        TEST_ASSERT_EQUAL(x, i++);
    }

    TEST_ASSERT_NOT_EQUAL(arv.data(), nullptr);
    TEST_ASSERT_EQUAL(arv.size(), 10);
    TEST_ASSERT_EQUAL(arv.size_bytes(), 20);
}

TEST(span, equalEmpty) {
    constexpr int size = 10;
    int tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    span<int> arv(tab);
    span<int> arv2;
    TEST_ASSERT_EQUAL(arv.empty(), false);
    TEST_ASSERT_EQUAL(arv2.empty(), true);
    TEST_ASSERT_EQUAL(arv == arv2, false);
    TEST_ASSERT_EQUAL(arv != arv2, true);
    TEST_ASSERT_EQUAL(arv == nullptr, false);
    TEST_ASSERT_EQUAL(arv2 == nullptr, true);
    arv2 = arv;
    TEST_ASSERT_EQUAL(arv == arv2, true);
    TEST_ASSERT_EQUAL(arv != arv2, false);
    TEST_ASSERT_EQUAL(arv == nullptr, false);
    TEST_ASSERT_EQUAL(arv2 == nullptr, false);
    TEST_ASSERT_EQUAL(arv.empty(), false);
    TEST_ASSERT_EQUAL(arv2.empty(), false);

    for (int i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL(arv[i], i);
        TEST_ASSERT_EQUAL(arv2[i], i);
        TEST_ASSERT_EQUAL(arv.at(i), i);
        TEST_ASSERT_EQUAL(arv2.at(i), i);
    }
}

TEST(span, reset) {
    constexpr int size = 100;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    span<int32_t> arv(tab);

    for (int i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL(arv[i], i);
    }
    TEST_ASSERT_NOT_EQUAL(arv.data(), nullptr);
    TEST_ASSERT_EQUAL(arv.size(), 100);
    TEST_ASSERT_EQUAL(arv.size_bytes(), 400);

    arv.reset();
    TEST_ASSERT_EQUAL(arv.data(), nullptr);
    TEST_ASSERT_EQUAL(arv.size(), 0);
    TEST_ASSERT_EQUAL(arv.size_bytes(), 0);
}

TEST(span, pointers) {
    constexpr int size = 10;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    span<int32_t> arv(tab);
    const span<int32_t> carv(arv);

    int32_t* ptr = arv.data();
    TEST_ASSERT_EQUAL(ptr, arv.data());
    const int32_t* cptr = carv.data();
    TEST_ASSERT_EQUAL(cptr, carv.data());
}

TEST(span, references) {
    constexpr int size = 10;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    span<int32_t> arv(tab);
    const span<int32_t> carv(tab);

    TEST_ASSERT_EQUAL(&arv[0], arv.begin());
    TEST_ASSERT_EQUAL(&arv[0] + 10, arv.end());
    TEST_ASSERT_EQUAL(&carv[0], carv.begin());
    TEST_ASSERT_EQUAL(&carv[0] + 10, carv.end());

    TEST_ASSERT_EQUAL(arv[0], arv.front());
    TEST_ASSERT_EQUAL(arv[9], arv.back());
    TEST_ASSERT_EQUAL(carv[0], arv.front());
    TEST_ASSERT_EQUAL(carv[9], arv.back());
}

TEST(span, slice) {
    constexpr int size = 100;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    int32_t* const tab_ptr = tab;
    span<int32_t> arv(tab_ptr, 100);

    span<int32_t> arv2(arv.subspan(0, 50));

    TEST_ASSERT_EQUAL(arv2.size(), 50);
    for (size_t i = 0; i < arv2.size(); ++i) {
        TEST_ASSERT_EQUAL(arv2[i], i);
    }

    arv2 = arv.subspan(20, 10);

    TEST_ASSERT_EQUAL(arv2.size(), 10);
    for (size_t i = 0; i < arv2.size(); ++i) {
        TEST_ASSERT_EQUAL(arv2[i], i + 20);
    }
}

TEST(span, equal) {
    uint8_t table[100];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            table[10 * i + j] = j;
        }
    }

    TEST_ASSERT_TRUE(make_span(table, 10) == make_span(table + 10, 10));
    TEST_ASSERT_TRUE(make_span(table, 20) == make_span(table + 30, 20));
    TEST_ASSERT_FALSE(make_span(table, 20) == make_span(table + 30, 21));
    TEST_ASSERT_FALSE(make_span(table + 1, 20) == make_span(table + 30, 20));
    TEST_ASSERT_TRUE(make_span(table, 50) == make_span(table + 30, 50));
}
