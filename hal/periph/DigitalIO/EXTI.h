#ifndef HAL_PERIPH_DIGITALIO_EXTI_H_
#define HAL_PERIPH_DIGITALIO_EXTI_H_

#include "hal/libs.h"

namespace hal {
namespace DigitalIO {
namespace ExternalInterrupt {

enum class Mode : uint8_t {
    level_low = 0,
    change    = 1,
    falling   = 2,
    rising    = 3,
};

template<uint8_t interrupt_nr, Mode mode>
class Line : libs::PureStatic {
 public:
    static_assert(interrupt_nr < 8, "Interrupt lines can be from 0 to 7!");

    static void enable() {
#ifdef EIMSK
        disable();

        if (interrupt_nr < 4) {
            libs::write_mask<2 * interrupt_nr, 2>(EICRA, mode);
        } else {
#ifdef EICRB
            libs::write_mask(2 * (interrupt_nr - 4), 2, EICRB, mode);
#endif
        }
        libs::set_bit<interrupt_nr>(EIMSK);
#else
#error Sorry, EXTI on this MCU is not implemented!
#endif
    }

    static void disable() {
        libs::clear_bit<interrupt_nr>(EIMSK);
    }
};

}  // namespace ExternalInterrupt
}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_EXTI_H_
