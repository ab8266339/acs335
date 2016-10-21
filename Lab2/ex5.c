#include "stm32f4xx.h"




int main(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;//Enable GPIOD ports
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;//Enable GPIOA ports
	GPIOA->MODER |= 0x0000; // GPIOA pin 0 USER PUSHBUTTON
	GPIOD->MODER |= GPIO_MODER_MODER12_0; //GPIOD pin 12 Green LED
	GPIOD->MODER |= GPIO_MODER_MODER14_0;//GPIOD pin 14 Red LED
	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;	//Enable Timer 2
	TIM2->CR1 = TIM2->CR1 & ~0x00000016; //Set TIM2_CR1 as inverse of 0x16 which is 10110 in BIN
	TIM2->CR1  = 1<<3; 		//Enable auto reload
	TIM2->PSC = 8400-1;		//provided psc value
	TIM2->ARR =923;				//calculated ARR value for 0.5s
	TIM2->EGR = 1;				//Reset timer
	TIM2->CR1 = 1<<0;			//Start timer
	
	for(;;){

	
		if ((GPIOA->IDR & 0x0001)==0){  			//when the button was not pressed
		GPIOD->BSRR =1<<(12+16);							//Keep the green led off
		GPIOD->BSRR =1<<14;										//blink the red led
		while(((TIM2->SR&0x0001)!=1)&((GPIOA->IDR & 0x0001)==0)){}; 		//while loop makes delay of 0.5s or whlie the button was not pressed 
		TIM2->SR  &= ~TIM_SR_UIF;   //To change the statu of TIM2 Statue Register to update the interrupt flag
		GPIOD->BSRR =1<<(14+16);		//Turn off the light after 0.5s
		while(((TIM2->SR&0x0001)!=1)&((GPIOA->IDR & 0x0001)==0)){};//while loop make delay of 0.5s or whlie the button was not pressed 
		TIM2->SR  &= ~TIM_SR_UIF;	 //To change the statu of TIM2 Statue Register to update the interrupt flag
	}
	else if ((GPIOA->IDR & 0x0001)==1){  //when the button was pressed
		
		GPIOD ->BSRR =1<<12;   //turn on the green led
		GPIOD ->BSRR =1<<(14+16); // turn off the red led
	}
	
		
}
}