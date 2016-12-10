
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32f4xx.h"
#include "my_headers.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Blink LED Thread'
 *---------------------------------------------------------------------------*/
 
void Blink_LED_Thread (void const *argument);                             // thread function
osThreadId tid_Blink_LED_Thread;                                          // thread id
osThreadDef (Blink_LED_Thread, osPriorityNormal, 1, 0);                   // thread object

int Init_Blink_LED_Thread (void) {

  tid_Blink_LED_Thread = osThreadCreate (osThread(Blink_LED_Thread), NULL);
  if (!tid_Blink_LED_Thread) return(-1);
  
  return(0);
}
	

void Blink_LED_Thread (void const *argument) {
uint8_t LED_on =1;
	uint8_t LED_off = 0;
  while (1) {
    Blink_LED(LED_on);
	osDelay (1000);
	Blink_LED(LED_off); // Insert thread code here...
		osDelay(1000);
    osThreadYield ();                                           // suspend thread
  }
}
