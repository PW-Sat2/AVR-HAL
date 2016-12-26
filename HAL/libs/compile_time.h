#ifndef HAL_LIBS_COMPILE_TIME_H_
#define HAL_LIBS_COMPILE_TIME_H_

namespace hal {
namespace libs {

template <int32_t base, int exp>
struct power {
    static_assert(base != 0, "Base cannot be equal to 0!");
    static const int32_t value = base * power<base, exp - 1>::value;
};

template <int32_t base>
struct power<base, 0> {
    static const int32_t value = 1;
};

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_COMPILE_TIME_H_
