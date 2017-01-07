#ifndef HAL_BOARDS_SUNS_EM3_SUNS_EM3_H_
#define HAL_BOARDS_SUNS_EM3_SUNS_EM3_H_

#include "periph/DigitalIO.h"
#include "periph/Serial.h"

#ifdef DEBUG
#define printf printf
#else
#define printf(text) ((void)0)
#endif

namespace hal {
namespace bsp {
static constexpr InternalADC::Input TEMP_BOARD = InternalADC::Input::ADC4;
static constexpr InternalADC::Input RTD_AIN_A = InternalADC::Input::ADC3;
static constexpr InternalADC::Input RTD_AIN_B = InternalADC::Input::ADC2;
static constexpr InternalADC::Input RTD_AIN_C = InternalADC::Input::ADC1;
static constexpr InternalADC::Input RTD_AIN_D = InternalADC::Input::ADC0;

namespace pins {
static constexpr DigitalIO::Pin SDA_A1 = 21;
static constexpr DigitalIO::Pin SDA_B1 = 22;
static constexpr DigitalIO::Pin SDA_C1 = 23;
static constexpr DigitalIO::Pin SDA_D1 = 24;
static constexpr DigitalIO::Pin SCL_1 = 25;

static constexpr DigitalIO::Pin SDA_A2 = 15;
static constexpr DigitalIO::Pin SDA_B2 = 13;
static constexpr DigitalIO::Pin SDA_C2 = 14;
static constexpr DigitalIO::Pin SDA_D2 = 12;
static constexpr DigitalIO::Pin SCL_2 = 16;

static constexpr DigitalIO::Pin SDA_A3 = 40;
static constexpr DigitalIO::Pin SDA_B3 = 41;
static constexpr DigitalIO::Pin SDA_C3 = 42;
static constexpr DigitalIO::Pin SDA_D3 = 44;
static constexpr DigitalIO::Pin SCL_3 = 43;

}  // namespace pins
}  // namespace bsp
}  // namespace hal
#endif  // HAL_BOARDS_SUNS_EM3_SUNS_EM3_H_
