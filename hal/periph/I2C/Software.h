#ifndef HAL_PERIPH_I2C_SOFTWARE_H_
#define HAL_PERIPH_I2C_SOFTWARE_H_

#include <util/delay.h>
#include "hal/periph/DigitalIO/Interface.h"
#include "_details.h"

namespace hal {
namespace I2C {

class Software : public details::_Interface {
 public:
    Software(DigitalIO::Interface& pin_sda, DigitalIO::Interface& pin_scl) : pin_sda{pin_sda}, pin_scl{pin_scl} {
    }

    void init() {
        pin_scl.init(DigitalIO::Interface::Mode::INPUT);
        pin_sda.init(DigitalIO::Interface::Mode::INPUT);
        pin_scl.reset();
        pin_sda.reset();
    }

    bool start(uint8_t address, const StartAction start_action) override {
        scl_high();
        hDelay();

        sda_low();
        hDelay();

        return write((address << 1) | static_cast<int>(start_action));
    }

    void stop() override {
        sda_low();
        hDelay();
        scl_high();
        qDelay();
        sda_high();
        hDelay();
    }

    bool write(uint8_t data) override {
        for (uint8_t i = 0; i < 8; ++i) {
            scl_low();
            qDelay();

            if (data & 0x80) {
                sda_high();
            } else {
                sda_low();
            }

            hDelay();
            scl_high();
            hDelay();

            while (pin_scl.read() == 0) {
            }

            data = data << 1;
        }

        // ACK Phase
        scl_low();
        qDelay();

        sda_high();
        hDelay();

        scl_high();
        hDelay();

        bool ack = !(pin_sda.read());

        scl_low();
        hDelay();

        return ack;
    }

    uint8_t read(Acknowledge ACK) override {
        uint8_t data = 0;

        for (uint8_t i = 0; i < 8; ++i) {
            scl_low();
            hDelay();
            scl_high();
            hDelay();

            while ((pin_scl.read()) == 0) {
            }

            if (pin_sda.read()) {
                data |= (0x80 >> i);
            }
        }
        scl_low();
        qDelay();

        if (ACK == true) {
            sda_low();
        } else {
            sda_high();
        }
        hDelay();

        scl_high();
        hDelay();

        scl_low();

        sda_high();
        hDelay();

        return data;
    }

 private:
    DigitalIO::Interface& pin_sda;
    DigitalIO::Interface& pin_scl;

    void qDelay() {
        _delay_loop_1(3);
    }
    void hDelay() {
        _delay_loop_1(5);
    }

    void sda_high() __attribute__((always_inline)) {
        pin_sda.init(DigitalIO::Interface::Mode::INPUT);
    }
    void sda_low() __attribute__((always_inline)) {
        pin_sda.init(DigitalIO::Interface::Mode::OUTPUT);
    }

    void scl_high() __attribute__((always_inline)) {
        pin_scl.init(DigitalIO::Interface::Mode::INPUT);
    }
    void scl_low() __attribute__((always_inline)) {
        pin_scl.init(DigitalIO::Interface::Mode::OUTPUT);
    }
};

}  // namespace I2C
}  // namespace hal

#endif  // HAL_PERIPH_I2C_SOFTWARE_H_