#ifndef HAL_DEVICES_LM60_H_
#define HAL_DEVICES_LM60_H_

namespace hal {

class LM60 {
 public:
    LM60() = delete;

    static float temperature(float mV) {
        return (mV - 434)/6.25;
    }
};

}  // namespace hal

#endif  // HAL_DEVICES_LM60_H_
