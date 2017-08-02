#ifndef HAL_LIBS_COMPILE_TIME_H_
#define HAL_LIBS_COMPILE_TIME_H_

#include <cstdint>
#include <tuple>
#include <type_traits>

namespace hal {
namespace libs {

template<std::int32_t base, int exp>
struct power {
    static_assert(base != 0, "Base cannot be equal to 0!");
    static const int32_t value = base * power<base, exp - 1>::value;
};

template<std::int32_t base>
struct power<base, 0> {
    static const int32_t value = 1;
};

constexpr uint64_t power_of_two(uint8_t exp) {
    return (exp == 0) ? 1 : 2 * power_of_two(exp - 1);
}

// clang-format off
template<uint8_t i>
using type_with_bits = typename std::conditional<(i <= 1), bool,
                       typename std::conditional<(i <= 8), uint8_t,
                       typename std::conditional<(i <= 16), uint16_t,
                       typename std::conditional<(i <= 32), uint32_t,
                       uint64_t>::type>::type>::type>::type;
// clang-format on

template<uint8_t exp>
constexpr type_with_bits<exp + 1> power_of_two() {
    return 2ULL * static_cast<type_with_bits<exp + 1>>(power_of_two<exp - 1>());
}

template<>
constexpr bool power_of_two<0>() {
    return 1;
}

/*!
 * Return proper unsigned type which can hold values up to max_value
 * @tparam max_value Maximal value requested.
 */
// clang-format off
template<uint64_t max_value>
using type_for_value = std::conditional_t<(max_value <= 0xFF), uint8_t,
                       std::conditional_t<(max_value <= 0xFFFF), uint16_t,
                       std::conditional_t<(max_value <= 0xFFFFFFFF), uint32_t,
                               uint64_t>>>;
// clang-format on

/*!
 * Test if T is specialization of Template. Result will be std::true_type or
 * std::false_type.
 * @tparam T Type under investigation
 * @tparam Template Template type. True if Template<...> can be equal to T.
 */
template<typename T, template<typename...> class Template>
struct is_specialization_of : std::false_type {};

template<template<typename...> class Template, typename... Args>
struct is_specialization_of<Template<Args...>, Template> : std::true_type {};


namespace details {
template<template<typename> typename Exec, typename Tuple>
struct ForEach {
    static void for_each_type(std::integer_sequence<std::size_t>) {
    }

    template<std::size_t Head, std::size_t... Tail>
    static void for_each_type(std::integer_sequence<std::size_t, Head, Tail...>) {
        Exec<typename std::tuple_element<Head, Tuple>::type>::run();

        for_each_type(std::integer_sequence<std::size_t, Tail...>());
    }
};
}  // namespace details

/*!
 * This function will invoke Exec<T>::run() for every type T in Tuple.
 * @tparam Exec Execution policy, template structure with run() method.
 * @tparam Tuple Tuple to iterate over.
 */
template<template<typename> typename Exec,
         typename Tuple,
         std::enable_if_t<hal::libs::is_specialization_of<Tuple, std::tuple>::value, int> = 0>
void for_each_type() {
    details::ForEach<Exec, Tuple>::for_each_type(
        std::make_integer_sequence<std::size_t, std::tuple_size<Tuple>::value>());
}
template<template<typename> typename Exec>
void for_each_type() {
}

/*!
 * This function will invoke Exec<T>::run() for every type T in Variadic
 * Template list.
 * @tparam Exec Execution policy, template structure with run() method.
 * @tparam Head First element
 * @tparam Tail Tail elements
 */
template<template<typename> typename Exec,
         typename Head,
         typename... Tail,
         std::enable_if_t<!hal::libs::is_specialization_of<Head, std::tuple>::value, int> = 0>
void for_each_type() {
    for_each_type<Exec, std::tuple<Head, Tail...>>();
}


}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_COMPILE_TIME_H_
