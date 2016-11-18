#include "stm32f4xx.h"

int main(){
	
SPI_HandleTypeDef SPI_Params; // Declares the structure handle for the parameters of SPI1
GPIO_InitTypeDef GPIOA_Params; // Declares the structure handle for the parameters of GPIOA
GPIO_InitTypeDef GPIOE_Params; // Declares the structure handle for the parameters of GPIOE
GPIO_InitTypeDef GPIOE_Params_I; // Declares the structure handle for the parameters of the interrupt pin on GPIOE
//uint16_t Z_Reg; //Declares the variable to store the z-axis MS 16-bits in
uint16_t X_Reg; //Declares the variable to store the x-axis MS 16-bits in
uint16_t Y_Reg; //Declares the variable to store the y-axis MS 16-bits in
uint8_t data_to_send[1]; //Declares an array to store the required LIS3DSH
//register address in. It has a single element since we will only be
//accessing a single address in each SPI transaction.
uint16_t data_size=1; //Declares a variable that specifies that only a
//single address is accessed in each transaction.
uint32_t data_timeout=1000; //Sets a maximum time to wait for the SPI
//transaction to complete in - this mean that our program won�t freeze if
//there is a problem with the SPI communication channel.
uint8_t CTRL_REG4; //Declares the variable to store the who_am_I register value in
// Read the value from the Who_am_I register of the LIS3DSH

	
// Code to initialise the SPI	
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enables the clock for SPI1
SPI_Params.Instance = SPI1; // Selects which SPI interface to use	
SPI_Params.Init.Mode = SPI_MODE_MASTER; // Sets the STM32F407 to act as the master
SPI_Params.Init.NSS = SPI_NSS_SOFT; // Sets the slave to be controlled by software
SPI_Params.Init.Direction = SPI_DIRECTION_2LINES; // Sets the SPI to fullduplex
SPI_Params.Init.DataSize = SPI_DATASIZE_8BIT; // Sets the data packet size to 8-bit
SPI_Params.Init.CLKPolarity = SPI_POLARITY_HIGH; // Sets the idle polarity for the clock line to high
SPI_Params.Init.CLKPhase = SPI_PHASE_2EDGE; // Sets the data line to change on the second transition of the clock line
SPI_Params.Init.FirstBit = SPI_FIRSTBIT_MSB; // Sets the transmission to MSB first
SPI_Params.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; // Sets the clock prescaler to divide the main APB2 clock (previously set to 84MHz) by 
//32 to give a SPI clock of 2.625MHz, which is less the maximum value of 10MHz for the SPI.
HAL_SPI_Init(&SPI_Params); // Configures the SPI using the specified parameters


// Code to initialise pins 5-7 of GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //Enable the clock for GPIOA
GPIOA_Params.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; // Selects pins5,6 and 7
GPIOA_Params.Alternate = GPIO_AF5_SPI1; //Selects alternate function 5 which corresponds to SPI1
GPIOA_Params.Mode = GPIO_MODE_AF_PP; //Selects alternate function push-pull mode
GPIOA_Params.Speed = GPIO_SPEED_FAST; //Selects fast speed
GPIOA_Params.Pull = GPIO_NOPULL; //Selects no pull-up or pull-down activation
HAL_GPIO_Init(GPIOA, &GPIOA_Params); // Sets GPIOA into the modes specified in GPIOA_Params


// Code to initialise pin 3 of GPIOE
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; //Enable the clock for GPIOE
GPIOE_Params.Pin = GPIO_PIN_3; // Selects pin 3
GPIOE_Params.Mode = GPIO_MODE_OUTPUT_PP; //Selects normal push-pull mode
GPIOE_Params.Speed = GPIO_SPEED_FAST; //Selects fast speed
GPIOE_Params.Pull = GPIO_PULLUP; //Selects pull-up activation
HAL_GPIO_Init(GPIOE, &GPIOE_Params); // Sets GPIOE into the modes specified in GPIOE_Params
GPIOE->BSRR |= GPIO_PIN_3; //Sets the serial port enable pin CS high (idle)
__HAL_SPI_ENABLE(&SPI_Params); //Enable the SPI

//Code to initialise GPIOE pin 0 for the interrupt
GPIOE_Params_I.Pin = GPIO_PIN_0; // Selects pin 0
GPIOE_Params_I.Mode = GPIO_MODE_IT_RISING; // Selects the interrupt mode and configures the interrupt to be signalled on a rising edge (low to high transition)
GPIOE_Params_I.Speed = GPIO_SPEED_FAST; //Selects fast speed
HAL_GPIO_Init(GPIOE, &GPIOE_Params_I); // Sets GPIOE into the modes specified in GPIOE_Params_I
__HAL_SPI_ENABLE(&SPI_Params); //Enable the SPI

// Initialize GPIO Port for LEDs and buttons
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable Port D clock
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		//Enable GPIOA ports
GPIOD->MODER |= GPIO_MODER_MODER14_0; // Port D.14 output - red LED
GPIOD->MODER |= GPIO_MODER_MODER12_0; // Port D.12 output - green LED
GPIOD->MODER |= GPIO_MODER_MODER15_0; // Port D.15 output - blue LED
GPIOD->MODER |= GPIO_MODER_MODER13_0; // Port D.13 output - orange
GPIOA->MODER |= 0; // GPIOA pin 0 USER PUSHBUTTON
	
	
	
data_to_send[0] = 0x00|0x20; // Address for Control_REG_4 register on LIS3DSH
GPIOE->BSRR |= GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0]=0x13;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
GPIOE->BSRR |= GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process




