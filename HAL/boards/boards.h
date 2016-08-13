#ifndef HAL_BOARDS_BOARDS_H_
#define HAL_BOARDS_BOARDS_H_

#if defined(BOARD_ARDUINOMEGA2560)
#include "ArduinoMega2560/ArduinoMega2560.h"
#elif defined(BOARD_ARDUINONANO328_16MHZ) || defined(BOARD_ARDUINONANO328_8MHZ)
#include "ArduinoNano328/ArduinoNano328.h"
#elif defined(BOARD_EASYAVR128)
#include "easyAVR128/easyAVR128.h"
#endif

#endif  // HAL_BOARDS_BOARDS_H_
