#ifndef HAL_MCU_ATMEGA328P_TQFP32_MCU_ANALOG_H_
#define HAL_MCU_ATMEGA328P_TQFP32_MCU_ANALOG_H_

namespace hal {
namespace mcu {

class InternalADCMcuSpecific {
 public:
    InternalADCMcuSpecific() = delete;

    enum class Input : uint8_t {
        ADC0 = 0,
        ADC1 = 1,
        ADC2 = 2,
        ADC3 = 3,
        ADC4 = 4,
        ADC5 = 5,
        ADC6 = 6,
        ADC7 = 7,
        TempSensor = 8,
        REF1V1 = 14,
        REFGND = 15
    };

    template<Input input>
    static void disable_digital() {
        static_assert(input < Input::ADC6, "Disabling digital buffer allowed only on ADC0..8");
        DIDR0 |= (1 << static_cast<uint8_t>(input));
    }
};

}  // namespace mcu
}  // namespace hal

#endif  // HAL_MCU_ATMEGA328P_TQFP32_MCU_ANALOG_H_
