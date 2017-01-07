#ifndef HAL_BOARDS_BOARDS_H_
#define HAL_BOARDS_BOARDS_H_

#if defined(BOARD_ARDUINOMEGA2560)
#include "ArduinoMega2560/ArduinoMega2560.h"
#elif defined(BOARD_ARDUINONANO328P_16MHZ) || defined(BOARD_ARDUINONANO328P_8MHZ)
#include "ArduinoNano328P/ArduinoNano328P.h"
#elif defined(BOARD_EASYAVR128)
#include "easyAVR128/easyAVR128.h"
#elif defined(BOARD_EVB_MEGA644P_16MHZ)
#include "EVB/EVB.h"
#elif defined(BOARD_ATMEGA324P)
#include "ATMEGA324P/ATMEGA324P.h"
#else
#error "No board defined!"
#endif

#endif  // HAL_BOARDS_BOARDS_H_
