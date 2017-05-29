#ifndef UNIT_TESTS_MOCKS_SPI_H_
#define UNIT_TESTS_MOCKS_SPI_H_

#include "tests.h"
#include <hal/hal>

struct EmptySPIMock : public hal::SPI::Interface {
    uint8_t transfer(uint8_t) override {
        TEST_FAIL();
        return 0;
    }

    void transfer(hal::libs::span<const uint8_t> in, hal::libs::span<uint8_t> out) override {
        TEST_ASSERT_EQUAL_INT(in.size(), out.size());
        TEST_FAIL();
    }

    void write(hal::libs::span<const uint8_t>) override {
        TEST_FAIL();
    }

    void read(hal::libs::span<uint8_t>, uint8_t) override {
        TEST_FAIL();
    }
};

#endif  // UNIT_TESTS_MOCKS_SPI_H_
