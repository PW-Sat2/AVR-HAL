#ifndef HAL_BOARDS_RadFET_EM1_RadFET_EM1_H_
#define HAL_BOARDS_RadFET_EM1_RadFET_EM1_H_

#include "DigitalIO.h"
#include "SPI.h"
#include "SPISoftware.h"
#include "AD7714.h"
#include "ADG709.h"

namespace hal {
namespace bsp {
namespace pins {

static constexpr DigitalIO::Pin MUX_A0        = 44;
static constexpr DigitalIO::Pin MUX_A1        = 42;
static constexpr DigitalIO::Pin MUX_EN        = 43;

static constexpr DigitalIO::Pin LDO_PGOOD     = 13;
static constexpr DigitalIO::Pin LDO_EN        = 16;
static constexpr DigitalIO::Pin LDO_FAULT     = 25;

static constexpr DigitalIO::Pin AD7714_MOSI   = 2;
static constexpr DigitalIO::Pin AD7714_MISO   = 1;
static constexpr DigitalIO::Pin AD7714_SCK    = 3;
static constexpr DigitalIO::Pin AD7714_CS     = 14;
static constexpr DigitalIO::Pin AD7714_DRDY   = 15;

static constexpr DigitalIO::Pin PLD_INT       = 33;

static constexpr DigitalIO::Pin WATCHDOG_KICK = 34;

}  // namespace pins


using AD7714_spi = SPI::Software<pins::AD7714_MOSI,
                                 pins::AD7714_MISO,
                                 pins::AD7714_SCK,
                                 SPI::Polarity::idle_low,
                                 SPI::Phase::trailing_sample>;



constexpr DigitalIO analogLDOEnable(pins::LDO_EN);

constexpr ADG709 mux(pins::MUX_A0, pins::MUX_A1, pins::MUX_EN);
constexpr uint8_t mux_tmp  = 0;
constexpr uint8_t mux_mos1 = 2;
constexpr uint8_t mux_mos2 = 3;
constexpr uint8_t mux_mos3 = 1;


AD7714<AD7714_spi> AD7714_adc(pins::AD7714_CS, pins::AD7714_DRDY);

}  // namespace bsp
}  // namespace hal

#endif  // HAL_BOARDS_RadFET_EM1_RadFET_EM1_H_
