#ifndef HAL_PERIPH_GPIO_IDIGITALIO_H_
#define HAL_PERIPH_GPIO_IDIGITALIO_H_

namespace hal {

class IDigitalIO {
 public:
    using Pin = uint8_t;

    enum class Mode {
        INPUT, OUTPUT, INPUT_PULLUP
    };

    virtual void init(const Mode mode) = 0;

    virtual void set() = 0;
    virtual void reset() = 0;
    virtual void toggle() = 0;
    virtual void write(bool value) = 0;

    virtual bool read() = 0;
};

}  // namespace hal

#endif  // HAL_PERIPH_GPIO_IDIGITALIO_H_
