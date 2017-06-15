#ifndef UNIT_TESTS_MOCKS_DIGITALIO_H_
#define UNIT_TESTS_MOCKS_DIGITALIO_H_

#include <hal/hal>
#include "tests.h"

template<typename T>
struct DigtalIOMock {
    static void set() {
        T::write(1);
    }

    static void reset() {
        T::write(0);
    }
};

#endif  // UNIT_TESTS_MOCKS_DIGITALIO_H_
