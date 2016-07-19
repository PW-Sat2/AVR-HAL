#ifndef HAL_PERIPH_SPI_H_
#define HAL_PERIPH_SPI_H_

#include <avr/io.h>
#include "mcu/mcu.h"
#include "DigitalIO.h"

namespace hal {

class SPI {
 public:
	enum SPI_Polarity {
		SPI_idle_low = 0, SPI_idle_high = 1
	};

	enum SPI_Phase {
		SPI_leading_sample = 0, SPI_trailing_sample = 1
	};

	enum SPI_DataOrder {
		SPI_MSB_First = 0, SPI_LSB_First = 1
	};

	enum SPI_Clock_Divisor {
		SPI_Clk_Div_4 = 0,
		SPI_Clk_Div_16 = 1,
		SPI_Clk_Div_64 = 2,
		SPI_Clk_Div_128 = 3,
	};

	struct InitTypeDef_t {
		SPI_Polarity polarity;
		SPI_Phase phase;
		SPI_DataOrder data_order;
		SPI_Clock_Divisor clk_divisor;
	};

	static void init(const SPI_Polarity polarity, const SPI_Phase phase, const SPI_DataOrder data_order, const SPI_Clock_Divisor clock_divisor) {
		pin_mosi.init(DigitalIO::OUTPUT);
		pin_sck.init(DigitalIO::OUTPUT);
		pin_ss.init(DigitalIO::INPUT_PULLUP);

		SPCR = (1 << SPE) | (1 << MSTR) | (clock_divisor)
				| (phase << CPHA) | (polarity << CPOL)
				| (data_order << DORD);
	}

	static uint8_t shift(const uint8_t data) {
		SPDR = data;
		while (!(SPSR & (1 << SPIF))) {
		}
		return SPDR;
	}

 private:
	const static DigitalIO pin_mosi, pin_sck, pin_ss;
};

constexpr DigitalIO SPI::pin_sck(mcu::pin_sck);
constexpr DigitalIO SPI::pin_mosi(mcu::pin_mosi);
constexpr DigitalIO SPI::pin_ss(mcu::pin_ss);


class SPI_Device {
private:
	const DigitalIO pin_cs;

public:
	constexpr explicit SPI_Device(const DigitalIO::Pin pin_cs) : pin_cs(pin_cs) {
	}

	void init() const {
		this->pin_cs.init(DigitalIO::OUTPUT);
		this->disable();
	}

	void enable(void) const {
		this->pin_cs.reset();
	}

	void disable(void) const {
		this->pin_cs.set();
	}

	uint8_t shift(const uint8_t data) const {
		return SPI::shift(data);
	}

	uint8_t data_transfer(const uint8_t data) const {
		this->enable();
		uint8_t x = SPI::shift(data);
		this->disable();
		return x;
	}

	void data_transfer(uint8_t * in_data, uint8_t * out_data, uint8_t len) const {
		this->enable();
		uint8_t tmp;
		while (len--) {
			tmp = SPI::shift(*in_data);
			(*out_data) = tmp;
			in_data++;
			out_data++;
		}
		this->disable();
	}
};

}

#endif /* HAL_PERIPH_SPI_H_ */
