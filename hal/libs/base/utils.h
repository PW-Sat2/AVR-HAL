#ifndef HAL_LIBS_BASE_UTILS_H_
#define HAL_LIBS_BASE_UTILS_H_

#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

namespace hal {
namespace libs {

/**
 * @brief Converts boolean value to 1 or 0
 * @param[in] value Value to convert
 * @return 1 for true, 0 for false
 */
static constexpr inline int ToInt(bool value) {
    return value ? 1 : 0;
}

/**
 * @brief Just marker indicating that value is in bytes
 * @param[in] value Value
 * @return The same value
 */
constexpr std::size_t operator"" _Bytes(unsigned long long int value) {
    return value;
}

/**
 * @brief Converts value in kilobytes to bytes
 * @param[in] value Values in kilobytes
 * @return Value in bytes
 */
constexpr std::size_t operator"" _KB(unsigned long long int value) {
    return value * 1024_Bytes;
}

/**
 * @brief Converts value in megabytes to bytes
 * @param[in] value Values in megabytes
 * @return Value in bytes
 */
constexpr std::size_t operator"" _MB(unsigned long long int value) {
    return value * 1024_KB;
}

/**
 * @brief Just marker indicating that value is in Hz
 * @param[in] value Value in Hz
 * @return the same value
 */
constexpr std::uint32_t operator"" _Hz(unsigned long long int value) {
    return value;
}

/**
 * @brief Converts KHz to Hz
 * @param[in] value Value in KHz
 * @return Value in Hz
 */
constexpr std::uint32_t operator"" _KHz(unsigned long long int value) {
    return value * 1000_Hz;
}

/**
 * @brief Converts MHz to Hz
 * @param[in] value Value in MHz
 * @return Value in Hz
 */
constexpr std::uint32_t operator"" _MHz(unsigned long long int value) {
    return value * 1000_KHz;
}

/**
 * @brief Inheriting from this class, will make derived class unconstructable
 */
struct PureStatic {
    PureStatic() = delete;
};

/**
 * @brief Private-inherit this class to prevent copy-operations
 */
struct NotCopyable {
    NotCopyable()                       = default;
    NotCopyable(const NotCopyable& arg) = delete;
    NotCopyable& operator=(const NotCopyable& arg) = delete;
};

/**
 * @brief Private-inherit this class to prevent move-operations
 */
struct NotMoveable {
    NotMoveable()                  = default;
    NotMoveable(NotMoveable&& arg) = delete;
    NotMoveable& operator=(NotMoveable&& arg) = delete;
};

/**
 * @brief Class that can logically contain either a value of type T or no value.
 */
template<class T>
class Option {
 public:
    /**
     * @brief Default ctor
     */
    Option();

    /**
     * @brief Factory method that constructs empty Option instance.
     * @return Empty Option instance.
     */
    static Option<T> None() {
        return Option<T>(false, T());
    }

    /**
     * @brief Factory method that constucts Option instance and its value in
     * place
     * @param args Arguments passed to constructor of T
     * @return Option instance
     */
    template<typename... Args>
    static Option<T> Some(Args&&... args) {
        return Option<T>(true, std::forward<Args>(args)...);
    }

    /**
     * @brief A flag indicating if this Option instance holds a value.
     */
    bool HasValue;

    /**
     * @brief Value held by Option instance if HasValue is true.
     */
    T Value;

