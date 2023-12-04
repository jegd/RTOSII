/** @file OA_BTN.c
 *  @Created on: Dic 03, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 *
 *  @brief Objeto activo que procesa la señal del botón de usuario
 *        y manda el estado del botón a una cola del objeto activo led.
 *
 */

/****************************INCLUDES****************************/
#include "OA_BTN.h"
/****************************DEFINES****************************/
#define SHORTPRESSEDMsg  "SHORTPRESSED\r\n"
#define LONGPRESSEDMsg   "LONGPRESSED\r\n"
#define BLOCKEDMsg       "BLOCKED\r\n"
#define UNBLOCKEDMsg     "UNBLOCKED\r\n"
#define NONEMsg          "NONE\r\n"
/****************************HANDLES****************************/
QueueHandle_t QueueBtnStatus;
/****************************VARIABLES GLOBALES****************************/
const char *messages[] = { SHORTPRESSEDMsg, LONGPRESSEDMsg, BLOCKEDMsg,
UNBLOCKEDMsg, NONEMsg }; //Vector de mensajes para los estados del botón
const char *OABTN_WelcomeMsg = "OA_BTN se está ejecutando\r\n"; //Mensaje de bienvenida.
volatile uint32_t RisingUp_Time = 0; //Marcador de tiempo del flanco de subida del botón.
volatile uint32_t FallingDown_Time = 0; //Marcador de tiempo del flanco de bajada del botón.
volatile int32_t BtnPressed_Time = 0; //Tiempo que el pulsador estuvo presionado.
enum Btn_Status Btn_State = NONE; //Estado del botón.
BaseType_t sd; //Variable para verificar el correcto encolado de la notificación
/****************************VARIABLES INTERNAS****************************/
static bool rising_flag = 0;       //Flag que indica que hubo flanco ascendente.
static uint32_t aux = 0;                          //Marcador auxiliar de tiempo.
debounceState_t boton;
bool unaVezBlockeado = 0;
bool buttonChange = 0;
/*!
 * @brief Función para resetear las variables de tiempo, flag de flanco descendente
 *        e escritura de mensaje por UART.
 *
 * @param[void]
 *
 * @return Función del tipo void.
 */
static void resetear_parametros(void) {
	RisingUp_Time = 0;
	FallingDown_Time = 0;
	if (Btn_State != BLOCKED)
		BtnPressed_Time = 0;
	rising_flag = 0;
	buttonChange = 0;
	Btn_State = NONE;
}
/*!
 * @brief Función para procesar el estado del botón.
 *
 * @param[enum Btn_Status] Estado del botón
 *
 * @return Función del tipo void.
 */
static void process_button_state(enum Btn_Status estadoButton) {
	switch (estadoButton) {
	case SHORTPRESSED:
		resetear_parametros();
		break;
	case LONGPRESSED:
		resetear_parametros();
		break;
	case BLOCKED:
		if (!rising_flag)
			resetear_parametros();
		buttonChange = 0;
		break;
	case UNBLOCKED:
		resetear_parametros();
		break;
	case NONE:
		if (100 < BtnPressed_Time && BtnPressed_Time < 2000) {
			Btn_State = SHORTPRESSED;
			buttonChange = 1;
		}

		else if (2000 < BtnPressed_Time && BtnPressed_Time < 8000) {
			Btn_State = LONGPRESSED;
			buttonChange = 1;
		} else if (BtnPressed_Time >= 8000) {
			buttonChange = 1;
			Btn_State = UNBLOCKED;
		} else if (RisingUp_Time != 0
				&& ((HAL_GetTick() / portTICK_PERIOD_MS - RisingUp_Time) >= 8000)) {
			buttonChange = 1;
			Btn_State = BLOCKED;
		}

		break;
	default:
		Btn_State = NONE;
		break;

	}
}

static void updateButton() {
	aux = HAL_GetTick() / portTICK_PERIOD_MS; //Guarda el tiempo en el que se llama al callback.
	debounceFSM_update(&boton);
	if (boton == BUTTON_DOWN && !rising_flag) {
		RisingUp_Time = aux;
		rising_flag = 1;
		FallingDown_Time = 0;
	} else if (boton == BUTTON_UP && rising_flag) {
		FallingDown_Time = aux;
		BtnPressed_Time = FallingDown_Time - RisingUp_Time;
		rising_flag = 0;
	}
}

//Tarea objeto activo botón
/*!
 * @brief Tarea del Objeto activo botón.
 *
 * @param[void *] Puntero a parámetros.
 *
 * @return Función del tipo void.
 */
void vTask_OA_BTN(void *pvParameters) {
	vPrintString(OABTN_WelcomeMsg);
	debounceFSM_init(&boton);
	while (1) {

		/*
		 * Actualiza el estado del botón
		 */
		updateButton();
		/*
		 * Procesado del estado del botón de usuario
		 *
		 * SHORPRESSED: El botón fue presionado entre 100 y 2000 ms.
		 * LONGPRESSED: El botón fue presionado entre 2000 y 8000 ms.
		 * BLOCKED: El botón se mantuvo presionado más de 8000 ms.
		 * UNBLOCKED: El botón estuvo en estado BLOCKED y posteriormente se liberó.
		 * NONE: El botón no fue presionado.
		 */
		process_button_state(Btn_State);
		/*
		 * Se encola la notificación del estado del botón
		 * objeto activo para ser leída por el objeto activo sys.
		 */
		if (Btn_State != NONE && buttonChange != 0) {
			sd = xQueueSend(QueueBtnStatus, &Btn_State, 0);
			assert(sd != 0); //Revisar que el mensaje se halla encolado correctamente.
		}

	}
}

