#ifndef HAL_PERIPH_MCU_EEPROM_H_
#define HAL_PERIPH_MCU_EEPROM_H_

#include <avr/eeprom.h>

#include "hal/libs.h"

namespace hal {

namespace details {
class AddressCounter {
 public:
    static size_t getAndIncreaseBy(size_t c) {
        auto now = counter;
        counter += c;
        return now;
    }

 private:
    static size_t counter;
};

}  // namespace details

template<typename T>
class EepromStorage : details::AddressCounter {
 public:
    constexpr EepromStorage()
        : eeprom_ptr(getPointerFromAddess(getAndIncreaseBy(size))) {
    }

    T read() const {
        T data;
        this->read(gsl::make_span(&data, size));
        return data;
    }

    operator T() const {
        return this->read();
    }

    void write(const T& data) const {
        this->write(gsl::make_span(&data, size));
    }

    void operator=(const T& data) const {
        this->write(data);
    }

 private:
    void* getPointerFromAddess(size_t address) {
        return reinterpret_cast<void*>(address);
    }

    void read(gsl::span<T> data_out) const {
        eeprom_read_block(static_cast<void*>(data_out.begin()), eeprom_ptr, size);
    }
    void write(gsl::span<const T> data_in) const {
        eeprom_write_block(data_in.begin(), eeprom_ptr, size);
    }

    void* const eeprom_ptr;
    constexpr static auto size = sizeof(T);
};

}  // namespace hal

#endif  // HAL_PERIPH_MCU_EEPROM_H_
