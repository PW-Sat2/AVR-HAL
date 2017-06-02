#include "tests.h"

using namespace hal::libs;

TEST_GROUP(span);

TEST(span, check_values) {
    constexpr int size = 10;
    int tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    gsl::span<int> arv(tab);
    const gsl::span<int> carv(tab);

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
    gsl::span<int> arv(tab);
    gsl::span<int> arv2;
    TEST_ASSERT_EQUAL(arv.empty(), false);
    TEST_ASSERT_EQUAL(arv2.empty(), true);
    TEST_ASSERT_EQUAL(arv == arv2, false);
    TEST_ASSERT_EQUAL(arv != arv2, true);
    arv2 = arv;
    TEST_ASSERT_EQUAL(arv == arv2, true);
    TEST_ASSERT_EQUAL(arv != arv2, false);
    TEST_ASSERT_EQUAL(arv.empty(), false);
    TEST_ASSERT_EQUAL(arv2.empty(), false);

    for (int i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL(arv[i], i);
        TEST_ASSERT_EQUAL(arv2[i], i);
        TEST_ASSERT_EQUAL(arv.at(i), i);
        TEST_ASSERT_EQUAL(arv2.at(i), i);
    }
}

TEST(span, pointers) {
    constexpr int size = 10;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    gsl::span<int32_t> arv(tab);
    const gsl::span<int32_t> carv(arv);

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
    gsl::span<int32_t> arv(tab);
    const gsl::span<int32_t> carv(tab);

    TEST_ASSERT_EQUAL(&arv[0], arv.begin());
    TEST_ASSERT_EQUAL(&arv[0] + 10, arv.end());
    TEST_ASSERT_EQUAL(&carv[0], carv.begin());
    TEST_ASSERT_EQUAL(&carv[0] + 10, carv.end());
}

TEST(span, slice) {
    constexpr int size = 100;
    int32_t tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = i;
    }
    int32_t* const tab_ptr = tab;
    gsl::span<int32_t> arv(tab_ptr, 100);

    gsl::span<int32_t> arv2(arv.subspan(0, 50));

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

    TEST_ASSERT_TRUE(gsl::make_span(table, 10) == gsl::make_span(table + 10, 10));
    TEST_ASSERT_TRUE(gsl::make_span(table, 20) == gsl::make_span(table + 30, 20));
    TEST_ASSERT_FALSE(gsl::make_span(table, 20) == gsl::make_span(table + 30, 21));
    TEST_ASSERT_FALSE(gsl::make_span(table + 1, 20) ==
                      gsl::make_span(table + 30, 20));
    TEST_ASSERT_TRUE(gsl::make_span(table, 50) == gsl::make_span(table + 30, 50));
}
