#ifndef HAL_LIBS_HAL_ASSERT_H_
#define HAL_LIBS_HAL_ASSERT_H_

#include <stdio.h>

namespace hal {
namespace libs {

#undef assert
#define assert(cond) \
    if (!(cond)) {     \
        fail_due_to_error("Assert failed"); \
    }

#undef fail_due_to_error
#define fail_due_to_error(string) \
    printf("Error at %s:%d - %s\r\n", __FILE__, __LINE__, string); \
    while (1) {}

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_HAL_ASSERT_H_
