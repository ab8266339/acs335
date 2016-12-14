//Name: Yunlong Li
//Date: 19-10-2016
//Course: Acs335
#include "stm32f4xx.h"
int main(void){
	uint8_t LED_on = 1; // Defines parameter for LED on
uint8_t LED_off = 0; // Defines parameter for LED off
SPI_HandleTypeDef SPI_Params; // Declares the structure handle for the parameters of SPI1	
GPIO_InitTypeDef GPIOA_Params; // Declares the structure handle for the parameters of GPIOA
GPIO_InitTypeDef GPIOE_Params; // Declares the structure handle for the parameters of GPIOE
GPIO_InitTypeDef GPIOE_Params_I; // Declares the structure handle for the parameters of GPIOE	
uint8_t data_to_send[1]; //Declares an array to store the required LIS3DSH register address in. It has a single element since we will only be accessing a single address in each SPI transaction.
uint16_t data_size=1; //Declares a variable that specifies that only a single address is accessed in each transaction.
uint32_t data_timeout=1000; //Sets a maximum time to wait for the SPI transaction to complete in - this mean that our program won’t freeze if there is a problem with the SPI communication channel.	

	uint8_t Y_Reg_H; //Declares the variable to store the y-axis MS 8-bits in high
	uint8_t Y_Reg_L; //Declares the variable to store the y-axis MS 8-bits in low
	int16_t Y_Accn;  //Declare the variable to store the y-axis accelerationin - 16 bit number
	uint8_t X_Reg_H; //Declares the variable to store the x-axis MS 8-bits in high
	uint8_t X_Reg_L; //Declares the variable to store the x-axis MS 8-bits in low	
	int16_t X_Accn;  //Declare the variable to store the x-axis accelerationin - 16 bit number
	uint8_t Z_Reg_H; //Declares the variable to store the y-axis MS 8-bits in high
	uint8_t Z_Reg_L; //Declares the variable to store the y-axis MS 8-bits in low
	int16_t Z_Accn;  //Declare the variable to store the y-axis accelerationin - 16 bit number
	uint16_t ii;     //Declare a variable to implement switch bounce
		uint32_t i;
	 
// Code to initialise the SPI
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //Enable the clock for SPI1
SPI_Params.Instance = SPI1; // Selects which SPI interface to use
SPI_Params.Init.Mode = SPI_MODE_MASTER; // Sets the STM32F407 to act as the master
SPI_Params.Init.NSS = SPI_NSS_SOFT; // Sets the slave to be controlled by software
SPI_Params.Init.Direction = SPI_DIRECTION_2LINES; // Sets the SPI to fullduplex
SPI_Params.Init.DataSize = SPI_DATASIZE_8BIT; // Sets the data packet size to 8-bit
SPI_Params.Init.CLKPolarity = SPI_POLARITY_HIGH; // Sets the idle polarity for the clock line to high
SPI_Params.Init.CLKPhase = SPI_PHASE_2EDGE; // Sets the data line to change on the second transition of the clock line
SPI_Params.Init.FirstBit = SPI_FIRSTBIT_MSB; // Sets the transmission to MSB first
SPI_Params.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; // Sets the clock prescaler to divide the main APB2 clock (previously set to 84MHz) by 32 to give a SPI clock of 2.625MHz, which is less the maximum value of 10MHz for the SPI.
HAL_SPI_Init(&SPI_Params); // Configures the SPI using the specified parameters

// Code to initialise pins 5-7 of GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //Enable the clock for GPIOA
GPIOA_Params.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; // Selects pins 5,6 and 7
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


GPIOE_Params_I.Pin = GPIO_PIN_0;
GPIOE_Params_I.Mode = GPIO_MODE_IT_RISING;
GPIOE_Params_I.Speed = GPIO_SPEED_FAST;
HAL_GPIO_Init(GPIOE, &GPIOE_Params_I);

GPIOE->BSRR = GPIO_PIN_3; //Sets the serial port enable pin CS high (idle)
__HAL_SPI_ENABLE(&SPI_Params); //Enable the SPI

// Initialize GPIO Port for LEDs
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable Port D clock
GPIOD->MODER |= GPIO_MODER_MODER14_0; // Port D.14 output - red LED
GPIOD->MODER |= GPIO_MODER_MODER12_0; // Port D.12 output - green LED
GPIOD->MODER |= GPIO_MODER_MODER13_0;
GPIOD->MODER |= GPIO_MODER_MODER15_0;

////////////////////////////////////////////////////ACC
data_to_send[0] = 0x20;
GPIOE->BSRR = GPIO_PIN_3<<16;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x73;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
GPIOE->BSRR = GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process


data_to_send[0] = 0x24; // Address for Register_4 register on LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH



data_to_send[0] = 0x23; // Address for Register_4 register on LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0xC8;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); 
GPIOE->BSRR = GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process

	

		
	while(1){
		// Read the value from the MSB (H) x-axis data register of the LIS3DSH
data_to_send[0] = 0x80|0x2D;//Address for control register 4 on the LIS3DSH
// Address for the MSB x-axis (H) data register on the LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);// Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
Z_Reg_H = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer substructure into our internal variable.

// Read the value from the MSB (L) x-axis data register of the LIS3DSH
data_to_send[0] = 0x80|0x2C;//Address for control register 4 on the LIS3DSH
// Address for the MSB x-axis (L) data register on the LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);// Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
Z_Reg_L = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer substructure into our internal variable.

Z_Accn = (Z_Reg_H <<8)| Z_Reg_L; //Combined the MSB and LSB 8-bit registers into a single 16-bit value
		data_to_send[0]=0x80|0x29;////////du x M
		GPIOE->BSRR = GPIO_PIN_3<<16;
		HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
    data_to_send[0]=0x00;
    HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout); 
    GPIOE->BSRR = GPIO_PIN_3;
    X_Reg_H = *SPI_Params.pRxBuffPtr;


    data_to_send[0] = 0x80|0x28;////////// du x L
		GPIOE->BSRR = GPIO_PIN_3<<16;
		HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
    data_to_send[0]=0x00;
    HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout); 
    GPIOE->BSRR = GPIO_PIN_3;
    X_Reg_L = *SPI_Params.pRxBuffPtr;
		
		X_Accn = (X_Reg_H<<8)|X_Reg_L;
		
		
		data_to_send[0]=0x80|0x2B;////////du x M
		GPIOE->BSRR = GPIO_PIN_3<<16;
		HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
    data_to_send[0]=0x00;
    HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout); 
    GPIOE->BSRR = GPIO_PIN_3;
    Y_Reg_H = *SPI_Params.pRxBuffPtr;


    data_to_send[0] = 0x80|0x2A;////////// du x L
		GPIOE->BSRR = GPIO_PIN_3<<16;
		HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
    data_to_send[0]=0x00;
    HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout); 
    GPIOE->BSRR = GPIO_PIN_3;
    Y_Reg_L = *SPI_Params.pRxBuffPtr;
		
		Y_Accn = (Y_Reg_H<<8)|Y_Reg_L;


				if((Y_Accn > 600||Y_Accn < -600||Z_Accn < -200)||(Z_Accn > 200))){
			GPIOD ->BSRR =1<<12;
				}
				else GPIOD ->BSRR = 1<<28;
		
	}
}