#include <avr/eeprom.h>

#include "span.h"

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
    constexpr EepromStorage() : eeprom_ptr(getPointerFromAddess(getAndIncreaseBy(sizeof(T)))) {

    }

    T read() const {
        T data;
        this->read(libs::make_span(&data, sizeof(T)));
        return data;
    }

    operator T() const {
        return this->read();
    }

    void write(const T& data) const {
        this->write(libs::make_span(&data, sizeof(T)));
    }

    void operator=(const T& data) const {
        this->write(data);
    }

 private:
    void * getPointerFromAddess(size_t address) {
        return (void *)(address);
    }

    void read(libs::span<T> data_out) const {
        eeprom_read_block((void*)data_out.begin(), eeprom_ptr, sizeof(T));
    }
    void write(libs::span<const T> data_in) const {
        eeprom_write_block(data_in.begin(), eeprom_ptr, sizeof(T));
    }

    void * const eeprom_ptr;
};

}  // namespace hal
