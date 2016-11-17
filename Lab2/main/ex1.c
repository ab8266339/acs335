#include "stm32f4xx.h"






int main(void){
	uint32_t ii;// define a counter 
// Initialize GPIO Port for LEDs
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// Enable GPIOD clock 
GPIOD->MODER |= GPIO_MODER_MODER12_0;		// Enable Green LED
GPIOD->MODER |= GPIO_MODER_MODER14_0;		// Enalbe Red LED
//Ex.1 of Assessed Lab
	for(;;){
		GPIOD->BSRR =1<<12;									//Turn on the green light
		for (ii=0;ii<5200000;ii++){}				//Use for loop to generate 2s delay of frequency 26MHZ
		GPIOD->BSRR =1<<(12+16);						//Turn off the green light
		GPIOD->BSRR =1<<14;									//Turn on the red light
		for (ii=0;ii<5200000;ii++){}				//Use for loop to generate 2s delay of frequency 26MHZ
		GPIOD->BSRR =1<<30;									//Turn on the red off	
	}
	

	
}

