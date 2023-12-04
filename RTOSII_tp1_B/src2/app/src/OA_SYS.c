/*
 * OA_SYS.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Jesus
 */
#include "OA_SYS.h"
color_led led_a_enviar;
estado_led estado_a_enviar;
extern QueueHandle_t QueueLEDS;
codigo_t codigo_a_enviar;

void sendToLeds(color_led color, estado_led estado)
{
	if(pdPASS==xQueueSend(QueueLEDS, &color, portMAX_DELAY))
	{
		//ok
	}
	if(pdPASS==xQueueSend(QueueLEDS, &estado, portMAX_DELAY))
	{
			//ok
	}

}
void sendToLeds_cod(codigo_t codigo)
{
	if(pdPASS==xQueueSend(QueueLEDS, &codigo, portMAX_DELAY))
	{
		//ok
	}

}

void vTask_OA_SYS(void *pvParameters)
{

	enum Btn_Status estadoBoton; //Variable que almacena la notificación de la cola que contiene el estado del botón
	//const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000UL); //xTicksToWait de la cola
	//vPrintString(OALEDS_WelcomeMsg);

	while(1)
	{
		if(pdPASS==xQueueReceive(QueueBtnStatus, &estadoBoton, 0))
		{
			switch (estadoBoton) {
				case SHORTPRESSED: // Toggle Led Verde
					//vPrintString(messages[Received]);
					//eboard_led_green(!eboard_gpio_read(EBOARD_GPIO_LEDG));
					//led_a_enviar=GREEN;
					//estado_a_enviar=!eboard_gpio_read(EBOARD_GPIO_LEDG);
					//sendToLeds(led_a_enviar,estado_a_enviar);
					if(eboard_gpio_read(EBOARD_GPIO_LEDG))
					sendToLeds_cod(GREEN_OFF);
					else
					sendToLeds_cod(GREEN_ON);
					break;
				case LONGPRESSED: // Toggle Led Rojo
					//vPrintString(messages[Received]);
					//eboard_led_red(!eboard_gpio_read(EBOARD_GPIO_LEDR));
					//led_a_enviar=RED;
					//estado_a_enviar=!eboard_gpio_read(EBOARD_GPIO_LEDR);
					//sendToLeds(led_a_enviar,estado_a_enviar);
					if(eboard_gpio_read(EBOARD_GPIO_LEDR))
					sendToLeds_cod(RED_OFF);
					else
					sendToLeds_cod(RED_ON);
					break;
				case BLOCKED: // Encender los dos Leds
					//vPrintString(messages[Received]);
					//eboard_led_green(true);
					//eboard_led_red(true);
					//led_a_enviar=RED;
					//estado_a_enviar=!eboard_gpio_read(EBOARD_GPIO_LEDR);
					//sendToLeds(led_a_enviar,estado_a_enviar);
					sendToLeds_cod(BOTH_ON);
				case UNBLOCKED: //Apagar los dos leds
					//vPrintString(messages[Received]);
					//eboard_led_green(false);
					//eboard_led_red(false);
					sendToLeds_cod(BOTH_OFF);
					break;
				case NONE: //No se presionó el botón
					//No realiza nada
					break;
				default:
					//eboard_led_green(false);
					//eboard_led_red(false);
					break;

				}

		}
	}

}
