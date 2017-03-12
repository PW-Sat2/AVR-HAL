#ifndef HAL_DEVICES_ITG3200_H_
#define HAL_DEVICES_ITG3200_H_

#include "I2C.h"
#include "array.h"
#include "reader.h"
#include "bit_operations.h"

namespace hal {
template<typename I2C>
class ITG3200 {
 public:
    struct GyroData {
        int16_t X_axis;
        int16_t Y_axis;
        int16_t Z_axis;
    };

    enum class LatchMode {
        PULSE = 0,
        LATCH = 1
    };

    enum class LatchClearMethod {
        STATUS_REG_READ = 0,
        ANY_REG_READ = 1
    };

    enum class InterruptControl {
        INT_DISABLED = 0,
        INT_ENABLED = 1
    };

    enum class InterruptPinLogic {
        ACTIVE_HIGH = 0,
        ACTIVE_LOW = 1
    };

    enum class InterruptDriveType {
        PUSH_PULL = 0,
        OPEN_DRAIN = 1
    };

    enum class PowerMode {
        ACTIVE = 0,
        SLEEP = 1
    };

    enum class AxisPowerMode {
        NORMAL = 0,
        STANDBY = 1
    };

    enum class LowPassFilter {
        LPF_256_HZ = 0,
        LPF_188_HZ = 1,
        LPF_98_HZ = 2,
        LPF_42_HZ = 3,
        LPF_20_HZ = 4,
        LPF_10_HZ = 5,
        LPF_5_HZ = 6
    };

    enum class ClockSource {
        INTERNAL_OSC = 0,
        PLL_X_GYRO_REF = 1,
        PLL_Y_GYRO_REF = 2,
        PLL_Z_GYRO_REF = 3,
        PLL_32_KHZ_REF = 4,
        PLL_19_MHZ_REF = 5
    };

    constexpr ITG3200(const uint8_t address) : i2cdevice{address} {
    }

    bool is_present() const {
        return 0b110100 == get_id();
    }

    uint8_t get_id() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(Registers::WHO_AM_I, data);
        return libs::read_mask<1, 5>(data[0]);
    }

    void set_filters(uint8_t sample_rate_div, LowPassFilter lpf) const {
        libs::array<uint8_t, 2> data = {sample_rate_div, static_cast<uint8_t>((0x18 | static_cast<uint8_t>(lpf)))};
        i2cdevice.write_register(Registers::SMPLRT_DIV, data);
    }

    int16_t get_temperature_raw() const {
        libs::array<uint8_t, 2> data;
        i2cdevice.read_register(Registers::TEMP_OUT_H, data);
        libs::Reader reader{data};
        return (reader.ReadSignedWordBE());
    }

    float get_temperature() const {
        int16_t temp_raw = get_temperature_raw();
        return static_cast<float>(temp_raw + 23000)/280;
    }

    GyroData get_raw_gyro() const {
        libs::array<uint8_t, 6> data;
        i2cdevice.read_register(Registers::GYRO_XOUT_H, data);

        libs::Reader reader{data};
        GyroData gyro_data;

        gyro_data.X_axis = reader.ReadSignedWordBE();
        gyro_data.Y_axis = reader.ReadSignedWordBE();
        gyro_data.Z_axis = reader.ReadSignedWordBE();

        return gyro_data;
    }

    void set_clock(ClockSource clock) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::PWR_MGM, read_data);

        libs::write_mask<0, 3>(read_data[0], static_cast<uint8_t>(clock));
        i2cdevice.write_register(Registers::PWR_MGM, read_data);
    }

    void set_power(PowerMode sleep, AxisPowerMode x_standby, AxisPowerMode y_standby, AxisPowerMode z_standby) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::PWR_MGM, read_data);

        libs::write_bit<6>(read_data[0], static_cast<uint8_t>(sleep));
        libs::write_bit<5>(read_data[0], static_cast<uint8_t>(x_standby));
        libs::write_bit<4>(read_data[0], static_cast<uint8_t>(y_standby));
        libs::write_bit<3>(read_data[0], static_cast<uint8_t>(z_standby));

        i2cdevice.write_register(Registers::PWR_MGM, read_data);
    }

    void hardware_reset() const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::PWR_MGM, read_data);

        libs::set_bit(read_data[0], 7);
        i2cdevice.write_register(Registers::PWR_MGM, read_data);
    }

    void init() const {
        libs::array<uint8_t, 1> data = {0x18};
        i2cdevice.write_register(Registers::DLPF_FS, data);
    }

    bool sensor_pll_ready() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(Registers::INT_STATUS, data);

        return libs::read_bit(data[0], 2);
    }

    bool data_ready() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(Registers::INT_STATUS, data);

        return libs::read_bit(data[0], 1);
    }

    void set_interrupt_pin(InterruptPinLogic logic, InterruptDriveType otype) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::INT_CFG, read_data);

        libs::write_bit<7>(read_data[0], static_cast<uint8_t>(logic));
        libs::write_bit<6>(read_data[0], static_cast<uint8_t>(otype));

        i2cdevice.write_register(Registers::INT_CFG, read_data);
    }

    void set_interrupt_flags(LatchMode latch_mode, LatchClearMethod latch_method, InterruptControl itg_rdy, InterruptControl data_rdy) const {
        libs::array<uint8_t, 1> read_data;
        i2cdevice.read_register(Registers::INT_CFG, read_data);

        libs::write_bit<5>(read_data[0], static_cast<uint8_t>(latch_mode));
        libs::write_bit<4>(read_data[0], static_cast<uint8_t>(latch_method));
        libs::write_bit<2>(read_data[0], static_cast<uint8_t>(itg_rdy));
        libs::write_bit<0>(read_data[0], static_cast<uint8_t>(data_rdy));
        
        i2cdevice.write_register(Registers::INT_CFG, read_data);
    }

 private:
    enum Registers {
        WHO_AM_I = 0x00,
        SMPLRT_DIV = 0x15,
        DLPF_FS = 0x16,
        INT_CFG = 0x17,
        INT_STATUS = 0x1A,
        TEMP_OUT_H = 0x1B,
        TEMP_OUT_L = 0x1C,
        GYRO_XOUT_H = 0x1D,
        GYRO_XOUT_L = 0x1E,
        GYRO_YOUT_H = 0x1F,
        GYRO_YOUT_L = 0x20,
        GYRO_ZOUT_H = 0x21,
        GYRO_ZOUT_L = 0x22,
        PWR_MGM = 0x3E
    };

    const I2C_Device<I2C> i2cdevice;
};

}  // namespace hal

#endif  // HAL_DEVICES_ITG3200_H_
