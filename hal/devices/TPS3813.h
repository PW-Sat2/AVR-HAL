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
template<int pulse_time_us>
class TPS3813 {
 public:
    /*!
     * Default ctor.
     * @param pin_WDI GPIO device used to kick watchdog.
     */
    constexpr explicit TPS3813(DigitalIO::Interface& pin_WDI)
        : pin_WDI{pin_WDI} {
    }

    /*!
     * Initializes device.
     * Has to be invoked before use of the device.
     */
    void init() const {
        this->pin_WDI.init(hal::DigitalIO::Interface::Mode::OUTPUT);
        this->pin_WDI.reset();
    }

    /*!
     * Method to kick watchdog timer.
     * Sends a pulse to device of specified time.
     */
    void kick() const {
        this->pin_WDI.set();
        _delay_us(pulse_time_us);
        this->pin_WDI.reset();
    }

 private:
    DigitalIO::Interface& pin_WDI;
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_TPS3813_H_
