#include "SPI.h"


int main() {
	hal::SPI::init(hal::SPI::SPI_Polarity::SPI_idle_high,
			  hal::SPI::SPI_leading_sample,
			  hal::SPI::SPI_MSB_First,
			  hal::SPI::SPI_Clk_Div_128);

	constexpr hal::SPI_Device dev1(1);
	dev1.init();

	dev1.shift(0xFF);

	uint8_t data[] = {1, 2, 3};
	dev1.data_transfer(data, data, 3);
}
