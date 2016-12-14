#include "stm32f4xx.h"

// Definition for the function to initialise the LED and button
void Initialise_LED_and_button(void){
// Initialize GPIO Port for LEDs
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable Port D clock 
	GPIOD->MODER |= GPIO_MODER_MODER12_0; // Port D.12 output -green LED
	GPIOD->MODER |= GPIO_MODER_MODER14_0; // Port D.14 output -red LED
	GPIOD->MODER |= GPIO_MODER_MODER13_0; // Port D.13 output -orange LED
	GPIOD->MODER |= GPIO_MODER_MODER15_0; // Port D.15 output -blue LED
//Initialize GPIO for push-button
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable Port A clock

	//init timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2 ->EGR = 1;
	TIM2 -> CR1 |= 1;
	TIM2->SR&= ~1; //Resets the flag
	TIM2 -> CR1 &= ~0x00000016;
	//TIM2 -> CR1 &= ~0x00000008;
	TIM2 -> PSC = 8400-1;
	TIM2 -> ARR = 250000-1;
	//init timer 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3 -> CR1 &= ~0x00000016;
	//TIM3 -> CR1 &= ~0x00000008;
	TIM3 -> PSC = 8400-1;
	TIM3 ->ARR = 50000-1;
	//init timer 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4 -> CR1 &= ~0x00000016;
	//TIM3 -> CR1 &= ~0x00000008;
	TIM4 -> PSC = 8400-1;
	TIM4 ->ARR = 150000-1;
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5 -> CR1 &= ~0x00000016;
	//TIM3 -> CR1 &= ~0x00000008;
	TIM5 -> PSC = 8400-1;
	TIM5 ->ARR = 150000-1;
}
// Definition for the function to blink the LED
void Blink_LED(uint8_t LED_state ){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<12; // Turn on the green LED
}
else{
	GPIOD->BSRR = 1<<(12+16); // Turn off the green LED
}
}
void Light(uint8_t LED_state ){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<12; // Turn on the green LED
}
else{
	GPIOD->BSRR = 1<<(12+16); // Turn off the green LED
}
}
// Definition for the function to blink the LED
void Red_LED(uint8_t LED_state){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<14; // Turn on the red LED
}
else{
GPIOD->BSRR = 1<<(14+16); // Turn off the red LED

}
}
void Green_LED(uint8_t LED_state){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<12; // Turn on the red LED
}
else{
GPIOD->BSRR = 1<<(12+16); // Turn off the green LED

}
}
void Orange_LED(uint8_t LED_state){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<13; // Turn on the red LED
}
else{
GPIOD->BSRR = 1<<(13+16); // Turn off the red LED

}
}
void Blue_LED(uint8_t LED_state){
if(LED_state == 1){ // Checks to see if the request is to turn the LED on or off
GPIOD->BSRR = 1<<15; // Turn on the red LED
}
else{
GPIOD->BSRR = 1<<(15+16); // Turn off the red LED

}
}