 private:
    template<typename... Args>
    Option(bool hasValue, Args&&... values);
};

template<typename T>
inline Option<T>::Option() : HasValue(false), Value(T()) {
}

template<typename T>
template<typename... Args>
Option<T>::Option(bool hasValue, Args&&... values)  //
    : HasValue(hasValue),                           //
      Value(std::forward<Args>(values)...) {
}

/**
 * @brief Factory method that constructs empty Option instance.
 * @return Empty Option instance.
 */
template<typename T>
static inline Option<T> None() {
    return Option<T>::None();
}

/**
 * @brief Factory method that constructs Option instance that holds given value.
 * @param[in] value Value to hold in Option instance.
 * @return Option instance that holds a value.
 */
template<typename T>
static inline Option<typename std::remove_reference<T>::type> Some(T&& value) {
    using U = typename std::remove_reference<T>::type;

    return Option<U>::Some(std::forward<U>(value));
}

/**
 * @brief Equality operator for @ref Option<T>
 * @param lhs Left side value
 * @param rhs Right side value (raw, not option)
 * @retval false lhs is None
 * @retval false lhs is Some and rhs is not equal to holded value
 * @retval true lhs is Some and rhs is equal to holded value
 */
template<typename T>
static inline bool operator==(const Option<T>& lhs, const T& rhs) {
    if (!lhs.HasValue) {
        return false;
    }

    return lhs.Value == rhs;
}

/**
 * @brief Equality operator for @ref Option<T>
 * @param lhs Right side value (raw, not option)
 * @param rhs Left side value
 * @retval false rhs is None
 * @retval false rhs is Some and lhs is not equal to holded value
 * @retval true rhs is Some and lhs is equal to holded value
 */
template<typename T>
bool operator==(const T& lhs, const Option<T>& rhs) {
    return rhs == lhs;
}

/**
 * @brief Inequality operator for @ref Option<T>
 * @param lhs Left side value
 * @param rhs Right side value (raw, not option)
 * @retval true lhs is None
 * @retval true lhs is Some and rhs is not equal to holded value
 * @retval false lhs is Some and rhs is equal to holded value
 */
template<typename T>
inline bool operator!=(const Option<T>& lhs, const T& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Equality operator for @ref Option<T>
 * @brief Inequality operator for @ref Option<T>
 * @param lhs Left side value
 * @param rhs Right side value (option)
 * @retval true when both are None
 * @retval false when one is None and other is Some
 * @retval false when both are Some and underlying values are not equal
 * @retval true when both are Some and underlying values are equal
 */
template<typename T>
bool operator==(const Option<T>& lhs, const Option<T>& rhs) {
    if (lhs.HasValue && rhs.HasValue) {
        return lhs.Value == rhs.Value;
    }

    return lhs.HasValue == rhs.HasValue;
}

/**
 * @brief Equality operator for @ref Option<T>
 * @param lhs Left side value
 * @param rhs Right side value (option)
 * @retval true when both are None
 * @retval false when one is None and other is Some
 * @retval false when both are Some and underlying values are not equal
 * @retval true when both are Some and underlying values are equal
 */
template<typename T>
inline bool operator!=(const Option<T>& lhs, const Option<T>& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Type wrapping integer of non-standard size
 * @tparam Integer type that will be used to hold smaller value
 * @tparam BitsCount Number of bits used by number
 * @ingroup utilities
 */
template<typename Underlying, std::uint8_t BitsCount>
class BitValue {
 public:
    /** @brief Mask used to trim value */
    static constexpr Underlying Mask = ~(~0ull << BitsCount);

    /**
     * @brief Public constant that contains size of the value in bits.
     */
    static constexpr int Size = BitsCount;

    /**
     * @brief Default .ctor
     */
    constexpr BitValue();
    /**
     * @brief Initializes with given value
     * @param v Initial value
     */
    constexpr BitValue(Underlying v);

    /**
     * @brief Extracts held value
     */
    constexpr operator Underlying() const;

    /**
     * @brief Extracts held value
     * @return Held value
     */
    Underlying Value() const;

 private:
    /** @brief Held value */
    Underlying _value;
};

template<typename Underlying, std::uint8_t BitsCount>
constexpr BitValue<Underlying, BitsCount>::operator Underlying() const {
    return this->_value;
}

template<typename Underlying, std::uint8_t BitsCount>
constexpr BitValue<Underlying, BitsCount>::BitValue(Underlying v)
    : _value(v & Mask) {
}

template<typename Underlying, std::uint8_t BitsCount>
constexpr BitValue<Underlying, BitsCount>::BitValue() : _value(0) {
}

template<typename Underlying, std::uint8_t BitsCount>
inline Underlying BitValue<Underlying, BitsCount>::Value() const {
    return this->_value;
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator<(BitValue<Underlying, BitsCount>& lhs,
                      BitValue<Underlying, BitsCount>& rhs) {
    return lhs.Value() < rhs.Value();
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator>(BitValue<Underlying, BitsCount>& lhs,
                      BitValue<Underlying, BitsCount>& rhs) {
    return rhs < lhs;
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator<=(BitValue<Underlying, BitsCount>& lhs,
                       BitValue<Underlying, BitsCount>& rhs) {
    return !(lhs > rhs);
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator>=(BitValue<Underlying, BitsCount>& lhs,
                       BitValue<Underlying, BitsCount>& rhs) {
    return !(lhs < rhs);
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator==(BitValue<Underlying, BitsCount>& lhs,
                       BitValue<Underlying, BitsCount>& rhs) {
    return lhs.Value() == rhs.Value();
}

template<typename Underlying, std::uint8_t BitsCount>
inline bool operator!=(BitValue<Underlying, BitsCount>& lhs,
                       BitValue<Underlying, BitsCount>& rhs) {
    return !(lhs == rhs);
}

namespace details {
/**
 * @brief Type that extracts size in bits of the selected type.
 * @tparam T Queried type.
 * @tparam flag Flag indicating whether the selected type is an enumeration
 */
template<typename T, bool flag>
struct BitSizeOf;

/**
 * @brief Type that extracts size in bits of the selected type.
 * @tparam T Queried type.
 * @remark Specialization for enumerations
 */
template<typename T>
struct BitSizeOf<T, true> {
    /**
     * @brief This value contanins queried type size in bits.
     */
    static constexpr std::uint32_t Value =
        std::numeric_limits<typename std::underlying_type<T>::type>::digits;
};

/**
 * @brief Type that extracts size in bits of the selected type.
 * @tparam T Queried type.
 * @remark Specialization for non-enumerations
 */
template<typename T>
struct BitSizeOf<T, false> {
    /**
     * @brief This value contains queried type size in bits.
     */
    static constexpr std::uint32_t Value = std::numeric_limits<T>::digits;
};

/**
 * @brief Type that extracts size in bits of the selected type.
 * @tparam T Queried type.
 * @remark Specialization for BitValues
 */
template<typename T, std::uint8_t BitCount>
struct BitSizeOf<BitValue<T, BitCount>, false> {
    /**
     * @brief This value contains queried type size in bits.
     */
    static constexpr std::uint32_t Value = BitValue<T, BitCount>::Size;
};
}  // namespace details

/**
 * @brief Template variable that holds size of the selected type in bits.
 * @tparam T Queried type.
 */
template<typename T>
struct BitLength {
    constexpr static std::uint32_t value =
        details::BitSizeOf<T, std::is_enum<T>::value>::Value;
};

namespace details {
/**
 * @brief Template variable that aggregates sizes of all passed types in bits.
 *
 * @remark Specialization for two or more types.
 * @tparam T type whose length in bits should be recorded.
 * @tparam Args list of types whose length in bits should be recorded.
 */
template<typename T, typename... Args>
struct AggregateSize {
    /**
     * @brief This value contains aggregates size in bits of all queried types.
     */
    static constexpr std::uint32_t value =
        BitLength<T>::value + AggregateSize<Args...>::value;
};

/**
 * @brief Template variable that aggregates sizes of all passed types in bits.
 *
 * @remark Specialization for single type.
 * @tparam T type whose length in bits should be recorded.
 */
template<typename T>
struct AggregateSize<T> {
    /**
     * @brief This value contains queried type size in bits.
     */
    static constexpr std::uint32_t value = BitLength<T>::value;
};
}  // namespace details

/**
 * @brief Template variable that aggregates sizes of all passed types in bits.
 * @tparam Args List of types whose sizes in bits should be aggregated.
 */
template<typename... Args>
struct Aggregate {
    constexpr static const std::uint32_t value =
        details::AggregateSize<Args...>::value;
};

}  // namespace libs
}  // namespace hal

/** @brief 24-bit unsigned integer */
using uint24_t = hal::libs::BitValue<std::uint32_t, 24>;

/** @brief 14-bit unsigned integer */
using uint14_t = hal::libs::BitValue<std::uint16_t, 14>;

/** @brief 12-bit unsigned integer */
using uint12_t = hal::libs::BitValue<std::uint16_t, 12>;

/** @brief 13-bit unsigned integer */
using uint13_t = hal::libs::BitValue<std::uint16_t, 13>;

/** @brief 10-bit unsigned integer */
using uint10_t = hal::libs::BitValue<std::uint16_t, 10>;

/** @brief 7-bit unsigned integer */
using uint7_t = hal::libs::BitValue<std::uint8_t, 7>;

#endif  // HAL_LIBS_BASE_UTILS_H_
