#ifndef HAL_PERIPH_MCU_SLEEP_H_
#define HAL_PERIPH_MCU_SLEEP_H_

#include <chrono>

namespace hal {

/*!
 * Generic delay for AVR microcontroller using std::chrono stuctures.
 * Behaves the same as std::this_thread::sleep_for on other platforms.
 * @param sleep_duration Duration sleep. Should be compile-time constant.
 */
template<class Rep, class Period>
constexpr void sleep_for(const std::chrono::duration<Rep, Period> sleep_duration) {
    const auto us =
        std::chrono::duration_cast<std::chrono::microseconds>(sleep_duration).count();
    _delay_us(us);
}

}  // namespace hal

#endif  // HAL_PERIPH_MCU_SLEEP_H_
