#ifndef HAL_AVR_SPI_H_
#define HAL_AVR_SPI_H_

#include <stdint.h>
#include "GPIO.h"

/*
 * @struct SPIPinDescr_t
 * @brief SPI pin description.
 * @details Contains numbers of MOSI, MISO, SCK and SS pin corresponding to particular MCU, in particular package.
 */
struct SPIPinDescr_t {
    uint8_t pin_mosi, pin_miso, pin_sck, pin_ss;
};

/*
 * @class SPI_t
 * @brief Class is used to provide user-friendly SPI handling.
 * @details Class offers methods for pin initialization and shifting data via SPI bus.
 */
class SPI_t {
 private:
    /*
     * @var spi_descr
     * @brief A description of the SPI device.
     * @details The variable stores the pin description assigned during initialization for future use by other methods.
     */
    GPIOPin_t pin_mosi, pin_miso, pin_sck, pin_ss;

 public:
    /*
     * @enum SPI_Polarity
     * @brief Type intended for specifying idle state of SCK line.
     */
    enum SPI_Polarity {
        SPI_idle_low = 0,
        SPI_idle_high = 1
    };

    /*
     * @enum SPI_Phase
     * @brief Type intended for specifying sampling edge during SPI transfer.
     */
    enum SPI_Phase {
        SPI_leading_sample = 0,
        SPI_trailing_sample = 1
    };

    /*
     * @enum SPI_DataOrder
     * @brief Type intended for specifying data order when shifting data.
     */
    enum SPI_DataOrder {
        SPI_MSB_First = 0,
        SPI_LSB_First = 1
    };

    /*
     * @enum SPI_Clock_Divisor
     * @brief Type intended for specifying clock divisor to provide SCK base time.
     */
    enum SPI_Clock_Divisor {
        SPI_Clk_Div_4 = 0,
        SPI_Clk_Div_16 = 1,
        SPI_Clk_Div_64 = 2,
        SPI_Clk_Div_128 = 3,
    };

    /*
     * @struct InitTypeDef_t
     * @brief Struct contains members describing all necessary data for SPI initialization.
     */
    struct InitTypeDef_t {
        SPI_Polarity polarity;
        SPI_Phase phase;
        SPI_DataOrder data_order;
        SPI_Clock_Divisor clk_divisor;
    };

    SPI_t();

    /*
     * @brief Initialization of the SPI.
     * @param InitStruct: Contains all information needed for SPI initialization.
     * @retval None
     */
    void init(SPI_t::InitTypeDef_t InitStruct);

    /*
     * @brief Shift data via SPI.
     * @param data: Contains 8-bit data to be shifted out of MCU.
     * @retval 8-bit data gathered during the transfer.
     */
    uint8_t shift(uint8_t data);
};

extern SPI_t SPI;

/*
 * @class SPI_Device_t
 * @brief Class is used to provide user-friendly SPI device handling.
 * @details Class offers methods for accessing external device with provided function for selecting slave.
 * @details SPI has to be initialised before accessing this class.
 */
class SPI_Device_t {
 private:
    /*
     * @var pin_cs
     * @brief Pin connected to external device pin slave select.
     */
    GPIOPin_t pin_cs;

 public:
    SPI_Device_t();
    explicit SPI_Device_t(uint8_t cs_pin);

    /*
     * @brief Initialization of the device.
     * @param cs_pin: pin number selecting slave device
     * @retval None
     */
    void init(uint8_t cs_pin);

    /*
     * @brief Enabling slave. Writes logic 0 to SS pin.
     * @param None
     * @retval None
     */
    void enable(void);

    /*
     * @brief Disabling slave. Writes logic 1 to SS pin.
     * @param None
     * @retval None
     */
    void disable(void);

    /*
     * @brief Shifting data via SPI, without changing state of SS pin.
     * @param None
     * @retval None
     */
    uint8_t shift(uint8_t data);

    /*
     * @brief Transferring 1-byte data via SPI bus. Function enables slave and after transfer disables it.
     * @param data: data to be shifted out
     * @retval response from device
     */
    uint8_t data_transfer(uint8_t data);

    /*
     * @brief Transferring n-byte data via SPI bus. Function enables slave and after transfer disables it.
     * @param in_data: data to be shifted out
     * @param out_data: response from device
     * @retval None
     */
    void data_transfer(uint8_t * in_data, uint8_t * out_data, uint8_t len);
};

#endif  // HAL_AVR_SPI_H_
