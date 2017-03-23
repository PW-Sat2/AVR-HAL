#ifndef HAL_LIBS_COMPILE_TIME_H_
#define HAL_LIBS_COMPILE_TIME_H_

#include <cstdint>
#include <type_traits>

namespace hal {
namespace libs {

template <std::int32_t base, int exp>
struct power {
    static_assert(base != 0, "Base cannot be equal to 0!");
    static const int32_t value = base * power<base, exp - 1>::value;
};

template <std::int32_t base>
struct power<base, 0> {
    static const int32_t value = 1;
};

constexpr uint64_t power_of_two(uint8_t exp) {
    return (exp == 0) ? 1 : 2*power_of_two(exp-1);
}

template<uint8_t i>
using type_with_bits = typename std::conditional<(i <= 1), bool,
                       typename std::conditional<(i <= 8), uint8_t,
                       typename std::conditional<(i <= 16), uint16_t,
                       typename std::conditional<(i <= 32), uint32_t,
                       uint64_t>::type>::type>::type>::type;

template<uint8_t exp>
constexpr type_with_bits<exp+1> power_of_two() {
    return 2ULL* static_cast<type_with_bits<exp+1>>(power_of_two<exp-1>());
}

template<>
constexpr bool power_of_two<0>() {
    return 1;
}

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_COMPILE_TIME_H_
