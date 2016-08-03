#ifndef HAL_PERIPH_SOFTI2C_H_
#define HAL_PERIPH_SOFTI2C_H_

#include "DigitalIO.h"
#include "I2C.h"

namespace hal {

template<int pin_nr_scl, int pin_nr_sda>
class SoftI2C_t: public I2C_Base {
public:
    static void init() {
        pin_scl.init(DigitalIO::Mode::INPUT);
        pin_sda.init(DigitalIO::Mode::INPUT);
        pin_scl.reset();
        pin_sda.reset();
    }

    static bool start(uint8_t address, const StartAction_t start_action) {
        pin_scl.pinmode(DigitalIO::Mode::INPUT);
        hDelay();

        pin_sda.pinmode(DigitalIO::Mode::OUTPUT);
        hDelay();

        return write((address << 1) | start_action);
    }

    static void stop() {
        pin_sda.pinmode(DigitalIO::Mode::OUTPUT);
        hDelay();
        pin_scl.pinmode(DigitalIO::Mode::INPUT);
        qDelay();
        pin_sda.pinmode(DigitalIO::Mode::INPUT);
        hDelay();
    }

    static bool write(uint8_t data) {
        for (uint8_t i = 0; i < 8; ++i) {
            pin_scl.pinmode(DigitalIO::Mode::OUTPUT);
            qDelay();

            if (data & 0x80) {
                pin_sda.pinmode(DigitalIO::Mode::INPUT);
            } else {
                pin_sda.pinmode(DigitalIO::Mode::OUTPUT);
            }

            hDelay();
            pin_scl.pinmode(DigitalIO::Mode::INPUT);
            hDelay();

            while (pin_scl.read() == 0) {
            };

            data = data << 1;
        }

        // ACK Phase
        pin_scl.pinmode(DigitalIO::Mode::OUTPUT);
        qDelay();

        pin_sda.pinmode(DigitalIO::Mode::INPUT);
        hDelay();

        pin_scl.pinmode(DigitalIO::Mode::INPUT);
        hDelay();

        bool ack = !(pin_sda.read());

        pin_scl.pinmode(DigitalIO::Mode::OUTPUT);
        hDelay();

        return ack;
    }

    static uint8_t read(Acknowledge_t ACK) {
        uint8_t data = 0;

        for (uint8_t i = 0; i < 8; ++i) {
            pin_scl.pinmode(DigitalIO::Mode::OUTPUT);
            hDelay();
            pin_scl.pinmode(DigitalIO::Mode::INPUT);
            hDelay();

            while ((pin_scl.read()) == 0) {
            };

            if (pin_sda.read()) {
                data |= (0x80 >> i);
            }

        }
        pin_scl.pinmode(DigitalIO::Mode::OUTPUT);
        qDelay();

        if (ACK == true) {
            pin_sda.pinmode(DigitalIO::Mode::OUTPUT);
        } else {
            pin_sda.pinmode(DigitalIO::Mode::INPUT);
        }
        hDelay();

        pin_scl.pinmode(DigitalIO::Mode::INPUT);
        hDelay();

        pin_scl.pinmode(DigitalIO::Mode::OUTPUT);

        pin_sda.pinmode(DigitalIO::Mode::INPUT);
        hDelay();

        return data;
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
    constexpr static DigitalIO pin_sda{pin_nr_sda}, pin_scl{pin_nr_scl};

    static void qDelay() {
        _delay_loop_2(3);
    }

    static void hDelay() {
        _delay_loop_2(5);
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_SOFTI2C_H_
