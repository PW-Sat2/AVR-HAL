#ifndef HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_
#define HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_

namespace hal {
namespace ExternalInterrupt {

enum class Mode : uint8_t {
    level_low = 0,
    change = 1,
    falling = 2,
    rising = 3
};

template<int int_nr, Mode mode = Mode::change>
void enable() {
    static_assert((int_nr >= 0) && (int_nr <= 7), "This device has INT0..7!");
    static_assert((int_nr >= 4) || (mode != Mode::change), "INTs 0..3 cannot have change mode!");

    if( int_nr < 4 ) {
        EICRA &= (~(0b11 << int_nr));
        EICRA |= (static_cast<uint8_t>(mode) << int_nr);
    } else {
        EICRB &= (~(0b11 << (int_nr-4)));
        EICRB |= (static_cast<uint8_t>(mode) << (int_nr-4));
    }
    SBI(EIMSK, int_nr);
}

template<int int_nr>
void disable() {
    CBI(EIMSK, int_nr);
}

}  // namespace ExternalInterrupt
}  // namespace hal

#endif /* HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_ */
