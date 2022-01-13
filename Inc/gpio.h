/*
 * gpio.h
 *
 *  Created on: Jan 12, 2022
 *      Author: khorton
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define INPUT      0
#define OUTPUT     1
#define ALT        2
#define ANALOG     3

#define GPIOA_BASE 0x40020000
#define GPIOA_MODE GPIOA_BASE
#define GPIOA_ODR  GPIOA_MODE + 0x14
#define GPIOA_AFLR GPIOA_BASE + 0x20
#define GPIOA_AFHR GPIOA_BASE + 0x24

#define GPIOD_BASE 0x40020C00
#define GPIOD_MODE GPIOD_BASE
#define GPIOD_ODR  GPIOD_BASE + 0x14


namespace Gpio {
	void config_mode(uint32_t mode_addr, uint8_t pin, uint8_t mode);
	void toggle_pin(uint32_t odr_addr, uint8_t pin);
}


#endif /* GPIO_H_ */
