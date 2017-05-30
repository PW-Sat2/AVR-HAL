#include <hal/hal>


int main() {
    hal::Serial0.init(4800, hal::STDIO::ENABLE);
    printf("Start!\r\n");

    using ITG3200 = hal::ITG3200<hal::TWI>;
    hal::TWI::init<10000>();
    hal::TWI::enable_internal_pullups();
    constexpr ITG3200 gyro(0x68);

    gyro.set_interrupt_flags(ITG3200::LatchMode::LATCH,
                             ITG3200::LatchClearMethod::STATUS_REG_READ,
                             ITG3200::InterruptControl::INT_ENABLED,
                             ITG3200::InterruptControl::INT_ENABLED);
    gyro.init();
    gyro.set_clock(ITG3200::ClockSource::PLL_X_GYRO_REF);
    gyro.set_filters(1, ITG3200::LowPassFilter::LPF_256_HZ);

    _delay_ms(1000);

    while (true) {
        while (false == gyro.data_ready()) {
        }

        if (gyro.is_present()) {
            ITG3200::GyroData data = gyro.get_raw_gyro();
            printf("T: %f\tX: %d\tY: %d\tZ: %d\r\n",
                   gyro.get_temperature(),
                   data.X_axis,
                   data.Y_axis,
                   data.Z_axis);
        } else {
            printf("Gyro NOK!\r\n");
        }

        _delay_ms(10);
    }
}
