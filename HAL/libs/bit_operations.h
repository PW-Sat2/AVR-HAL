#ifndef HAL_LIBS_BIT_OPERATIONS_H_
#define HAL_LIBS_BIT_OPERATIONS_H_

namespace hal {

template<typename reg_type>
constexpr void set_bit(reg_type & val, const int bit_pos) {
    val |= (1 << bit_pos);
}

template<typename reg_type>
constexpr void set_bit(reg_type * val, const int bit_pos) {
    (*val) |= (1 << bit_pos);
}

template<typename reg_type>
constexpr void clear_bit(reg_type & val, const int bit_pos) {
    val &= (~(1 << bit_pos));
}

template<typename reg_type>
constexpr void clear_bit(reg_type * val, const int bit_pos) {
    (*val) &= (~(1 << bit_pos));
}

template<typename reg_type>
constexpr bool read_bit(const reg_type val, const int bit_pos) {
    return static_cast<bool>((val >> bit_pos) & 0b1);
}

}  // namespace hal

#endif  // HAL_LIBS_BIT_OPERATIONS_H_
