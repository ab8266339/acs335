#include "stm32f4xx.h"






int main(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;		//Enable GPIOD ports
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;		//Enable GPIOA ports
	GPIOA->MODER |= 0; // GPIOA pin 0 USER PUSHBUTTON
	GPIOD->MODER |= GPIO_MODER_MODER12_0; //GPIOD pin 12 Green LED
	for(;;){
	if ((GPIOA->IDR & 0x0001)==1){				//the if switch to determine whether the button has been pushed

		
		GPIOD ->BSRR =1<<12;								//turn on the green LED
	}
	else {
		GPIOD->BSRR =1<<(12+16);						//Turn off the green LED
	}
	
}
}




