#ifndef HAL_PERIPH_TWI_H_
#define HAL_PERIPH_TWI_H_

#include <avr/io.h>
#include <util/twi.h>
#include "mcu.h"
#include "DigitalIO.h"
#include "I2C.h"
#include "compile_time.h"

namespace hal {

class TWI : public I2C_Base {
 public:
    template<uint32_t frequency>
    static void init() {
        set_speed<frequency>();
        TWCR = (1 << TWEN);
    }

    static void enable_internal_pullups() {
        DigitalIO pin_scl{mcu::pin_scl}, pin_sda{mcu::pin_sda};
        pin_scl.init(hal::DigitalIO::INPUT_PULLUP);
        pin_sda.init(hal::DigitalIO::INPUT_PULLUP);
    }

    static void disable() {
        TWCR = 0;
    }

    template<uint32_t frequency>
    static void set_speed() {
        TWSR = calc_twps<frequency>::value;
        TWBR = calc_twbr<frequency, calc_twps<frequency>::value>::value;
    }

    static bool start(uint8_t address, const StartAction_t start_action) {
        uint8_t twst;
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        wait_for_finish();
        twst = TW_STATUS;
        if ((twst != TW_START) && (twst != TW_REP_START)) {
            return false;
        }
        TWDR = (address << 1) | start_action;
        TWCR = (1 << TWINT) | (1 << TWEN);
        wait_for_finish();
        twst = TW_STATUS;
        if (((start_action == StartAction_t::START_READ) && (twst != TW_MR_SLA_ACK)) ||
            ((start_action == StartAction_t::START_WRITE) && (twst != TW_MT_SLA_ACK))) {
            return false;
        }
        return true;
    }

    static void stop(void) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
        while (TWCR & (1 << TWSTO)) {}
    }

    static bool write(const uint8_t data) {
        TWDR = data;
        TWCR = (1 << TWINT) | (1 << TWEN);
        wait_for_finish();
        uint8_t twst = TW_STATUS;
        if (twst != TW_MT_DATA_ACK) {
            return 1;
        }

        return 0;
    }

    static uint8_t read(Acknowledge_t ACK) {
        TWCR =  (1 << TWINT) | (1 << TWEN) | (ACK << TWEA);
        wait_for_finish();
        return TWDR;
    }

    static void write(const libs::array_view<const uint8_t> & arv) {
        auto size = arv.size();
        auto * data = arv.data();
        while (size--) {
            write(*data);
            data++;
        }
    }

    static void read(libs::array_view<uint8_t> arv, Acknowledge_t last_byte_ACK = NACK) {
        auto size = arv.size()-1;
        auto * data = arv.data();
        while(size--) {
            *data = read(ACK);
            data++;
        }
        *data = read(last_byte_ACK);
    }

 private:
    static void wait_for_finish() {
        while (read_bit(TWCR, TWINT) == false) {}
    }

    template<uint32_t frequency, int twps>
    struct calc_twbr {
        static const int32_t value = ((F_CPU/frequency)-16)/(2*libs::power<4, twps>::value);
    };

    template<uint32_t frequency, int twps = 0>
    struct calc_twps {
        static const int32_t value =
                (calc_twbr<frequency, twps>::value < 255 ) ?
                        twps :
                        calc_twps<frequency, twps+1>::value;
    };
    // recursion stop at max value of twps
    template<uint32_t frequency>
    struct calc_twps<frequency, 3> {
        static const int32_t value = 3;
    };
};

}  // namespace hal

#endif  // HAL_PERIPH_TWI_H_
