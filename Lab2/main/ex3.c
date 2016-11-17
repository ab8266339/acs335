#include "stm32f4xx.h"




int main(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN; 		//Enable GPIOS
	GPIOD->MODER |= GPIO_MODER_MODER12_0;// GPIOD pin 12 output-green LED
	//Initialize Timer 2
	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;			//Enable Timer 2 of APB1
	TIM2->CR1 = TIM2->CR1 & ~0x00000016;		//Set TIM2_CR1 as inverse of 0x16 which is 10110 in BIN
	TIM2->CR1  = 0<<3;											//Set 3rd bit of CR1 as 1 to turn off auto repeat
	TIM2->PSC = 8400-1;											//The value of prescalar provided on sheet
	TIM2->ARR =1905-1;											//Calculated ARR value to generate 1sec delay
	TIM2->EGR = 1;													//Reset TIM2 to initial value
for(;;){																	//for loop to make code runing repeatedly			
	
	GPIOD->BSRR = 1<<12;										//Turn on Green LED
	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
	GPIOD->BSRR = 1<<(12+16);								//Turn off Green LED
	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
	
	}
}

