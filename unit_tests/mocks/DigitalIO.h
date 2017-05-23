#ifndef UNIT_TESTS_MOCKS_DIGITALIO_H_
#define UNIT_TESTS_MOCKS_DIGITALIO_H_

#include "tests.h"
#include <hal/hal>

struct DigtalIOMock : public hal::DigitalIO::Interface {
    void init(const Mode) override {
        TEST_FAIL();
    }

    void toggle() override {
        TEST_FAIL();
    }

    void write(bool) override {
        TEST_FAIL();
    }

    bool read() override {
        TEST_FAIL();
        return false;
    }
};

#endif  // UNIT_TESTS_MOCKS_DIGITALIO_H_
