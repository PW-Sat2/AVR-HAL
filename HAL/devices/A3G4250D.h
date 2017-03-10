#ifndef HAL_DEVICES_A3G4250D_H_
#define HAL_DEVICES_A3G4250D_H_

#include <stdlib.h>
#include "I2C.h"
#include "array.h"

namespace hal {
template<typename I2C>
class A3G4250D {
 public:
    struct GyroData {
        int16_t X_axis;
        int16_t Y_axis;
        int16_t Z_axis;
    };

    enum LatchMode {
        PULSE = 0,
        LATCH = 1
    };

    enum LatchClearMethod {
        STATUS_REG_READ = 0,
        ANY_REG_READ = 1
    };

    enum InterruptControl {
        INT_DISABLED = 0,
        INT_ENABLED = 1
    };

    enum InterruptPinLogic {
        ACTIVE_HIGH = 0,
        ACTIVE_LOW = 1
    };

    enum InterruptDriveType {
        PUSH_PULL = 0,
        OPEN_DRAIN = 1
    };

    enum PowerMode {
        SLEEP = 0,
        ACTIVE = 1
    };

    enum AxisPowerMode {
        POWER_DOWN = 0,
        NORMAL = 1
    };

    enum LowPassFilter {
        LPF_256_HZ = 0,
        LPF_188_HZ = 1,
        LPF_98_HZ = 2,
        LPF_42_HZ = 3,
        LPF_20_HZ = 4,
        LPF_10_HZ = 5,
        LPF_5_HZ = 6
    };

    enum ClockSource {
        INTERNAL_OSC = 0,
        PLL_X_GYRO_REF = 1,
        PLL_Y_GYRO_REF = 2,
        PLL_Z_GYRO_REF = 3,
        PLL_32_KHZ_REF = 4,
        PLL_19_MHZ_REF = 5
    };


    struct Status {
        bool ZYXOR;
        bool ZYXDA;
    };

    enum class DataOutputPath {
        LP1_ONLY = 0b000,
        HP_FILTERED = 0b001,
        LP2_FILTERED = 0b010,
        LP2_HP_FILTERED = 0b111
    };

    enum class HighPassFilterMode {
        NORMAL_HP_RESET_FILTER = 0b00,
        REFERENCE_SIGNAL_FOR_FILTERING = 0b01,
        NORMAL_MODE = 0b10,
        AUTO_RESET_ON_INT = 0b11
    };

    enum class HighPassFilterCutOff {
        HP_8_15_30_56_HZ = 0b0000,
        HP_4_8_15_30_HZ = 0b0001,
        HP_2_4_8_15_HZ = 0b0010,
        HP_1_2_4_8_HZ = 0b0011,
        HP_05_1_2_4_HZ = 0b0100,
        HP_02_05_1_2_HZ = 0b0101,
        HP_01_02_05_1_HZ = 0b0110,
        HP_005_01_02_05_HZ = 0b1000,
        HP_001_002_005_01_HZ = 0b1001
    };

    enum class DataRateCutOff {
        DR_00_BW_00_100_Hz_CF_12_5 = 0b0000,
        DR_00_BW_01_100_Hz_CF_25 = 0b0001,
        DR_00_BW_10_100_Hz_CF_25 = 0b0010,
        DR_00_BW_11_100_Hz_CF_25 = 0b0011,
        DR_01_BW_00_200_Hz_CF_12_5 = 0b0100,
        DR_01_BW_01_200_Hz_CF_25 = 0b0101,
        DR_01_BW_10_200_Hz_CF_50 = 0b0110,
        DR_01_BW_11_200_Hz_CF_70 = 0b0111,
        DR_10_BW_00_400_Hz_CF_20 = 0b1000,
        DR_10_BW_01_400_Hz_CF_25 = 0b1001,
        DR_10_BW_10_400_Hz_CF_50 = 0b1010,
        DR_10_BW_11_400_Hz_CF_110 = 0b1011,
        DR_11_BW_00_800_Hz_CF_30 = 0b1100,
        DR_11_BW_01_800_Hz_CF_35 = 0b1101,
        DR_11_BW_10_800_Hz_CF_50 = 0b1110,
        DR_11_BW_11_800_Hz_CF_110 = 0b1111
    };

    enum class SelfTest {
        DISABLED = 0b00,
        SELF_TEST_0 = 0b01,
        SELF_TEST_1 = 0b11
    };

    constexpr A3G4250D(const uint8_t address) : i2cdevice{address} {
    }

    bool is_present() const {
        return 0b11010011 == get_id();
    }

