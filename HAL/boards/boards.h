#ifndef HAL_BOARDS_BOARDS_H_
#define HAL_BOARDS_BOARDS_H_

#ifndef BOARD
#error "No board defined!\nAdd BOARD= directive to your Makefile!"
#endif

// Macro for adding quotes
#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X

// clang-format off
#include STRINGIFY(BOARD/board.h)
// clang-format on

#undef STRINGIFY2
#undef STRINGIFY

#endif  // HAL_BOARDS_BOARDS_H_
