/*
 * rcc.cpp
 *
 *  Created on: Jan 11, 2022
 *      Author: khorton
 */




#include "rcc.h"

namespace Rcc {
	void APB2ENR_t::start_spi1_clk()
		{
			this->SPI1EN = ENABLE;
		}
}
