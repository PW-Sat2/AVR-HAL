#ifndef HAL_PERIPH_MCU_EEPROM_H_
#define HAL_PERIPH_MCU_EEPROM_H_

#include <avr/eeprom.h>

#include "hal/libs.h"

namespace hal {

/*!
 * EEPROM memory wrapper.
 * For given type T and object in eeprom memory it will ease access to
 * underlying type.
 * @tparam T Type of underlying object
 */
template<typename T>
class EepromWrapper {
 public:
    /*!
     * Constructor. Provide object defined with EEMEM attribute (placed in
     * EEPROM memory).
     * @param data_eeprom Object to wrap
     */
    explicit constexpr EepromWrapper(T& data_eeprom)
        : eeprom_ptr{&data_eeprom} {
    }

    /*!
     * Read data from EEPROM.
     * @return Data read from EEPROM.
     */
    T read() const {
        T data;
        read(gsl::make_span(&data, size));
        return data;
    }

    /*!
     * Read data from EEPROM. Allows reads without .read() method
     * @return Data read from EEPROM.
     */
    operator T() const {
        return this->read();
    }

    /*!
     * Write data to EEPROM object.
     * @param data Data to write
     */
    void write(const T& data) const {
        write(gsl::make_span(&data, size));
    }

    /*!
     * Write data to EEPROM object.
     * @param data Data to write
     */
    void operator=(const T& data) const {
        this->write(data);
    }

 private:
    void read(gsl::span<T> data_out) const {
        eeprom_read_block(data_out.begin(), eeprom_ptr, size);
    }
    void write(gsl::span<const T> data_in) const {
        eeprom_write_block(data_in.begin(), eeprom_ptr, size);
    }

    void* const eeprom_ptr;
    constexpr static auto size = sizeof(T);
};

}  // namespace hal

#endif  // HAL_PERIPH_MCU_EEPROM_H_
