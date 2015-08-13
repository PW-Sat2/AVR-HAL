/*
* @brief A driver for Analog Devices ADG709, 4-to-1 differential multiplexer.
* @author Grzegorz Gajoch
* @author Micha� Gumiela
* @date 2015-07
*/
#ifndef DEVICES_ADG709_H_
#define DEVICES_ADG709_H_

#include "GPIO.h"

/*
 * @class ADG709_t
 * @brief Class is used to provide user-friendly solutions for mux handling.
 * @details Class offers methods for selecting input of the mux, as well as disabling/enabling the device. 
 */

class ADG709_t {
 private:
    GPIOPin_t A0, A1, EN;

 public:
     /*
     * @struct InitTypeDef_t
     * @brief Description of hardware connection of controlling lines of the mux.
     * @details Contains numbers of mcu leads connected to A0, A1 and EN pins of the mux.
     */
    struct InitTypeDef_t {
        uint8_t pin_A0, pin_A1, pin_EN;
    };
    ADG709_t();
    explicit ADG709_t(const InitTypeDef_t & InitStruct);

    /*
     * @brief Initialization of the device.
     * @param InitStruct: Contains all information needed for device initialization.
     * @retval None
     */
    void init(const InitTypeDef_t & InitStruct);

    /*
     * @brief Activate the device.
     * @param None
     * @retval None
     */
    void enable();

    /*
     * @brief Deactivate the device.
     * @param None
     * @retval None
     */
    void disable();

    /*
     * @brief Select demanded input.
     * @detailed Enable/disable methods are higher in hierarchy.
     * @param channel: Determines a number of channel to be chosen. Range 0-3.
     * @retval None
     */
    void select(const uint8_t channel);
};


#endif  // DEVICES_ADG709_H_
