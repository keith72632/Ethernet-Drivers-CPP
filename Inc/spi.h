/*
 * spi.h
 *
 *  Created on: Jan 11, 2022
 *      Author: khorton
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "rcc.h"
#include "gpio.h"

//CR1 Bitfield
#define CPHA       0
#define CPOL       1
#define MSTR       2
#define BR         3
#define SPE        6
#define LSB        7
#define SSI        8
#define SSM        9
#define RX_ONLY    10
#define DFF        11
#define CRC_NEXT   12
#define CRC_EN     13
#define BIDI_OE    14
#define BIDI_MODE  15

//Status Register Bitfield
#define RXNE       0
#define TXE        1
#define BSY        7

//spi1 address 0x40013000
namespace Spi{
	typedef struct spi {
	private:
		uint32_t CR1;
		uint32_t CR2;
		uint32_t SR;
		uint32_t DR;
		uint32_t CRCPR;
		uint32_t RXCRCR;
		uint32_t TXCRCR;
		uint32_t I2SCFGR;
		uint32_t I2SPR;
	public:
		void spi_config(uint32_t rcc_spi, uint32_t rcc_gpio);
		void transmit(uint8_t data, uint8_t size);
		void receive(uint8_t *data, uint8_t size);
		void pin_config(void);
		void toggle_ss(void);
		void pull_ss_high(void);
		void pull_ss_low(void);
	}__attribute__((packed))SPI_t;
}


#endif /* SPI_H_ */
