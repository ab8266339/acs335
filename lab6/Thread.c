#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32f4xx.h"
#include "my_headers.h"

/*----------------------------------------------------------------------------
 *      Thread definition
 *---------------------------------------------------------------------------*/
/* Thread IDs */
osThreadId tid_Blink_LED_Thread;
osThreadId tid_Button_Thread; 
osThreadId tid_Second_Thread;
osThreadId tid_Light_Thread;
osEvent evt;
/* Forward reference */
void Blink_LED_Thread (void const *argument); // Declares the main thread function that is defined later in the codeosThreadId tid_Blink_LED_Thread; // Declares an ID that we will associate with the thread and which allows easy reference to it when using some of the OS functions.
void Button_Thread (void const *argument); // Declares the main thread function that is defined later in the code
void Second_Thread (void const *argument);
void Light_Thread (void const *argument);
/* Thread definitions */
osThreadDef (Button_Thread, osPriorityNormal, 1, 0); // Declares the main thread object that we will use later. The parameters can be used to adjust certain properties, such as the priority of a thread and how many instances of it exist.
osThreadDef (Blink_LED_Thread, osPriorityNormal, 1, 0); // Declares the main thread object that we will use later. The parameters can be used to adjust certain properties, such as the priority of a thread and how many instances of it exist.
osThreadDef (Second_Thread, osPriorityNormal, 1, 0);
osThreadDef (Light_Thread, osPriorityAboveNormal, 1, 0);
// Code to define the thread function to initialise the main thread -this initialise function is called from the “main.c” file to start the thread.
int Init_Button_Thread (void) {
tid_Button_Thread = osThreadCreate (osThread(Button_Thread), NULL); // Creates the main thread object that we have declared and assigns it the thread ID that we have declared.
if(!tid_Button_Thread) return(-1); // Checks to make sure the thread has been created.
return(0);
}
int Init_Blink_LED_Thread (void) {
tid_Blink_LED_Thread = osThreadCreate (osThread(Blink_LED_Thread), NULL); 
// Creates the main thread object that we have declared and assigns it the thread ID that we have declared.
if(!tid_Blink_LED_Thread) return(-1); 
// Checks to make sure the thread has been created.
return(0);
}
int Init_Second_Thread(void){
tid_Second_Thread= osThreadCreate ((osThread(Second_Thread)),NULL);
	if(!tid_Second_Thread) return(-1);
	return (0);
	;
	}
int Init_Light_Thread(void){
tid_Light_Thread= osThreadCreate ((osThread(Light_Thread)),NULL);
	if(!tid_Light_Thread) return(-1);
	return (0);
	;
}
uint16_t Z_Reg;
void Light_Thread (void const *argument) {}
/*
-------------------------------------------------------------------------
*      Blink LED Thread
*
-----------------------------------------------------------------------
*/
// Code to define the thread function to initialise the main thread -this initialise function is called from the “main.c” file to start the thread.
// Code to define the operation of the main thread. This is effectively the code that was in the infinite FOR loop of our previous blinky program.
void Blink_LED_Thread (void const *argument) {
uint8_t LED_on = 1; // Defines parameter for LED on
uint8_t LED_off = 0; // Defines parameter for LED off
	evt = osSignalWait(0x01,0);
//	int counter1;
	osSignalSet(tid_Blink_LED_Thread, 0x01);
while (1) { // Creates an infinite loop so that the blinking never terminate
	Green_LED(LED_on); // Blinks the green LED on once
	Blue_LED(LED_on);
	if (osEventSignal == 0x08){
		while(1){
	if(((GPIOA->IDR & 0x00000001) == 0x00000001) & ((GPIOD->ODR & (1<<14)) != (1<<14))){
		Green_LED(LED_off);
		osDelay(3000);
		TIM2 ->EGR = 1;
		TIM2 -> CR1 |= 1;
		TIM2->SR &= ~1; //Resets the flag
while((TIM2 -> SR & 0x0001)!=1){
	Green_LED(LED_off);
	Blue_LED(LED_on);
	osDelay(100);
	Blue_LED(LED_off);
	osDelay(100);
};
//	TIM2->SR &= ~1; //Resets the flag
	TIM3 ->EGR = 1;
	TIM3 -> CR1 |= 1;
	TIM3->SR&= ~1; //Resets the flag
while((TIM3 -> SR & 0x0001)!=1){
	Blue_LED(LED_on);
	osDelay(100);
	Blue_LED(LED_off);
	osDelay(100);
};
Green_LED(LED_on); // Blinks the green LED on once
	Blue_LED(LED_on);
TIM4 ->EGR  |= 1;
TIM4 -> CR1 |= 1;
TIM4->SR&= ~1; //Resets the flag
while((TIM4 -> SR & 0x0001)!=1){
	if(((GPIOA->IDR & 0x00000001) == 0x00000001)){
		evt = osSignalWait(0x02,15000);
		evt = osSignalWait(0x01,0);
		osSignalSet(tid_Blink_LED_Thread, 0x01);
		osThreadYield();
		break;
		}
	else evt = osSignalWait(0,0);
		
	}
	

	TIM4->SR&= ~1; //Resets the flag

osThreadYield(); // This function tells the RTOS that when the thread gets to this stage the RTOS should suspend this thread and run the next thread that isready to run. If there is no other thread ready (which is the case with this simple program since we only have one thread) then the calling thread continues. This function effectively forces the RTOS to reschedule and is useful in more complex systems andscheduling policies.
}
		}
}
}
}
/*
-------------------------------------------------------------------------
*      Red LED and Orange LED on when button pressed thread Thread
*
-----------------------------------------------------------------------
*/
// Code to define the operation of the main thread. This is effectively the code that was in the infinite FOR loop of our previous blinky program.
void Button_Thread (void const *argument) {
uint8_t LED_on = 1; // Defines parameter for LED on
uint8_t LED_off = 0; // Defines parameter for LED off
evt=osSignalWait(0x01,0);
while (1) { // Creates an infinite loop so that the blinking never terminates
// Checks the state of the push-button and only turns the red LED on if the button has only just been pressed, which is indicated by the state of the red LED. 
if (evt.status ==osOK ){
	while(1){
	if(((GPIOA->IDR & 0x00000001) == 0x00000001) & ((GPIOD->ODR & (1<<14)) != (1<<14))){
	Green_LED(LED_off);
	Orange_LED(LED_on);
	osDelay(2000);
	Orange_LED(LED_off);
	Red_LED(LED_on);
	osDelay(1000);
	Red_LED(LED_off);
	TIM2 -> EGR  |= 1;
	TIM2 -> CR1 |= 1;
	TIM2 -> SR &=~1; //Resets the flag
	
	while ((TIM2-> SR & 0x0001)!=1){
		Red_LED(LED_on);
	}
	TIM3 ->EGR  |= 1;
	TIM3 -> CR1 |= 1;
	TIM3->SR&= ~1; //Resets the flag
		while((TIM3 -> SR & 0x0001)!=1){
			Red_LED(LED_off);
		Orange_LED(LED_on);
		osDelay(300);
		Orange_LED(LED_off);
		osDelay(300);
};
	TIM3->SR&= ~1;
TIM4 ->EGR  |= 1;
TIM4 -> CR1 |= 1;
TIM4->SR&= ~1; //Resets the flag
while((TIM4 -> SR & 0x0001)!=1){
	if(((GPIOA->IDR & 0x00000001) == 0x00000001)){
	 evt=osSignalWait(0x02,15000);
	evt =osSignalWait(0x01,0);
		osSignalSet(tid_Button_Thread, 0x01);
		osThreadYield();
		break;
	}
	else evt = osSignalWait(0x01,0);
	}
	TIM4->SR&= ~1; //Resets the flag
}
osThreadYield();
	}

// Checks the state of the push-button and only turns the red LED off if the button has only just been released, which is indicated by the state of the red LED. 
//osThreadYield(); // This function tells the RTOS that when the thread gets to this stage the RTOS should suspend this thread and run the the case with this simple program since we only have one thread) then the calling thread continues. This function effectively forces the RTOS to reschedule and is useful in more complex systems and scheduling policies.
}
}
}





