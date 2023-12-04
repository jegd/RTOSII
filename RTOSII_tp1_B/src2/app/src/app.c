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
#include "OA_SYS.h"
#include "eboard.h"
#define QUEUE_BUTTON_LENGHT (1)
#define QUEUE_LEDS_LENGHT (1)
xTaskHandle vTask_OA_BTNHandle;
xTaskHandle vTask_OA_LEDSHandle;
xTaskHandle vTask_OA_SYSHandle;


QueueHandle_t QueueLEDS;
// ------ internal data definition -------------------------------------
//Texto de inicialización
const char *pcTextForMain = "*******RTOS II TP 1 Parte A is running******* \r\n"
		                    "- Anthony  Maisincho              N°SIU e2011 \r\n"
		                    "- Jesus    Gonzales               N°SIU e2006\r\n";
//Inicia las tareas de los OA

	/* App Initialization */
void app_init( void ){
		  	vPrintString( pcTextForMain );

		    // drivers
		    {
		      eboard_init();
		    }

			/*Creación de colas*/
		  	QueueBtnStatus = xQueueCreate(QUEUE_LEDS_LENGHT,sizeof(Btn_State));


			/* Check the queues was created successfully */
			configASSERT( QueueBtnStatus != NULL );

			/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
			vQueueAddToRegistry( QueueBtnStatus, "QueueBtnStatus" );

			/*Creación de colas*/
			QueueLEDS = xQueueCreate(QUEUE_BUTTON_LENGHT,sizeof(color_led));

			/* Check the queues was created successfully */
			configASSERT( QueueLEDS != NULL );

			/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
			vQueueAddToRegistry( QueueLEDS, "QueueLEDS" );




			BaseType_t ret;

			/* Task OA_BTN thread at priority 2 */
			ret = xTaskCreate(vTask_OA_BTN, /* Pointer to the function thats implement the task. */
			"Task OA_BTN", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&vTask_OA_BTNHandle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task OA_LEDS thread at priority 2 */
			ret = xTaskCreate(vTask_OA_LEDS, /* Pointer to the function thats implement the task. */
			"Task OA_LEDS", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&vTask_OA_LEDSHandle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task OA_SYS thread at priority 2 */
			ret = xTaskCreate(vTask_OA_SYS, /* Pointer to the function thats implement the task. */
			"Task OA_SYS", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&vTask_OA_SYSHandle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);


			return;

}

