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

#define RCC_GPIOA  0
#define RCC_GPIOB  1
#define RCC_GPIOC  2
#define RCC_GPIOD  3
#define RCC_GPIOE  4



namespace Rcc {
	typedef struct AHB1ENR {
	private:
		uint32_t GPIOA_EN    :1;
		uint32_t GPIOB_EN    :1;
		uint32_t GPIOC_EN    :1;
		uint32_t GPIOD_EN    :1;
		uint32_t GPIOE_EN    :1;
		uint32_t GPIOF_EN    :1;
		uint32_t GPIOG_EN    :1;
		uint32_t GPIOH_EN    :1;
		uint32_t GPIOI_EN    :1;
		uint32_t GPIOJ_EN    :1;
		uint32_t GPIOK_EN    :1;
		//TODO finish this register
		uint32_t RES         :21;
	public:
		void start_clock_a(void);
		void start_clock_d(void);
	}__attribute((packed))AHB1ENR_t;

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
