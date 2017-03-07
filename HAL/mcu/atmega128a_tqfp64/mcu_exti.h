#ifndef HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_
#define HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_

namespace hal {

extern int impossible_exti_line;
extern int impossible_exti_mode_at_this_line;

class ExternalInterrupt {
 public:
    enum class Mode : uint8_t {
        level_low = 0,
        change = 1,
        falling = 2,
        rising = 3
    };

    constexpr ExternalInterrupt(int pin_nr, Mode mode) :
                                int_nr{check_pin(pin_nr, mode)},
                                mode{mode} {
    }

    constexpr static int check_pin(int pin_nr, Mode mode) {
        return (pin_nr >= 0) ?
                ((pin_nr < 8) ?
                    (((pin_nr > 3) || (mode != Mode::change)) ?
                        pin_nr :
                        impossible_exti_mode_at_this_line) :
                    impossible_exti_line) :
                impossible_exti_line;
    }

    void enable() const {
        disable();
        if (int_nr < 4) {
            EICRA &= (~(0b11 << 2*int_nr));
            EICRA |= (static_cast<uint8_t>(mode) << 2*int_nr);
        } else {
            EICRB &= (~(0b11 << (2*(int_nr-4))));
            EICRB |= (static_cast<uint8_t>(mode) << (2*(int_nr-4)));
        }
        set_bit(EIMSK, int_nr);
    }

    void disable() const {
        clear_bit(EIMSK, int_nr);
    }

 private:
    const int int_nr;
    const Mode mode;
};

}  // namespace hal

#endif  // HAL_MCU_ATMEGA128A_TQFP64_MCU_EXTI_H_
