#ifndef HAL_LIBS_DEVICE_SUPPORTS_LM60_H_
#define HAL_LIBS_DEVICE_SUPPORTS_LM60_H_

namespace hal {
namespace libs {

namespace LM60 {
    static float temperature(float mV) {
        return (mV - 434)/6.25;
    }
}  // namespace LM60

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_DEVICE_SUPPORTS_LM60_H_
