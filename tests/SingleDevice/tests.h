#ifndef UNIT_TESTS_TESTS_H_
#define UNIT_TESTS_TESTS_H_

#include "unity.h"
#include <hal/hal>

typedef void (*fptr)();

struct Case {
    Case() : function{nullptr}, line{0} {}
    Case(fptr function_, int line) : function{function_}, line{line} {}
    fptr function;
    int line;
};

static hal::libs::FIFO_data<Case, 10> data;

fptr add_test_group(void (*fun)(), bool get = false);


#undef TEST
#define TEST(group, name) \
    void TEST_##group##_##name();\
    struct TEST_##group##_##name##_str { \
        TEST_##group##_##name##_str() {  \
            data.append(Case(TEST_##group##_##name, __LINE__));   \
        }\
    } TEST_##group##_##name##_str_inst;  \
    void TEST_##group##_##name()



#define RUN(group, name) RUN_TEST(TEST_##group##_##name##)

#define TEST_GROUP(group)\
    void TEST_##group##_GROUP_RUNNER(void);\
    struct TEST_##group##_str { \
        TEST_##group##_str() {  \
            add_test_group(TEST_##group##_GROUP_RUNNER);\
        }                            \
    } TEST_##group##_##name##_str_inst;  \
    void TEST_##group##_GROUP_RUNNER(void) {\
        UNITY_BEGIN();\
        while (data.getLength() > 0) {\
            auto case_now = data.get();\
            UnityDefaultTestRun(case_now.function, "", case_now.line);\
        }\
        UNITY_END();\
    }

#endif  // UNIT_TESTS_TESTS_H_
