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
/****************************DEFINES Y MACROS****************************/
#define MAX_THREADS_ 1
QueueHandle_t QueueLED_hijo;
extern QueueHandle_t QueueLEDS;
typedef enum{
	ON,
	OFF
}estado_t;
typedef enum{
	RED,
	GREEN
}color_t;

typedef struct{
	estado_t estado;
	color_t color;
}led_t;
static struct {
	QueueHandle_t hclient_queue;
	void (*callback)(led_t *);
	size_t task_cnt;
	size_t client_cnt;
} atencion;
#define TASK_PERIOD_MS_         (10)				//Tiempo que toma atender al led



led_t infoLed;
led_t infoLed2;

/*!
 * @brief Callback para manejar los leds usando el código encolado
 *
 * @param[codigo_t ] El código del estado que debe tener el led
 *
 * @return Función del tipo void.
 */
static void callbackLEDS(led_t* leds) {
	if(leds->color==GREEN && leds->estado==ON)
	{
		eboard_led_green(1);
	}
	else if(leds->color==GREEN && leds->estado==OFF)
	{
		eboard_led_green(0);
	}
	else if(leds->color==RED && leds->estado==ON)
	{
		eboard_led_red(1);
	}
	else if(leds->color==RED && leds->estado==OFF)
	{
		eboard_led_red(0);
	}
}
/*!
 * @brief Elimina la tarea hijo
 *
 * @return Función del tipo void.
 */
static void task_delete_(void) {
	ELOG("Borro una tarea");
	atencion.task_cnt--;
	ELOG("Cantidad de tareas: %d", atencion.task_cnt);
	vTaskDelete(NULL);
}
/*!
 * @brief Task para llamar al callback mientras hayan clientes sin atender en la cola
 *@param[void *] Puntero a parámetros.
 * @return Función del tipo void.
 */
static void task_(void *argument) {
	led_t* client;
	while (true) {
		while (pdPASS == xQueueReceive(atencion.hclient_queue,&client , 0)) {
			ELOG("Código del estado del led: [%i]", client);

			atencion.client_cnt++;
			ELOG("Cantidad de estados leds siendo atendidos: %d", client->color);

			atencion.callback(client);
			//Tiempo que toma atender a un item led de la cola
			vTaskDelay((TickType_t) (TASK_PERIOD_MS_ / portTICK_PERIOD_MS));
			ELOG("Fin de la atención del led: [%i]", client);

			atencion.client_cnt--;
			ELOG("Cantidad de estados leds siendo atendidos: %d", atencion.client_cnt);
		}
		task_delete_();
	}
}
/*!
 * @brief Crea un task dinámico
 *
 * @return Función del tipo void.
 */
static bool task_create_(void) {
	if (atencion.task_cnt < MAX_THREADS_)
	{
		ELOG("Creo una tarea");
		atencion.task_cnt++;
		ELOG("Cantidad de tareas: %d", atencion.task_cnt);
		BaseType_t status;
		status = xTaskCreate(task_, "task_bank", 128, NULL,
				tskIDLE_PRIORITY + 1, NULL);
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
/*!
 * @brief Envía puntero a una estructura con los datos del led a atender
 * @param[led_t *] La informacion del led.
 * @return Función del tipo void.
 */
static void sendtoQueueHijo(led_t* leds)
{
	if (pdPASS== xQueueSend(atencion.hclient_queue,&leds, 0))
			{
				ELOG("Ingresa el cliente [%i] a la fila", codigo_recibido);
				if (0 == atencion.task_cnt)
				{
					if(!task_create_())
					{
						ELOG("Error!!!");//error
					}
				}
			}
			else
			{
				ELOG("Error!!!");				//error
			}
}
/*!
 * @brief Decodifica el valor recibido
 * @param[codigo_t ] Codigo recibido desde OA_SYS.
 * @return Función del tipo void.
 */
static void decodificarLeds(codigo_t cod) {
	switch (cod) {
					case GREEN_ON:
						infoLed.color = GREEN;
						infoLed.estado=ON;
						sendtoQueueHijo(&infoLed);
						break;
					case GREEN_OFF:
						infoLed.color = GREEN;
						infoLed.estado=OFF;
						sendtoQueueHijo(&infoLed);
						break;
					case RED_ON:
						infoLed.color = RED;
						infoLed.estado=ON;
						sendtoQueueHijo(&infoLed);
						break;
					case RED_OFF:
						infoLed.color = RED;
						infoLed.estado=OFF;
						sendtoQueueHijo(&infoLed);
						break;
					case BOTH_ON:
						infoLed.color = GREEN;
						infoLed.estado=ON;
						sendtoQueueHijo(&infoLed);
						infoLed2.color = RED;
						infoLed2.estado=ON;
						sendtoQueueHijo(&infoLed2);
						break;
					case BOTH_OFF:
						infoLed.color = GREEN;
						infoLed.estado=OFF;
						sendtoQueueHijo(&infoLed);
						infoLed2.color = RED;
						infoLed2.estado=OFF;
						sendtoQueueHijo(&infoLed2);
						break;
					}
}
/*!
 * @brief Crea un task dinámico
 * @param[void *] Puntero a parámetros.
 * @return Función del tipo void.
 */
void vTask_OA_LEDS(void *pvParameters) {

	codigo_t codigo_recibido;

	/*Creación de cola para task hijo*/
	QueueLED_hijo = xQueueCreate(2, sizeof(led_t*));

	/* Check the queues was created successfully */
	configASSERT(QueueLED_hijo != NULL);

	/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
	vQueueAddToRegistry(QueueLED_hijo, "QueueLED_hijo");

	atencion.hclient_queue = QueueLED_hijo;
	atencion.callback = callbackLEDS;

	while (1) {

		/*
		 * Recibe el estado del botón de la cola y lo envía a la cola de atención
		 */
		if (pdPASS == xQueueReceive(QueueLEDS, &codigo_recibido, 0))
		{
			decodificarLeds(codigo_recibido);
		}
		else
		{
			ELOG("Error!!!");			//error
		}

	}
}
