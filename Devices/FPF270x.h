/*
* @brief A driver for Fairchild Semiconductor FPF2700/FPF2701/FPF2702 -- AccuPower(TM) 0.4 ~ 2 A Adjustable Over-Current Protection Load Switches
* @author Grzegorz Gajoch
* @date 2015-07
*/
#ifndef DEVICES_FPF270X_H_
#define DEVICES_FPF270X_H_

#include "GPIO.h"

/*
 * @class FPF270x_t
 * @brief Class is used to provide user-friendly solutions to communicate with FPF270x over-current protection switch.
 * @details Class offers methods for enabling/disabling device, checking for overload and powergood flags.
 */
class FPF270x_t {
 private:
    GPIOPin_t pin_on, pin_flag, pin_pgood;

 public:
    /*
     * @struct InitTypeDef_t
     * @brief Description of hardware connection of controlling lines of the switch.
     * @details Contains numbers of mcu leads connected to enable, flag and powergood pins.
     */
    struct InitTypeDef_t {
        uint8_t pin_on, pin_flag, pin_pgood;
    };
    FPF270x_t();
    explicit FPF270x_t(const InitTypeDef_t & InitStruct);

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
    void on();

    /*
     * @brief Deactivate the device.
     * @param None
     * @retval None
     */
    void off();

    /*
     * @brief Checks for error signal from device.
     * @param None
     * @retval True means some sort of error have occured.
     */
    bool error_occured();

    /*
     * @brief Checks for power good flag.
     * @param None
     * @retval True means out voltage is withing limits.
     */
    bool powergood();
};

#endif  // DEVICES_FPF270X_H_
