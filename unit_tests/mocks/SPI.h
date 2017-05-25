#ifndef UNIT_TESTS_MOCKS_SPI_H_
#define UNIT_TESTS_MOCKS_SPI_H_

#include "tests.h"
#include <hal/hal>

struct EmptySPIMock : public hal::SPI::Interface {
    uint8_t transfer(uint8_t output) override {
        TEST_FAIL();
        return 0;
    }

    void transfer(hal::libs::span<const uint8_t> output, hal::libs::span<uint8_t> input) override {
        TEST_FAIL();
    }

    void write(hal::libs::span<const uint8_t> output) override {
        TEST_FAIL();
    }

    void read(hal::libs::span<uint8_t> input, uint8_t output_value) override {
        TEST_FAIL();
    }
};

#endif  // UNIT_TESTS_MOCKS_SPI_H_
