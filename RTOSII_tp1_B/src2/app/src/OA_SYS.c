/*
 * OA_SYS.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Jesus
 */
#include "OA_SYS.h"
extern QueueHandle_t QueueLEDS;
codigo_t codigo_a_enviar;
/*!
 * @brief Manda el código de led por medio de la cola de leds
 *
 * @param[codigo_t ] El código del estado que debe tener el led
 *
 * @return Función del tipo void.
 */
static void sendToLeds_cod(codigo_t codigo)
{
	if(pdPASS==xQueueSend(QueueLEDS, &codigo, 0))
	{
		//ok
	}
	else
	{
		ELOG("Error!!!");//error
	}

}
/*!
 * @brief OA_SYS procesa el código recibido del botón
 * @param[void *] Puntero a parámetros.
 * @return Función del tipo void.
 */
void vTask_OA_SYS(void *pvParameters)
{

	enum Btn_Status estadoBoton; //Variable que almacena la notificación de la cola que contiene el estado del botón

	while(1)
	{
		if(pdPASS==xQueueReceive(QueueBtnStatus, &estadoBoton, 0))
		{
			switch (estadoBoton) {
				case SHORTPRESSED: // Toggle Led Verde
					if(eboard_gpio_read(EBOARD_GPIO_LEDG))
					sendToLeds_cod(GREEN_OFF);
					else
					sendToLeds_cod(GREEN_ON);
					break;
				case LONGPRESSED: // Toggle Led Rojo
					if(eboard_gpio_read(EBOARD_GPIO_LEDR))
					sendToLeds_cod(RED_OFF);
					else
					sendToLeds_cod(RED_ON);
					break;
				case BLOCKED: // Encender los dos Leds
					sendToLeds_cod(BOTH_ON);
					break;
				case UNBLOCKED: //Apagar los dos leds
					sendToLeds_cod(BOTH_OFF);
					break;
				case NONE:
					//No realiza nada
					break;
				default:
					//default
					break;

				}

		}
		else
			{
				ELOG("Error!!!");//error
			}
	}

}
