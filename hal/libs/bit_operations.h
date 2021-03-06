#ifndef HAL_LIBS_BIT_OPERATIONS_H_
#define HAL_LIBS_BIT_OPERATIONS_H_

#include "compile_time.h"

namespace hal {
namespace libs {

template<typename reg_type>
constexpr inline void
set_bit(reg_type& val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void set_bit(reg_type& val, const int bit_pos) {
    val |= (1UL << bit_pos);
}

template<int bit_pos, typename reg_type>
constexpr inline void set_bit(reg_type& val) {
    val |= (1UL << bit_pos);
}

template<typename reg_type>
constexpr inline void
set_bit(reg_type* val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void set_bit(reg_type* val, const int bit_pos) {
    (*val) |= (1UL << bit_pos);
}

template<typename reg_type>
constexpr inline void
clear_bit(reg_type& val, const int bit_pos) __attribute__((always_inline));
template<typename reg_type>
constexpr inline void clear_bit(reg_type& val, const int bit_pos) {
    val &= (~(1UL << bit_pos));
}

template<int bit_pos, typename reg_type>
constexpr inline void clear_bit(reg_type& val) {
    val &= (~(1UL << bit_pos));
}

template<typename reg_type>
constexpr inline void
clear_bit(reg_type* val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void clear_bit(reg_type* val, const int bit_pos) {
    (*val) &= (~(1UL << bit_pos));
}

template<uint8_t start, uint8_t length>
constexpr type_with_bits<start + length> bit_mask() {
    static_assert(start + length <= 64, "too large bit_mask (exceeding uint64_t)!");
    return (power_of_two<length>() - 1ULL) << start;
}

constexpr uint64_t bit_mask(uint8_t start, uint8_t length) {
    return (power_of_two(length) - 1ULL) << start;
}

template<uint8_t start, uint8_t length, typename T>
constexpr type_with_bits<length> read_mask(T value) {
    static_assert(start + length <= 8 * sizeof(value),
                  "Read with mask exceeded register size");
    return (value & bit_mask<start, length>()) >> start;
}

constexpr uint64_t read_mask(uint8_t start, uint8_t length, uint64_t value) {
    return (value & bit_mask(start, length)) >> start;
}

template<uint8_t bit_pos, typename T>
constexpr bool read_bit(T value) {
    return read_mask<bit_pos, 1>(value);
}

template<typename T>
constexpr bool read_bit(T value, uint8_t bit_pos) {
    return (value >> bit_pos) & 0x1;
}

template<uint8_t start, uint8_t length, typename T, typename T2>
constexpr void write_mask(T& destination, T2 value) {
    static_assert(start + length <= 8 * sizeof(destination),
                  "Write with mask exceeded register size");
    destination &= (~static_cast<T>(bit_mask<start, length>()));
    destination |= (static_cast<T>(value) << start);
}

template<uint8_t start, typename T>
constexpr void write_bit(T& destination, bool value) {
    write_mask<start, 1>(destination, value);
}

template<typename T, typename T2>
constexpr void
write_mask(uint8_t start, uint8_t length, T& destination, T2 value) {
    destination &= (~static_cast<T>(bit_mask(start, length)));
    destination |= (static_cast<T>(value) << start);
}


constexpr auto max_value_on_bits(std::uint8_t bitsCount) {
    return (1 << bitsCount) - 1;
}

/*!
 * Take the lowest byte of numeric value.
 * @tparam T type of the value
 * @param value
 * @return Lowest byte of \ref value
 */
template<typename T>
constexpr std::uint8_t low_byte(T value) {
    return value & 0xFFu;
}

/*!
 * Take the highest byte of numeric value.
 * Defined only on arithmetic, unsigned values.
 * @tparam T tyoe of the value
 * @param value
 * @return Highest byte of \ref value
 */
template<typename T>
constexpr std::uint8_t high_byte(T value) {
    static_assert(std::is_arithmetic<T>() && std::is_unsigned<T>(),
                  "needs to be arithmetic type!");
    constexpr auto shift = 8 * (sizeof(T) - 1);
    return (value >> shift);
}

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_BIT_OPERATIONS_H_
