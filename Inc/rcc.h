/*
 * rcc.h
 *
 *  Created on: Jan 11, 2022
 *      Author: khorton
 */

#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>

#define ENABLE     0x01
#define DISABLE    0x00

namespace Rcc {
	typedef struct APB2ENR {
	private:
		uint32_t TIM1EN      :1;
		uint32_t TIM8EN      :1;
		uint32_t RES1        :2;
		uint32_t USART1EN    :1;
		uint32_t USART6EN    :1;
		uint32_t RES2        :2;
		uint32_t ADC1EN      :1;
		uint32_t ADC2EN      :1;
		uint32_t ADC3EN      :1;
		uint32_t SDIOEN      :1;
		uint32_t SPI1EN      :1;
		uint32_t RES3        :1;
		uint32_t SYSCFGEN    :1;
		uint32_t RES4        :1;
		uint32_t TIM9EN      :1;
		uint32_t TIM10EN     :1;
		uint32_t TIM11EN     :1;
		uint32_t RES5        :13;
	public:
		void start_spi1_clk(void);
	}__attribute__((packed))APB2ENR_t;
}


#endif /* RCC_H_ */
