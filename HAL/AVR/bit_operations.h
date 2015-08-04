#ifndef HAL_AVR_BIT_OPERATIONS_H_
#define  HAL_AVR_BIT_OPERATIONS_H_


#define sbi(reg, bit) ((reg) |= (1 << (bit)))
#define cbi(reg, bit) ((reg) &= (~(1 << (bit))))
#define read_bit(reg, bit)  (((reg) >> bit) & 0x1)

// #define bit_is_clear(sfr,bit) (!(sfr & (1 << bit)))

#endif  // HAL_AVR_BIT_OPERATIONS_H_
