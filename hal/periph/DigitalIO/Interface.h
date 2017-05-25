#ifndef HAL_PERIPH_DIGITALIO_INTERFACE_H_
#define HAL_PERIPH_DIGITALIO_INTERFACE_H_

namespace hal {
namespace DigitalIO {

class Interface {
 public:
    using Pin = uint8_t;

    enum class Mode {
        INPUT, OUTPUT, INPUT_PULLUP
    };

    virtual void init(const Mode mode) = 0;

    void set() {
        this->write(1);
    }

    virtual void reset() {
        this->write(0);
    }

    virtual void toggle() = 0;
    virtual void write(bool value) = 0;

    virtual bool read() = 0;
};

}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_INTERFACE_H_
