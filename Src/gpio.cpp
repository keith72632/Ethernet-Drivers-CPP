/*
 * gpio.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: khorton
 */


#include "gpio.h"

namespace Gpio {
	void config_mode(uint32_t mode_addr, uint8_t pin, uint8_t mode)
	{
		uint32_t *temp = (uint32_t*)mode_addr;
		*temp |= ((pin * 2) << mode);
	}

	void toggle_pin(uint32_t odr_addr, uint8_t pin)
	{
		uint32_t *temp = (uint32_t*)odr_addr;
		*temp ^= (1 << pin);
	}
}
