#include <util/delay.h>
#include "Serial.h"
#include "I2C.h"
#include "SoftI2C.h"
#include "A3G4250D.h"
#include "array.h"


int main() {
    hal::Serial0.init(19200, hal::STDIO::ENABLE);
    printf("Start!\r\n");

    using SoftI2C = hal::SoftI2C<13, 14>;
    SoftI2C::init();

    using A3G4250D = hal::A3G4250D<SoftI2C>;
    constexpr A3G4250D gyro(0b1101001);
    gyro.set_default();
    gyro.set_data_rate_bandwidth(A3G4250D::DataRateCutOff::DR_00_BW_00_100_Hz_CF_12_5);
    gyro.set_power_mode(A3G4250D::PowerMode::ACTIVE, A3G4250D::AxisPowerMode::NORMAL, A3G4250D::AxisPowerMode::NORMAL, A3G4250D::AxisPowerMode::NORMAL);
    gyro.data_output_path(A3G4250D::DataOutputPath::LP2_FILTERED);
    // set up the gyro

    _delay_ms(1000);

    while (true) {
        printf("Rcv: %u\r\n", gyro.get_id());

        if (gyro.is_present()) {
            printf("Gyro OK!\r\n");
            while(false == gyro.status().ZYXDA) {
                printf("Data not ready\r\n");
            }

            A3G4250D::GyroData data = gyro.get_raw_gyro();
            printf("T: %d\tX: %d\tY: %d\tZ: %d\r\n", gyro.get_temperature_raw(), data.X_axis, data.Y_axis, data.Z_axis);
        } else {
            printf("Gyro NOK!\r\n");
        }

        _delay_ms(100);
    }
}
