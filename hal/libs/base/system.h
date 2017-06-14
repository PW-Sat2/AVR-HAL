#ifndef HAL_LIBS_BASE_SYSTEM_H_
#define HAL_LIBS_BASE_SYSTEM_H_

#include <cstddef>
#include <cstdint>
#include <type_traits>

/**
 * @brief Macro for stating that routine parameter is not used.
 */
#define UNREFERENCED_PARAMETER(x) ((void)x)

#define UNUSED1(a) ((void)a)
#define UNUSED2(a, b) ((void)a), UNUSED1(b)
#define UNUSED3(a, b, c) ((void)a), UNUSED2(b, c)
#define UNUSED4(a, b, c, d) ((void)a), UNUSED3(b, c, d)
#define UNUSED5(a, b, c, d, e) ((void)a), UNUSED4(b, c, d, e)

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)

#define UNUSED_IMPL_(nargs) UNUSED##nargs
#define UNUSED_IMPL(nargs) UNUSED_IMPL_(nargs)
#define UNUSED(...) UNUSED_IMPL(VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

/**
 * @brief Macro that calculates the number of elements in an array.
 */
#define COUNT_OF(x) count_of(x)

/**
 * @brief Helper function that returns number of elements from an array.
 */
template<typename T, std::size_t size>
constexpr inline std::size_t count_of(T (&)[size]) {
    return size;
}

#ifdef __cplusplus
#define EXTERNC_BEGIN extern "C" {
#define EXTERNC_END }
#else
#define EXTERNC_BEGIN
#define EXTERNC_END
#endif

template<typename Enum>
constexpr bool has_flag(Enum value, Enum flag) {
    auto valueU = static_cast<typename std::underlying_type<Enum>::type>(value);
    auto flagU  = static_cast<typename std::underlying_type<Enum>::type>(flag);

    return (valueU & flagU) == flagU;
}

constexpr bool has_flag(std::uint32_t value, std::uint32_t flag) {
    return (value & flag) == flag;
}

template<typename Enum>
constexpr inline typename std::underlying_type<Enum>::type num(Enum v) {
    return static_cast<typename std::underlying_type<Enum>::type>(v);
}


#endif  // HAL_LIBS_BASE_SYSTEM_H_
