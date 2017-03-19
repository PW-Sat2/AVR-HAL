#ifndef HAL_DEVICES_AD5641_H_
#define HAL_DEVICES_AD5641_H_

#include "SPI.h"
#include "DigitalIO.h"
#include "bit_operations.h"
#include "array.h"
#include "writer.h"

namespace hal {

template<typename spi>
class AD5641 {
 public:
    constexpr AD5641(DigitalIO::Pin pin_sync) : spi_dev(pin_sync) {
    }

    void init() {
        spi_dev.init();
    }

    void write(uint16_t data_lsb) {
        data_lsb &= libs::bit_mask<0, 14>();

        libs::array<uint8_t, 2> data;
        libs::Writer writer{data};
        writer.WriteLowerBytesBE(data_lsb, 2);

        spi_dev.write(data);
    }

 private:
    const SPI::Device<spi> spi_dev;
};

}  // namespace hal


#endif  // HAL_DEVICES_AD5641_H_
