/*
 * spi.cpp
 *
 *  Created on: Jan 11, 2022
 *      Author: khorton
 */

#include "spi.h"

namespace Spi {
	void SPI_t::spi_config(uint32_t rcc_spi, uint32_t rcc_gpio)
	{
		Rcc::APB2ENR_t *apb2 = (Rcc::APB2ENR_t*)rcc_spi;
		apb2->start_spi1_clk();

		Rcc::AHB1ENR_t *ahb1 = (Rcc::AHB1ENR_t*)rcc_gpio;
		ahb1->start_clock_a();
		ahb1->start_clock_d();

		this->pin_config();

		//CPHA = 1, CPOL = 1, Enable Master Mode, BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz
		this->CR1 |= ( 1 << MSTR ) | ( 2 << BR );
		//Frame format . 0 = Most Significant Bit First, 1 = Least Significant Bit First
		this->CR1 &= ~( 1 << LSB );
		//Software slave management
		this->CR1 |= ( 1 << SSI ) | ( 1 << SSM );
		//Full duplex, 8 bit data
		this->CR1 &= ~(1 << RX_ONLY) & ~( 1 << DFF );
	}

	void SPI_t::transmit(uint8_t data, uint8_t size)
	{
//		uint32_t *dr = (uint32_t*)0x4001300c;
		/************** STEPS TO FOLLOW *****************
		1. Wait for the TXE bit to set in the Status Register
		2. Write the data to the Data Register
		3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
		4. Clear the Overrun flag by reading DR and SR
		************************************************/

		while(!(( this->SR ) & ( 1 << 1 ))){}; //wait for the TXE bit to be set, this will indicate buffer is empty
		this->DR = data;
		/*During discontinuous communications, there is a 2 APB clock period delay between the
		write operation to the SPI_DR register and BSY bit setting. As a consequence it is
		mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
		data.
		*/
	    while (this->SR & 0x80) {};      /* wait for transmission done */
		while((( this->SR ) & ( 1 << 7 ))){}; //Wait for BSY to reset, indicates that SPI is not busy

		//clear the overrun flag by reading DR and SR
		uint8_t temp = this->DR;
		temp = this->SR;
	}

	void SPI_t::receive(uint8_t *data, uint8_t size)
	{
		/************** STEPS TO FOLLOW *****************
		1. Wait for the BSY bit to reset in Status Register
		2. Send some Dummy data before reading the DATA
		3. Wait for the RXNE bit to Set in the status Register
		4. Read data from Data Register
		************************************************/

		while(size)
		{
			//1.
			while((( this->SR ) & ( 1 << BSY ))){};
			//2.
			this->DR = 0x00;
			//3.
			while((( this->SR ) & ( 1 << 0 ))){};
			//4.
			*data++ = this->DR;
			size--;
		}

	}

	void SPI_t::pin_config(void)
	{
		uint32_t *gpioa_mode = (uint32_t*)0x40020000;
		uint32_t *gpiod_mode = (uint32_t*)0x40020C00;

		*gpioa_mode |= (2 << 10) | (2 << 12) | (2 << 14);
		*gpiod_mode |= (1 << 14);
	}

	void SPI_t::toggle_ss(void)
	{
		uint32_t *odr = (uint32_t*)0x40020c14;
		*odr ^= ( 1 << 7 );
	}

	void SPI_t::pull_ss_high()
	{
		uint32_t *odr = (uint32_t*)0x40020c14;
		*odr |= (1 << 7);
	}

	void SPI_t::pull_ss_low()
	{
		uint32_t *odr = (uint32_t*)0x40020c14;
		*odr &= ~(1 << 7);
	}
}


