#include <hal/hal>

int main() {
    hal::Serial0.init(4800, hal::STDIO::ENABLE);
    printf("Start!\r\n");

    hal::TWI::init<10000>();
    hal::TWI::enable_internal_pullups();

    using A3G4250D = hal::A3G4250D<hal::TWI>;
    constexpr A3G4250D gyro(A3G4250D::I2C_Address::SEL_HIGH);
    gyro.set_data_rate_bandwidth(
        A3G4250D::DataRateCutOff::DR_00_BW_00_100_Hz_CF_12_5);
    gyro.set_power_mode(A3G4250D::PowerMode::ACTIVE,
                        A3G4250D::AxisPowerMode::NORMAL,
                        A3G4250D::AxisPowerMode::NORMAL,
                        A3G4250D::AxisPowerMode::NORMAL);
    gyro.data_output_path(A3G4250D::DataOutputPath::LP2_FILTERED);

    _delay_ms(1000);

    while (true) {
        printf("Rcv: %u\r\n", gyro.get_id());

        if (gyro.is_present()) {
            printf("Gyro OK!\r\n");
            while (false == gyro.status().DATA_AVAILABLE) {
                printf("Data not ready\r\n");
                _delay_ms(100);
            }

            A3G4250D::GyroData data = gyro.get_raw_gyro();
            printf("T: %d\tX: %d\tY: %d\tZ: %d\r\n",
                   gyro.get_temperature_raw(),
                   data.X_axis,
                   data.Y_axis,
                   data.Z_axis);
        } else {
            printf("Gyro NOK!\r\n");
        }

        _delay_ms(100);
    }
}
