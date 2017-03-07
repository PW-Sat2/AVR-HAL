#ifndef HAL_LIBS_BIT_OPERATIONS_H_
#define HAL_LIBS_BIT_OPERATIONS_H_

namespace hal {

template<typename reg_type>
constexpr inline void set_bit(reg_type & val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void set_bit(reg_type & val, const int bit_pos) {
    val |= (1UL << bit_pos);
}


template<typename reg_type>
constexpr inline void set_bit(reg_type * val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void set_bit(reg_type * val, const int bit_pos) {
    (*val) |= (1UL << bit_pos);
}


template<typename reg_type>
constexpr inline void clear_bit(reg_type & val, const int bit_pos) __attribute__((always_inline));
template<typename reg_type>
constexpr inline void clear_bit(reg_type & val, const int bit_pos) {
    val &= (~(1UL << bit_pos));
}


template<typename reg_type>
constexpr inline void clear_bit(reg_type * val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline void clear_bit(reg_type * val, const int bit_pos) {
    (*val) &= (~(1UL << bit_pos));
}


template<typename reg_type>
constexpr inline bool read_bit(const reg_type val, const int bit_pos) __attribute__((always_inline));

template<typename reg_type>
constexpr inline bool read_bit(const reg_type val, const int bit_pos) {
    return static_cast<bool>((val >> bit_pos) & 0b1);
}

}  // namespace hal

#endif  // HAL_LIBS_BIT_OPERATIONS_H_
