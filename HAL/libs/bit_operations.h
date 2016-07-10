#ifndef HAL_BIT_OPERATIONS_H_
#define HAL_BIT_OPERATIONS_H_

#define SBI(reg, bit) ((reg) |= (1 << (bit)))
#define CBI(reg, bit) ((reg) &= (~(1 << (bit))))
#define RBI(reg, bit)  (((reg) >> bit) & 0x1)

#endif  // HAL_BIT_OPERATIONS_H_
