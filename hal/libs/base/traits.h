#ifndef LIBS_BASE_INCLUDE_TRAITS_HPP_
#define LIBS_BASE_INCLUDE_TRAITS_HPP_

#pragma once

#include <cstdint>
#include <type_traits>

namespace hal {

/**
 * @addtogroup utilities
 * @{
 */

/**
 * @brief Type trait for converting bool to integer at compile time.
 */
template<bool>
struct AsInt final {
    /**
     * @brief Assigned value.
     */
    static constexpr std::uint32_t value = 0;
};

/**
 * @brief Type trait for converting bool to integer at compile time.
 *
 * Specialization for true value.
 */
template<>
struct AsInt<true> final {
    /**
     * @brief Assigned value.
     */
    static constexpr std::uint32_t value = 1;
};

/**
 * @brief Checks if type is in list
 * @tparam T Type to check
 * @tparam List Template pack for checking
 */
template<typename T, typename... List>
class IsInList {
 private:
    /**
     * @brief Check logic - single step
     * @return Value indicating whether type is in list
     */
    template<std::uint8_t Tag, typename Head, typename... Rest>
    static constexpr bool Check() {
        if (std::is_same<T, Head>::value) {
            return true;
        }

        return Check<0, Rest...>();
    }

    /**
     * @brief Check logic - stop condition
     * @return Always false
     */
    template<std::uint8_t Tag>
    static constexpr bool Check() {
        return false;
    }

 public:
    /** @brief Value indicating whether type is in list */
    static constexpr bool value = Check<0, List...>();
};

/**
 * @brief Checks if types in template pack are unique
 * @tparam Ts Template pack to check
 */
template<typename... Ts>
class AreTypesUnique {
 private:
    /**
     * @brief Check logic - single step
     * @return Value indicating whether types in template pack are unique
     */
    template<std::uint8_t Tag, typename Head, typename... Rest>
    static constexpr bool IsUnique() {
        if (IsInList<Head, Rest...>::value) {
            return false;
        }

        return IsUnique<0, Rest...>();
    }

    /**
     * @brief Check logic - stop condition
     * @return Always true
     */
    template<std::uint8_t Tag>
    static constexpr bool IsUnique() {
        return true;
    }

 public:
    /** @brief Value indicating whether types in template pack are unique */
    static constexpr bool value = IsUnique<0, Ts...>();
};

/**
 * @brief Checks if value is in list
 */
template<typename ValueType>
struct IsValueInList {
    /**
     * @brief Checks if values is in list
     * @return true if value is in list
     */
    template<ValueType Value, ValueType Head, ValueType... Rest>
    static constexpr bool IsInList() {
        return Value == Head || IsInList<Value, Rest...>();
    }

    /**
     * @brief Checks if values is in list (stop condition)
     * @return Always false
     */
    template<ValueType Value>
    static constexpr bool IsInList() {
        return false;
    }
};

/** @} */
}

#endif /* LIBS_BASE_INCLUDE_TRAITS_HPP_ */
