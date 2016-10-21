#include "stm32f4xx.h"





//EX,1
//int main(void){
//	uint32_t ii;// define a counter 
//// Initialize GPIO Port for LEDs
//RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// Enable GPIOD clock 
//GPIOD->MODER |= GPIO_MODER_MODER12_0;		// Enable Green LED
//GPIOD->MODER |= GPIO_MODER_MODER14_0;		// Enalbe Red LED
////Ex.1 of Assessed Lab
//	for(;;){
//		GPIOD->BSRR =1<<12;									//Turn on the green light
//		for (ii=0;ii<5200000;ii++){}				//Use for loop to generate 2s delay of frequency 26MHZ
//		GPIOD->BSRR =1<<(12+16);						//Turn off the green light
//		GPIOD->BSRR =1<<14;									//Turn on the red light
//		for (ii=0;ii<5200000;ii++){}				//Use for loop to generate 2s delay of frequency 26MHZ
//		GPIOD->BSRR =1<<30;									//Turn on the red off	
//	}
//	

//	
//}


//EX.2
//#include "stm32f4xx.h"




//int main(void){
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;			//Enable Timer 2 of APB1
//	GPIOD->MODER |= GPIO_MODER_MODER12_0;		// GPIOD pin 12 output-green LED
//	//Initialize Timer 2
//	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;			//Enable Timer 2 of APB1
//	TIM2->CR1 = TIM2->CR1 & ~0x00000016;		//Set TIM2_CR1 as inverse of 0x16 which is 10110 in BIN
//	TIM2->CR1  = 1<<3;											//Set 3rd bit of CR1 as 1 to turn off auto repeat
//	TIM2->PSC = 8400-1;											//The value of prescalar provided on sheet
//	TIM2->ARR =1905-1;											//Calculated ARR value to generate 1sec delay
//	TIM2->EGR = 1;													//Reset TIM2 to initial value
//for(;;){
//	
//	GPIOD->BSRR = 1<<12;										//Turn on Green LED
//	TIM2->CR1 |= TIM_CR1_CEN;								//Turn on timer
//	//TIM2->CR1 = 1<<0;											//Another way to turn on the timer
//	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
//	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
//	GPIOD->BSRR = 1<<(12+16);								//Turn off Green LED
//	TIM2->CR1 |= TIM_CR1_CEN;								//Turn off timer
//	//TIM2->CR1 = 0<<0;											//Another way to turn off the timer
//	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
//	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
//	
//	}
//}



//EX.3
//#include "stm32f4xx.h"




//int main(void){
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN; 		//Enable GPIOS
//	GPIOD->MODER |= GPIO_MODER_MODER12_0;// GPIOD pin 12 output-green LED
//	//Initialize Timer 2
//	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;			//Enable Timer 2 of APB1
//	TIM2->CR1 = TIM2->CR1 & ~0x00000016;		//Set TIM2_CR1 as inverse of 0x16 which is 10110 in BIN
//	TIM2->CR1  = 0<<3;											//Set 3rd bit of CR1 as 1 to turn on auto repeat
//	TIM2->PSC = 8400-1;											//The value of prescalar provided on sheet
//	TIM2->ARR =1905-1;											//Calculated ARR value to generate 1sec delay
//	TIM2->EGR = 1;													//Reset TIM2 to initial value
//for(;;){																	//for loop to make code runing repeatedly			
//	
//	GPIOD->BSRR = 1<<12;										//Turn on Green LED
//	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
//	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
//	GPIOD->BSRR = 1<<(12+16);								//Turn off Green LED
//	while((TIM2->SR&0x0001)!=1){}; 					//1 sec delay caused by while loop, the time was defined by ARR and PSC
//	TIM2->SR  &= ~TIM_SR_UIF;								//To change the statu of TIM2 Statue Register to update the interrupt flag
//	
//	}
//}



//EX.4
//#include "stm32f4xx.h"




//int main(void){
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;		//Enable GPIOD ports
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;		//Enable GPIOA ports
//	GPIOA->MODER |= 0; // GPIOA pin 0 USER PUSHBUTTON
//	GPIOD->MODER |= GPIO_MODER_MODER12_0; //GPIOD pin 12 Green LED
//	for(;;){
//	if ((GPIOA->IDR & 0x0001)==1){				//the if switch to determine whether the button has been pushed

//		
//		GPIOD ->BSRR =1<<12;								//turn on the green LED
//	}
//	else {
//		GPIOD->BSRR =1<<(12+16);						//Turn off the green LED
//	}
//	
//}
//}






//EX.5
//int main(void){
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIODEN;//Enable GPIOD ports
//	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;//Enable GPIOA ports
//	GPIOA->MODER |= 0x0000; // GPIOA pin 0 USER PUSHBUTTON
//	GPIOD->MODER |= GPIO_MODER_MODER12_0; //GPIOD pin 12 Green LED
//	GPIOD->MODER |= GPIO_MODER_MODER14_0;//GPIOD pin 14 Red LED
//	RCC-> APB1ENR |=RCC_APB1ENR_TIM2EN;	//Enable Timer 2
//	TIM2->CR1 = TIM2->CR1 & ~0x00000016; //Set TIM2_CR1 as inverse of 0x16 which is 10110 in BIN
//	TIM2->CR1  = 1<<3; 		//Enable auto reload
//	TIM2->PSC = 8400-1;		//provided psc value
//	TIM2->ARR =923;				//calculated ARR value for 0.5s
//	TIM2->EGR = 1;				//Reset timer
//	TIM2->CR1 = 1<<0;			//Start timer
//	
//	for(;;){

//	
//		if ((GPIOA->IDR & 0x0001)==0){  			//when the button was not pressed
//		GPIOD->BSRR =1<<(12+16);							//Keep the green led off
//		GPIOD->BSRR =1<<14;										//blink the red led
//		while(((TIM2->SR&0x0001)!=1)&((GPIOA->IDR & 0x0001)==0)){}; 		//while loop makes delay of 0.5s or whlie the button was not pressed 
//		TIM2->SR  &= ~TIM_SR_UIF;   //To change the statu of TIM2 Statue Register to update the interrupt flag
//		GPIOD->BSRR =1<<(14+16);		//Turn off the light after 0.5s
//		while(((TIM2->SR&0x0001)!=1)&((GPIOA->IDR & 0x0001)==0)){};//while loop make delay of 0.5s or whlie the button was not pressed 
//		TIM2->SR  &= ~TIM_SR_UIF;	 //To change the statu of TIM2 Statue Register to update the interrupt flag
//	}
//	else if ((GPIOA->IDR & 0x0001)==1){  //when the button was pressed
//		
//		GPIOD ->BSRR =1<<12;   //turn on the green led
//		GPIOD ->BSRR =1<<(14+16); // turn off the red led
//	}
//	
//		
//}
//}