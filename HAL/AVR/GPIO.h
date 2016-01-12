/*
 * @brief Abstraction layer for General Purpose Input/Output (GPIO).
 * @author Grzegorz Gajoch 
 * @author Micha³ Gumiela
 * @date 2015-07
 */

#ifndef HAL_AVR_GPIO_H_
#define HAL_AVR_GPIO_H_

#include <stdint.h>


/*
 * @struct GPIOPinDescr_t
 * @brief GPIO pin description.
 * @details Contains adressed of DDR, PORT and PIN registers and number of pin corresponding to particular MCU, in particular package.
 */
struct GPIOPinDescr_t {
    volatile uint8_t *DDRx, *PORTx, *PINx;
    uint8_t pin;
};

/*
 * @class GPIOPin_t
 * @brief Class is used to provide user-friendly GPIO handling.
 * @details Class offers methods for pin initialization in input/input pull-up/output modes,
 * @details setting high state, resetting to low state or writing particular state.
 */
class GPIOPin_t {
 private:
    /*
     * @var pin_reg
     * @brief A description of the pin.
     * @details The variable stores the pin description assigned during initialization for future use by other methods.
     */
    GPIOPinDescr_t pin_reg;

 public:
    /*
     * @enum GPIO_Mode
     * @brief Type intended for specifying mode of GPIO operation.
     */
    enum  GPIO_Mode {
        input,
        output,
        input_pullup
    };

    /*
     * @struct InitTypeDef_t
     * @brief Struct contains members describing all necessary data for pin initialization.
     */
    struct InitTypeDef_t {
        uint8_t pin_nr;  /**< A physical pin number of particular MCU and package. */
        GPIO_Mode mode;  /**< Mode wherein the pin will be operating. */
    };

    GPIOPin_t();
    explicit GPIOPin_t(GPIOPin_t::InitTypeDef_t InitStruct);

    /*
     * @brief Initialization of the pin.
     * @param InitStruct: Contains all information needed for pin initialization i.e. pin number and mode of operation.
     * @retval None
     */
    void init(GPIOPin_t::InitTypeDef_t InitStruct);

    /*
     * @brief Writes high state to the pin.
     * @param None
     * @retval None
     */
    void set();

    /*
     * @brief Writes low state to the pin.
     * @param None
     * @retval None
     */    
    void reset();

    /*
     * @brief Writes either low or high state to the pin, depending on input value.
     * @param value: Determines state to be written to the pin.
     * @retval None
     */    
    void write(bool value);

    /*
     * @brief Reads state of the pin.
     * @param None
     * @retval State of the pin, i.e. either high or low.
     */    
    bool read(void);
    
    /*
     * @brief Changes mode (input/output/input_pullup) of the pin.
     * @param mode: Determines mode of the pin to be changed.
     * @retval None.
     */    
    void pinmode(GPIOPin_t::GPIO_Mode mode);
};


#endif  // HAL_AVR_GPIO_H_
