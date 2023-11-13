#include "OA_LEDS.h"

#define SHORTPRESSEDMsg  "SHORTPRESSED\r\n"
#define LONGPRESSEDMsg   "LONGPRESSED\r\n"
#define BLOCKEDMsg       "BLOCKED\r\n"
#define UNBLOCKEDMsg     "UNBLOCKED\r\n"
#define NONEMsg          "NONE\r\n"

static const char *messages[]={SHORTPRESSEDMsg,LONGPRESSEDMsg,BLOCKEDMsg,UNBLOCKEDMsg,NONEMsg};

void vTask_OA_LEDS(void *pvParameters) {

	BaseType_t rv;
	enum Btn_Status Received;
	const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000UL);
	while (1) {
		rv = xQueueReceive(QueueBtnStatus, &Received, xDelay10000ms);
		configASSERT(&rv != NULL);
		if(Received<0 &&Received>4) configASSERT(FALSE);
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
			//acción
			break;
		default:
			eboard_led_green(false);
			eboard_led_red(false);
			break;

		}
	}
}
