#ifndef HAL_MCU_ATMEGA324P_TQFP32_MCU_WATCHDOG_H_
#define HAL_MCU_ATMEGA324P_TQFP32_MCU_WATCHDOG_H_

namespace hal {
namespace mcu {

class Watchdog {
 public:
    enum class Period : int {
        p_15ms = 0,
        p_30ms = 1,
        p_60ms = 2,
        p_120ms = 3,
        p_250ms = 4,
        p_500ms = 5,
        p_1000ms = 6,
        p_2000ms = 7,
        p_4000ms = 8,
        p_8000ms = 9
    };
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA324P_TQFP32_MCU_WATCHDOG_H_
