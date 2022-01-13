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
	void AHB1ENR_t::start_clock_a(void)
	{
		this->GPIOA_EN = 0x01;
	}

	void AHB1ENR_t::start_clock_d()
	{
		this->GPIOD_EN = 0x01;
	}
}