//int counter;
void Second_Thread (void const *argument){
uint8_t LED_on = 1; // Defines parameter for LED on
uint8_t LED_off = 0; // Defines parameter for LED off	
SPI_HandleTypeDef SPI_Params; // Declares the structure handle for the parameters of SPI1
GPIO_InitTypeDef GPIOA_Params; // Declares the structure handle for the parameters of GPIOA
GPIO_InitTypeDef GPIOE_Params; // Declares the structure handle for the parameters of GPIOE
GPIO_InitTypeDef GPIOE_Params_I; // Declares the structure handle for the parameters of the interrupt pin on GPIOE
	uint16_t Z_flag;
//uint16_t Z_Reg; //Declares the variable to store the z-axis MS 16-bits in
//uint16_t X_Reg; //Declares the variable to store the x-axis MS 16-bits in
//uint16_t Y_Reg; //Declares the variable to store the y-axis MS 16-bits in
uint8_t data_to_send[1]; //Declares an array to store the required LIS3DSH
//register address in. It has a single element since we will only be
//accessing a single address in each SPI transaction.
uint16_t data_size=1; //Declares a variable that specifies that only a
//single address is accessed in each transaction.
uint32_t data_timeout=1000; //Sets a maximum time to wait for the SPI
//transaction to complete in - this mean that our program won’t freeze if
//there is a problem with the SPI communication channel.
//uint8_t CTRL_REG4; //Declares the variable to store the who_am_I register value in
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
GPIOD->BSRR |= (1<<13); // Turns on the orange LED
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
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		//Enable GPIOA ports
GPIOA->MODER |= 0; // GPIOA pin 0 USER PUSHBUTTON
data_to_send[0] = 0x00|0x20; // Address for Control_REG_4 register on LIS3DSH
GPIOE->BSRR |= GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0]=0x97;
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout);
GPIOE->BSRR |= GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process


// Write a new value to control register 3 of the LIS3DSH to configure the interrupts
data_to_send[0] = 0x23; // Address for control register 3 on the LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0xC8; // Enable DRDY connected to Int1, sets Int1 active to high, enables int1
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the new register value to the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3; // Set the SPI communication enable line high to signal the end of the communication process
//

for(;;){ //the loop keeps everything repeat
// Get the value from the MSB X-axis and Y-axis data register of the LIS3DSH
data_to_send[0] = 0x2D; // Address for Z out on LIS3DSH
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication 
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x0000; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
Z_Reg = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer sub-structure into our internal variable.
	Orange_LED(LED_on);
	
data_to_send[0] = 0x5f; // 
GPIOE->BSRR = GPIO_PIN_3<<16; // Set the SPI communication enable line low to initiate communication 
HAL_SPI_Transmit(&SPI_Params,data_to_send,data_size,data_timeout); // Send the address of the register to be read on the LIS3DSH
data_to_send[0] = 0x00; // Set a blank address because we are waiting to receive data
HAL_SPI_Receive(&SPI_Params,data_to_send,data_size,data_timeout);// Get the data from the LIS3DSH through the SPI channel
GPIOE->BSRR = GPIO_PIN_3;// Set the SPI communication enable line high to signal the end of the communication process
Z_flag = *SPI_Params.pRxBuffPtr; // Read the data from the SPI buffer sub-structure into our internal variable.
	Orange_LED(LED_on);


}
}
