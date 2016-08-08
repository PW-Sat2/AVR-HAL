#ifndef FPF270X_H_
#define FPF270X_H_

namespace hal {
class FPF270x {
public:
    constexpr FPF270x(const DigitalIO::Pin pin_on,
            const DigitalIO::Pin pin_flag, const DigitalIO::Pin pin_pgood) :
            DIO_on(pin_on), DIO_flag(pin_flag), DIO_pgood(pin_pgood) {
    }

    void init() {
        this->DIO_on.init(DigitalIO::OUTPUT);
        this->DIO_flag.init(DigitalIO::INPUT_PULLUP);
        this->DIO_pgood.init(DigitalIO::INPUT_PULLUP);
    }

    void on() {
        this->DIO_on.reset();
    }

    void off() {
        this->DIO_on.set();
    }

    bool errorOccured() {
        return this->DIO_flag.read();
    }

    bool powerGood() {
        return this->DIO_pgood.read();
    }

private:
    DigitalIO DIO_on, DIO_flag, DIO_pgood;
};
}

#endif /* FPF270X_H_ */
