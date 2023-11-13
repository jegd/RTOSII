/*
 * OA_BTN.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Compumax
 */

#include "OA_BTN.h"

volatile uint32_t RisingUp_Time = 0;
volatile uint32_t FallingDown_Time = 0;
volatile int32_t BtnPressed_Time = 0;
bool flag = 0;
enum Btn_Status Btn_State;
BaseType_t sd;
QueueHandle_t QueueBtnStatus;
uint32_t aux = 0;
const char *OABTN_WelcomeMsg = "OA_BTN se está ejecutando\r\n";
const char *debug1 = "entre a la IRQ\r\n";
const char *debug2 = "entre a la SET\r\n";
const char *debug3 = "entre a la RESET\r\n";

#define SHORTPRESSEDMsg  "SHORTPRESSED\r\n"
#define LONGPRESSEDMsg   "LONGPRESSED\r\n"
#define BLOCKEDMsg       "BLOCKED\r\n"
#define UNBLOCKEDMsg     "UNBLOCKED\r\n"
#define NONEMsg          "NONE\r\n"

static const char *messages[]={SHORTPRESSEDMsg,LONGPRESSEDMsg,BLOCKEDMsg,UNBLOCKEDMsg,NONEMsg};

bool down_flag = 0;				//Flag que indica que hubo flanco ascendente
// Interrupción
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	aux = HAL_GetTick() / portTICK_PERIOD_MS; //guardo el tiempo en el que se llama al callback
	if (eboard_switch()) {
		//vPrintString( debug2 );
		RisingUp_Time = aux;
		down_flag = 0;
		FallingDown_Time = 0;
	} else if (!eboard_switch()) {
		//vPrintString( debug2 );
		FallingDown_Time = aux;
		down_flag = 1;
	}
}

static void resetear_parametros(void) {
	RisingUp_Time = 0; //Reseteo el contador de tiempo del rising edge
	FallingDown_Time = 0;
	BtnPressed_Time = 0;
	down_flag = 0;
	vPrintString(messages[Btn_State]);
	if (Btn_State != BLOCKED)
		Btn_State = NONE;
	else
		Btn_State = UNBLOCKED;
}

//Tarea objeto activo
void vTask_OA_BTN(void *pvParameters) {
	vPrintString(OABTN_WelcomeMsg);
	while (1) {

		if (down_flag)
			BtnPressed_Time = FallingDown_Time - RisingUp_Time;

		switch (Btn_State) {
		case SHORTPRESSED:
			resetear_parametros();
			break;
		case LONGPRESSED:
			resetear_parametros();
			break;
		case BLOCKED:
			if (down_flag)
				resetear_parametros();
			break;
		case UNBLOCKED:
			resetear_parametros();
			break;
		case NONE:
			if (100 < BtnPressed_Time && BtnPressed_Time < 2000)
				Btn_State = SHORTPRESSED;

			else if (2000 < BtnPressed_Time && BtnPressed_Time < 8000)
				Btn_State = LONGPRESSED;

			else if (RisingUp_Time != 0
					&& ((HAL_GetTick() / portTICK_PERIOD_MS - RisingUp_Time)
							>= 8000))
				Btn_State = BLOCKED;
			break;
		default:
			Btn_State = NONE;
			break;

		}

		sd = xQueueSend(QueueBtnStatus, &Btn_State, portMAX_DELAY);
		assert(sd != 0); // revisar que el mensaje se halla encolado correctamente.
	}
}