    uint8_t get_id() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(Registers::WHO_AM_I, data);
        return data[0];
    }

    void set_data_rate_bandwidth(DataRateCutOff dr_cf) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::CTRL_REG1, read_data);

        libs::array<uint8_t, 1> data = {(read_data[0] & 0b00001111) | (static_cast<uint8_t>(dr_cf) << 4)};
        i2cdevice.write_register(Registers::CTRL_REG1, data);
    }

    void set_power_mode(PowerMode power, AxisPowerMode x_standby, AxisPowerMode y_standby, AxisPowerMode z_standby) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::CTRL_REG1, read_data);

        libs::array<uint8_t, 1> data = {(read_data[0] & 0b11110000) 
            | (static_cast<uint8_t>(power) << 3)
            | (static_cast<uint8_t>(x_standby) << 2)
            | (static_cast<uint8_t>(y_standby) << 1)
            | (static_cast<uint8_t>(z_standby) << 0)
        };

        i2cdevice.write_register(Registers::CTRL_REG1, data);
    }

    void high_pass_filter(HighPassFilterMode mode, HighPassFilterCutOff cutoff) const {
        libs::array<uint8_t, 1> data1 = {(static_cast<uint8_t>(mode) << 4) | (static_cast<uint8_t>(cutoff))};
        i2cdevice.write_register(Registers::CTRL_REG2, data1);
    }

    void data_output_path(DataOutputPath path) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::CTRL_REG5, read_data);

        libs::array<uint8_t, 1> data2 = {((read_data[0] & 0b11101100) | ((static_cast<uint8_t>(path) & 0b100) << 4) | (static_cast<uint8_t>(path) & 0b011))};
        i2cdevice.write_register(Registers::CTRL_REG5, data2);
    }

    uint8_t get_temperature_raw() const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::OUT_TEMP, read_data);
        return read_data[0];
    }

    Status status() const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::STATUS_REG, read_data);
        
        Status stat;

        if (read_data[0] & 0b00000001) {
            stat.ZYXOR = true;
        } else {
            stat.ZYXOR = false;
        }

        if (read_data[0] & 0b00010000) {
            stat.ZYXDA = true;
        } else {
            stat.ZYXDA = false;
        }

        return stat;
    }

    bool data_ready() const {
        return status().ZYXDA;
    }

    GyroData get_raw_gyro() const {
        libs::array<uint8_t, 6> read_data;
        i2cdevice.read_register(Registers::OUT_X_L | (1 << 7), read_data);
        GyroData data;

        data.X_axis = (static_cast<int16_t>(read_data[1]) << 8) | read_data[0];
        data.Y_axis = (static_cast<int16_t>(read_data[3]) << 8) | read_data[2];
        data.Z_axis = (static_cast<int16_t>(read_data[5]) << 8) | read_data[4];

        return data;
    }

    void self_test(SelfTest st) const {
        libs::array<uint8_t, 1> data_rcv;
        i2cdevice.read_register(Registers::CTRL_REG4, data_rcv);

        libs::array<uint8_t, 1> data_snd = {((data_rcv[0] & 0b11111001) | (static_cast<uint8_t>(st) << 1))};
        i2cdevice.write_register(Registers::CTRL_REG4, data_snd);
    }

 private:
    enum Registers {
        WHO_AM_I = 0x0F,
        CTRL_REG1 = 0x20,
        CTRL_REG2 = 0x21,
        CTRL_REG3 = 0x22,
        CTRL_REG4 = 0x23,
        CTRL_REG5 = 0x24,
        REFERENCE = 0x25,
        OUT_TEMP = 0x26,
        STATUS_REG = 0x27,
        OUT_X_L = 0x28,
        OUT_X_H = 0x29,
        OUT_Y_L = 0x2A,
        OUT_Y_H = 0x2B,
        OUT_Z_L = 0x2C,
        OUT_Z_H = 0x2D,
        FIFO_CTRL_REG = 0x2E,
        FIFO_SRC_REG = 0x2F,
        INT1_CFG = 0x30,
        INT1_SRC = 0x31,
        INT1_TSH_XH = 0x32,
        INT1_TSH_XL = 0x33,
        INT1_TSH_YH = 0x34,
        INT1_TSH_YL = 0x35,
        INT1_TSH_ZH = 0x36,
        INT1_TSH_ZL = 0x37,
        INT1_DURATION = 0x38
    };

    const I2C_Device<I2C> i2cdevice;
};

}  // namespace hal

#endif  // HAL_DEVICES_ITG3200_H_
