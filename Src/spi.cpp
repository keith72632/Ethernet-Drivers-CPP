/*
 * spi.cpp
 *
 *  Created on: Jan 11, 2022
 *      Author: khorton
 */

#include "spi.h"

namespace Spi {
	void SPI_t::spi_config()
	{
		//CPHA = 1, CPOL = 1, Enable Master Mode, BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz
		this->CR1 |= ( 1 << CPHA ) | ( 1 << CPOL ) | ( 1 << MSTR ) | ( 3 << BR );
		//Frame format . 0 = Most Significant Bit First, 1 = Least Significant Bit First
		this->CR1 &= ~( 1 << LSB );
		//Software slave management
		this->CR1 |= ( 1 << SSI ) | ( 1 << SSM );
		//Full duplex, 8 bit data
		this->CR1 &= ~(1 << RX_ONLY) & ~( 1 << DFF );
	}

	void SPI_t::transmit(uint8_t *data, uint32_t size)
	{
		/************** STEPS TO FOLLOW *****************
		1. Wait for the TXE bit to set in the Status Register
		2. Write the data to the Data Register
		3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
		4. Clear the Overrun flag by reading DR and SR
		************************************************/

		uint32_t i = 0;
		while(i < size)
		{
			while(!((this->SR) & (1 << TXE))){}; //wait for the TXE bit to be set, this will indicate buffer is empty
			this->DR = data[i];
			i++;
		}
		/*During discontinuous communications, there is a 2 APB clock period delay between the
		write operation to the SPI_DR register and BSY bit setting. As a consequence it is
		mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
		data.
		*/
		while(!((this->SR)&(1<<TXE))){}; //Wait for TXE bit to be set, indicates buffer is empty
		while(((this->SR)&(1 << BSY))){}; //Wait for BSY to reset, indicates that SPI is not busy

		//clear the overrun flag by reading DR and SR
		uint8_t temp = this->DR;
		temp = this->SR;
	}
}


