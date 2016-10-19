#include "stm32f4xx.h"




int main(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0;// GPIOD pin 12 output-green LED
	//Initialize Timer 2
	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;
	TIM2->CR1 &= ~0x00000016;
	TIM2->CR1  = 1<<3;
	TIM2->PSC = 8400-1;
	TIM2->ARR =1905-1;
	TIM2->EGR = 1<<0;
	
	



	GPIOD->BSRR = 1<<12;
	TIM2->CR1 |= TIM_CR1_CEN;
	while((TIM2->SR&0x0001)!=1){}; 
	TIM2->SR  &= ~TIM_SR_UIF;
	GPIOD->BSRR = 1<<(12+16);
	TIM2->CR1 |= TIM_CR1_CEN;
	while((TIM2->SR&0x0001)!=1){}; 
	TIM2->SR  &= ~TIM_SR_UIF;
	
}