/*
 * AD7714.h
 *
 * Created: 2015-07-29 15:17:39
 * Author: begreen / rexina
 */ 

#ifndef DEVICES_AD7714_H_
#define DEVICES_AD7714_H_

#include "GPIO.h"
#include "SPI.h"


class AD7714_t {
 public:
    SPI_Device_t AD7714_SPI;

    enum ADC_Registers {
        COMM_REG = 0,
        MODE_REG = 1,
        FILTER_HIGH_REG = 2,
        FILTER_LOW_REG = 3,
        TEST_REG = 4,
        DATA_REG = 5,
        ZERO_SCALE_CALIB_REG = 6,
        FULL_SCALE_CALIB_REG = 7
    };

    enum ADC_Channels {
        AIN1_CH = 0,
        AIN2_CH = 1,
        AIN3_CH = 2,
        AIN4_CH = 3,
        AIN5_CH = 6,
        AIN1_2_CH = 4,
        AIN3_4_CH = 5,
        AIN5_6_CH = 6,
        TEST_CH = 7
    };

    enum ADC_Gain {
        Gain_1 = 0,
        Gain_2 = 1,
        Gain_4 = 2,
        Gain_8 = 3,
        Gain_16 = 4,
        Gain_32 = 5,
        Gain_64 = 6,
        Gain_128 = 7
    };

    enum DataLength {
        Data_24bit = 1,
        Data_16bit = 0
    };

    enum ADC_Modes {
        NormalMode = 0,
        SelfCalib = 1,
        ZeroScaleSysCalib = 2,
        FullScaleSysCalib = 3,
        SysOffsetCalib = 4,
        BackgroundCalib = 5,
        ZeroScaleSelfCalib = 6,
        FullScaleSelfCalib = 7
    };
    
    enum Control_State {
        OFF = 0,
        ON  = 1
    };

    enum Polarity {
        bipolar = 0,
        unipolar = 1
    };


    struct InitTypeDef_t {
        uint8_t CS_pin_nr, DRDY_pin_nr, RESET_pin_nr, STANDBY_pin_nr, BUFFER_pin_nr;
    };

    ADC_Channels actual_channel;
    DataLength dataLen;

    /**
      * @brief    Sets ADC channel configuration.
      * @param    channel: determines ADC's channel configuration.
      * @retval Returns data from 1 byte Communication Register.
      */
    uint8_t changeChannel(ADC_Channels channel);

    /**
      * @brief    Checks a status of A/D data conversion polling DRDY pin.
      * @param    None
      * @retval Returns information whether data is available (true/false).
      */
    bool data_available(void);

    /**
      * @brief    Waits for end of A/D conversion.
      * @param  None
      * @retval None
      */
    void waitForDRDY(void);

    /**
      * @brief Resets device by asserting low-state on /RESET pin. After a while device is set back to normal, active mode.
      * @param  None
      * @retval None
      */
    void reset(void);

    /**
      * @brief Initialize the device.
      * @param  InitStruct: definition of the pins the device is connected to.
      * @retval None
      */
    void init(AD7714_t::InitTypeDef_t InitStruct);

    /**
      * @brief Controls mode of the device: standby or active by asserting /STANDBY pin.
      * @param  status: ON -- device in active mode, OFF -- device in standby mode
      * @retval None
      */
    void power_mode(Control_State status);

    /**
      * @brief Controls input buffer of the device. Enabling buffer increases input impedance of analog inputs. Controlled by asserting state on BUFFER pin.
      * @param  buff_stat: OFF -- buffer turned off, ON -- buffer turned on
      * @retval None
      */
    void buffer(Control_State buff_stat);

    /**
      * @brief Writes data to Communication Register of the device. 
      * @param  reg: Address of the next register
      * @param    read: true -- set next operation for reading, false -- set next operation for writing  
      * @param    channel: choose channel of analog input
      * @retval None
      */
    void writeToCommReg(ADC_Registers reg, bool read);

    /**
      * @brief Reads latest sampled and converted analog data according to previous settings.
      * @param None
      * @retval Raw data from A/D conversion.
      */
    uint32_t read_data(void);

    /**
      * @brief Writes data to Mode Register of the device. 
      * @param  mode: Determines mode of the device operation.
      * @param    gain: Sets gain applied on currently set channel.
      * @retval None
      */
    void writeToModeReg(ADC_Modes mode, ADC_Gain gain);

    /**
      * @brief Controls polarity, filters settings and resolution of A/D conversion.
      * @param  set_polarity: unipolar -- the device works in unipolar mode, bipolar -- bipolar mode.
      * @param    data_length: sets length of data in Data Register (16/24 bits).
      * @param    filter: sets filtering properties, value in range 19-4000, f_noth = fclk/128/filter
      * @retval None
      */
    void setFilter(Polarity set_polarity, DataLength data_length, uint16_t filter);

    AD7714_t();
    explicit AD7714_t(AD7714_t::InitTypeDef_t InitStruct);

 private:
    GPIOPin_t DRDY_pin, RESET_pin, STANDBY_pin, BUFFER_pin;
};

#endif  // DEVICES_AD7714_H_
