#include "stm32f4xx.h"




int main(void){
	uint32_t ii;
// Initialize GPIO Port for LEDs
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;// Enable GPIOD clock 
GPIOD->MODER |= GPIO_MODER_MODER12_0;
GPIOD->MODER |= GPIO_MODER_MODER14_0;
//Ex.1
	for(;;){
		GPIOD->BSRR =1<<12;//Turn on the green light
		for (ii=0;ii<52000000;ii++){}
		GPIOD->BSRR =1<<(12+16);
		GPIOD->BSRR =1<<14;//Turn on the orange light
		for (ii=0;ii<52000000;ii++){}
		GPIOD->BSRR =1<<30;//Turn on the orange off	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
};

