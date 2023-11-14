/** @file OA_LEDS.c
 *  @Created on: Nov 12, 2023
 *  @Authors:  Edda     Andrade                N°SIU e2014
 *             Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 *
 *  @brief Objeto activo que recibe la notificación del objeto activo botón.
 *
 */

/****************************INCLUDES****************************/
#include "OA_LEDS.h"
/****************************VARIABLES GLOBALES****************************/
extern const char *messages[]; //Puntero al vector de mensajes para los estados del botón
const char *OALEDS_WelcomeMsg = "OA_LEDS se está ejecutando\r\n"; //Mensaje de bienvenida.
//Tarea objeto activo led
/*!
 * @brief Tarea del Objeto activo botón.
 *
 * @param[void *] Puntero a parámetros.
 *
 * @return Función del tipo void.
 */
void vTask_OA_LEDS(void *pvParameters) {

	BaseType_t rv; //Variable para verificar el correcto encolado de la notificación
	enum Btn_Status Received; //Variable que almacena la notificación de la cola que contiene el estado del botón
	const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000UL); //xTicksToWait de la cola
	vPrintString(OALEDS_WelcomeMsg);

	while (1) {

		/*
		 * Recibe el estado del botón de la cola y lo envía a la variable Received
		 */
		rv = xQueueReceive(QueueBtnStatus, &Received, xDelay10000ms);
		//Revisar que el mensaje se halla encolado correctamente.
		configASSERT(&rv != NULL);
		//Revisar que el valor del estado del botón esté dentro del rango esperado
		if(Received<0 &&Received>4) configASSERT(FALSE);

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

		switch (Received) {
		case SHORTPRESSED: // Toggle Led Verde
			vPrintString(messages[Received]);
			eboard_led_green(!eboard_gpio_read(EBOARD_GPIO_LEDG));
			break;
		case LONGPRESSED: // Toggle Led Rojo
			vPrintString(messages[Received]);
			eboard_led_red(!eboard_gpio_read(EBOARD_GPIO_LEDR));
			break;
		case BLOCKED: // Encender los dos Leds
			vPrintString(messages[Received]);
			eboard_led_green(true);
			eboard_led_red(true);
			break;
		case UNBLOCKED: //Apagar los dos leds
			vPrintString(messages[Received]);
			eboard_led_green(false);
			eboard_led_red(false);
			break;
		case NONE: //No se presionó el botón
			//No realiza nada
			break;
		default:
			eboard_led_green(false);
			eboard_led_red(false);
			break;

		}
	}
}
