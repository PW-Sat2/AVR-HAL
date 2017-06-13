#ifndef HAL_DEVICES_TPS3813_H_
#define HAL_DEVICES_TPS3813_H_

#include "hal/periph.h"

namespace hal {
namespace devices {

/*!
 * TPS3813 Processor Supervisory Circuit with Window-Watchdog Timer driver.
 * @tparam pulse_time_us Duration of a kick pulse in microseconds
 * (max. 768 us / F_CPU in MHz).
 */
template<typename pin_WDI, uint16_t pulse_time_us>
struct TPS3813 {
    static_assert(pulse_time_us < (768000000 / F_CPU),
                  "Pulse duration too long - max. 768 us / F_CPU in MHz");
    /*!
     * Initializes device.
     * Has to be invoked before use of the device.
     */
    static void init() {
        pin_WDI::init(hal::DigitalIO::Mode::OUTPUT);
        pin_WDI::reset();
    }

    /*!
     * Method to kick watchdog timer.
     * Sends a pulse to device of specified time.
     */
    static void kick() {
        pin_WDI::set();
        _delay_us(pulse_time_us);
        pin_WDI::reset();
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_TPS3813_H_