// Write a new value to control register 3 of the LIS3DSH to configure the interrupts
data_to_send[0] = 0x23; // Address for control register 3 on the LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0xC8; // Enable DRDY connected to Int1, sets Int1 active to high, enables int1
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the new register value to the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process
//GPIOD->BSRR |= (1<<13); // Turns on the orange LED

for(;;){ //the loop keeps everything repeat
if ((GPIOA->IDR & 0x0001)!=1){  			//when the button was not pressed
if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0)==SET){ // If interupt us avoked, start this
__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); // Clears the interrupt flag before proceeding to service the interrupt for next time use

// Get the value from the MSB X-axis and Y-axis data register of the LIS3DSH
data_to_send[0] = 0x80|0x29; // Address for X out on LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication 
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
X_Reg = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer sub-structure into our internal variable.

	
data_to_send[0] = 0x80|0x2B; // Address for Y OUT on LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication 
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
Y_Reg = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer sub-structure into our internal variable.


if((Y_Reg&0x80) == 0x80){ // Check to see if the received value is positive or negative - the acceleration is a signed 16-bit number so the MSB is the sign bit - 1 is negative, 0 is positive. 
GPIOD->BSRR = (1<<15); // If the receive value is negative turn on the blue LED
GPIOD->BSRR = (1<<(13+16)); // If the receive value is negative turn off the orange LED
}
else if((Y_Reg) == 0x00){ //Check to see if the received value is 0, 
GPIOD->BSRR = (1<<(13+16)); // turn off led
GPIOD->BSRR = (1<<(15+16)); // turn off led
}
else{
GPIOD->BSRR = (1<<13); // If the received value is another case turn on the orange LED
GPIOD->BSRR = (1<<(15+16)); // If the received value is another case turn off the blue LED
}

if((X_Reg) == 0x00){ //if X value is 0
GPIOD->BSRR = (1<<(14+16)); // turn ff the red LED
GPIOD->BSRR = (1<<(12+16)); //  turn off the green LED
}

else if((X_Reg&0x80) != 0x80){ //determine the value is a positive value
GPIOD->BSRR = (1<<14); // If the received value is positive turn on the red LED
GPIOD->BSRR = (1<<(12+16)); // If the received value is positive turn off the green LED
}

else if((X_Reg&0x80) == 0x80){ //determine the value is a negative value
GPIOD->BSRR = (1<<12); // If the received value is positive turn on the green LED
GPIOD->BSRR = (1<<(14+16)); // If the received value is positive turn off the red LED
}

else{
	
	//to let initial value cases stay here
	}

}

}


else{
// Just to let else status of code be kept here, in case of unpredicted changes. 
} 
}
}
