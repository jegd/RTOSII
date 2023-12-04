/** @file OA_LEDS.c
 *  @Created on: Dic 03, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 *
 *  @brief Objeto activo que recibe la notificación del objeto activo botón.
 *
 */

/****************************INCLUDES****************************/
#include "OA_LEDS.h"
/****************************VARIABLES GLOBALES****************************/

#define MAX_THREADS_ 6
QueueHandle_t QueueLED_hijo;
extern QueueHandle_t QueueLEDS;
static struct {
	QueueHandle_t hclient_queue;
	void (*callback)(codigo_t);
	size_t task_cnt;
	size_t client_cnt;
} atencion;

#define TASK_PERIOD_MS_         (10*1000)
//Tarea objeto activo led
/*!
 * @brief Tarea del Objeto activo botón.
 *
 * @param[void *] Puntero a parámetros.
 *
 * @return Función del tipo void.
 */
void callbackLEDS(codigo_t cod) {
	switch (cod) {
	case GREEN_ON:
		eboard_led_green(1);
		break;
	case GREEN_OFF:
		eboard_led_green(0);
			break;
	case RED_ON:
		eboard_led_red(1);
			break;
	case RED_OFF:
		eboard_led_red(0);
			break;
	case BOTH_ON:
		eboard_led_red(1);
		eboard_led_green(1);
				break;
	case BOTH_OFF:
		eboard_led_red(0);
		eboard_led_green(0);
				break;
	}
}

static void task_delete_(void)
{
  ELOG("Borro una tarea");
  atencion.task_cnt--;
  ELOG("Cantidad de tareas: %d", atencion.task_cnt);

  vTaskDelete(NULL);
}

static void task_(void* argument)
{
	codigo_t client;
  while (true)
  {
    while (pdPASS == xQueueReceive(atencion.hclient_queue, &client, 0))
    {
      ELOG("Llamo al cliente: [%i]", client);

    atencion.client_cnt++;
      ELOG("Cantidad de clientes siendo atendidos: %d", atencion.client_cnt);

      atencion.callback(client);
      vTaskDelay((TickType_t)(TASK_PERIOD_MS_ / portTICK_PERIOD_MS));
      ELOG("Fin de la atención del cliente: [%i]", client);

      atencion.client_cnt--;
      ELOG("Cantidad de clientes siendo atendidos: %d", atencion.client_cnt);
    }
    task_delete_();
  }
}


static bool task_create_(void)
{
  if(atencion.task_cnt < MAX_THREADS_)
  {
    ELOG("Creo una tarea");
    atencion.task_cnt++;
    ELOG("Cantidad de tareas: %d", atencion.task_cnt);
    BaseType_t status;
    status = xTaskCreate(task_, "task_bank", 128, NULL, tskIDLE_PRIORITY + 2, NULL);
    while (pdPASS != status)
    {
      ELOG("Error!!!");
      // error
    }
    return true;
  }
  else
  {
    ELOG("No puedo crear nuevas tareas");
    return false;
  }
}


void vTask_OA_LEDS(void *pvParameters) {

	BaseType_t rv; //Variable para verificar el correcto encolado de la notificación
	color_led color_recibido; //Variable que almacena la notificación de la cola que contiene el estado del botón
	estado_led estado_recibido;
	codigo_t codigo_recibido;
	const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000UL); //xTicksToWait de la cola
	//vPrintString(OALEDS_WelcomeMsg);

	/*Creación de colas*/
	QueueLED_hijo = xQueueCreate(4,sizeof(codigo_t));

		/* Check the queues was created successfully */
		configASSERT( QueueLED_hijo != NULL );

		/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
		vQueueAddToRegistry( QueueLED_hijo, "QueueLED_hijo" );

		atencion.hclient_queue = QueueLED_hijo;
			atencion.callback = callbackLEDS;

	while (1) {

		/*
		 * Recibe el estado del botón de la cola y lo envía a la variable Received
		 */
		/*
		 if(pdPASS==xQueueReceive(QueueLEDS, &color_recibido, xDelay10000ms))
		 {
		 //ok
		 vPrintString("color recibido");
		 }
		 if(pdPASS==xQueueReceive(QueueLEDS, &estado_recibido, xDelay10000ms))
		 {
		 vPrintString("estado recibido");
		 }
		 */
		if (pdPASS== xQueueReceive(QueueLEDS, &codigo_recibido, xDelay10000ms)) {

			//ok
			vPrintStringAndNumber("color recibido", (uint32_t) codigo_recibido);
		}
		  if (pdPASS == xQueueSend(atencion.hclient_queue, (void* )&codigo_recibido, 0))
		  {
		    // ok
		    ELOG("Ingresa el cliente [%i] a la fila", codigo_recibido);
		    if(0 == atencion.task_cnt)
		    {
		      task_create_();
		    }
		    //return true;
		  }

		//Revisar que el mensaje se halla encolado correctamente.
		//configASSERT(&rv != NULL);
		//Revisar que el valor del estado del botón esté dentro del rango esperado
		//if(Received<0 &&Received>4) configASSERT(FALSE);

		/*
		 * Procesamiento de la notificación recibida
		 *
		 * SHORPRESSED: Invertir el estado del LED verde
		 * LONGPRESSED: Invertir el estado del LED rojo.
		 * BLOCKED: Encender el LED verde y LED rojo.
		 * UNBLOCKED: Apagar el LED verde y el LED rojo.
		 * NONE: No realiza nada.
		 *
		 */

	}
}
