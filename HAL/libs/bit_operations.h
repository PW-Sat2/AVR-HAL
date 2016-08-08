#ifndef HAL_LIBS_BIT_OPERATIONS_H_
#define HAL_LIBS_BIT_OPERATIONS_H_

namespace hal {


#define SBI(reg, bit) ((reg) |= (1 << (bit)))
#define CBI(reg, bit) ((reg) &= (~(1 << (bit))))
#define RBI(reg, bit)  (((reg) >> bit) & 0x1)


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
constexpr bool read_bit(const reg_type val, const int bit_pos) {
    return ((val >> bit_pos) & 0b1) ? true : false;
}

}  // namespace hal

#endif  // HAL_LIBS_BIT_OPERATIONS_H_
