#ifndef HAL_PERIPH_DIGITALIO_INTERFACE_H_
#define HAL_PERIPH_DIGITALIO_INTERFACE_H_

namespace hal {
namespace DigitalIO {

using Pin = uint8_t;

enum class Mode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
};

}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_INTERFACE_H_
