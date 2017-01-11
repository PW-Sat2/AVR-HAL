#ifndef HAL_BOARDS_BOARDS_H_
#define HAL_BOARDS_BOARDS_H_

#if defined(BOARD_ARDUINOMEGA2560)
    #include "ArduinoMega2560/ArduinoMega2560.h"
#elif defined(BOARD_SUNS_EM3)
    #include "SunS_EM3/SunS_EM3.h"
#elif defined(BOARD_ARDUINONANO328P_16MHZ) || defined(BOARD_ARDUINONANO328P_8MHZ)
    #include "ArduinoNano328P/ArduinoNano328P.h"
#elif defined(BOARD_RADFET_STAND)
    #include "RadFET_stand/RadFET_stand.h"
#elif defined(BOARD_EASYAVR128)
    #include "easyAVR128/easyAVR128.h"
#elif defined(BOARD_EVB_MEGA644P_16MHZ)
    #include "EVB/EVB.h"
#elif defined(BOARD_RADFET_EM1)
    #include "RadFET_EM1/RadFET_EM1.h"
#elif defined(BOARD_EVB_ATMEGA324P)
    #include "EVB_ATMega324p/EVB_ATMega324p.h"
#else
    #error "No board defined!"
#endif

#endif  // HAL_BOARDS_BOARDS_H_
