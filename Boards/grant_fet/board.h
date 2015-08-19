/*
 * board.h
 *
 * Created: 2015-07-29 15:59:27
 *  Author: Micha³ Gumiela
 */ 

#ifndef BOARDS_GRANT_FET_BOARD_H_
#define BOARDS_GRANT_FET_BOARD_H_

#include "GPIO.h"
#include "ADG709.h"

/* LEDs */
const GPIOPin_t::InitTypeDef_t LED_BLUE = {58, GPIOPin_t::output};
const GPIOPin_t::InitTypeDef_t LED_YELLOW = {59, GPIOPin_t::output};
const GPIOPin_t::InitTypeDef_t LED_GREEN = {60, GPIOPin_t::output};
const GPIOPin_t::InitTypeDef_t LED_RED = {61, GPIOPin_t::output};

/* MOS MUX */
const ADG709_t::InitTypeDef_t MUX_MOS = {46, 44, 47};

/* PT1000 MUX */
const ADG709_t::InitTypeDef_t MUX_PT = {43, 45, 42};

#endif  //  BOARDS_GRANT_FET_BOARD_H_
