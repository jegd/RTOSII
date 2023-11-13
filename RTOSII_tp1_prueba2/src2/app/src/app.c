#include "main.h"
#include "cmsis_os.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "app.h"
#include "driver.h"
#include "supporting_Functions.h"
#include "OA_BTN.h"
#include "OA_LEDS.h"
#include "eboard.h"

xTaskHandle vTask_OA_BTNHandle;
xTaskHandle vTask_OA_LEDSHandle;

// ------ internal data definition -------------------------------------
//const char *pcTextForMain = "Edda Andrade - RTOS II TP1-Parte A is running \r\n\n";
const char *pcTextForMain = "Edda Andrade - RTOS II TP 1 Parte A is running \r\n\n";
//Inicia las tareas de los OA

	/* App Initialization */
void app_init( void ){
		  	vPrintString( pcTextForMain );

		    // drivers

		    {
		      eboard_init();
		    }

			/*Creación de colas*/
		  	QueueBtnStatus = xQueueCreate(10,sizeof(Btn_State));


			/* Check the queues was created successfully */
			configASSERT( QueueBtnStatus != NULL );


			/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
			vQueueAddToRegistry( QueueBtnStatus, "QueueBtnStatus" );


			BaseType_t ret;

			/* Task OA_BTN thread at priority 2 */
			ret = xTaskCreate(vTask_OA_BTN, /* Pointer to the function thats implement the task. */
			"Task OA_BTN", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 2UL), /* This task will run at priority 1. 		*/
			&vTask_OA_BTNHandle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task B thread at priority 2 */
			ret = xTaskCreate(vTask_OA_LEDS, /* Pointer to the function thats implement the task. */
			"Task OA_LEDS", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 2UL), /* This task will run at priority 1. 		*/
			&vTask_OA_LEDSHandle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			return;

}

