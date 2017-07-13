#ifndef HAL_PERIPH_DIGITALIO_DUMMY_H_
#define HAL_PERIPH_DIGITALIO_DUMMY_H_

namespace hal {
namespace DigitalIO {

/*!
 * Dummy GPIO pin.
 * Can be used with device drivers when pin does not exist on a board (or is
 * unused).
 * @tparam read_value value of pin which will be returned from read() function.
 * Default value false
 */
template<bool read_value = false>
struct Dummy : libs::PureStatic {
    template<typename T>
    static constexpr inline void init(const T&) {
    }

    static constexpr inline void set() {
    }

    static constexpr inline void reset() {
    }

    static constexpr inline void write(bool) {
    }

    static constexpr inline bool read() {
        return read_value;
    }

    static constexpr inline void toggle() {
    }
};

}  // namespace DigitalIO
}  // namespace hal

#endif  // HAL_PERIPH_DIGITALIO_DUMMY_H_
