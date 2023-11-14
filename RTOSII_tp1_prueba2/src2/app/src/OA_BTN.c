/** @file OA_BTN.c
 *  @Created on: Nov 12, 2023
 *  @Authors:  Edda     Andrade                N°SIU e2014
 *             Anthony  Maisincho              N°SIU e2011
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
enum Btn_Status Btn_State; //Estado del botón.
BaseType_t sd; //Variable para verificar el correcto encolado de la notificación
/****************************VARIABLES INTERNAS****************************/
static bool rising_flag = 0;       //Flag que indica que hubo flanco ascendente.
static uint32_t aux = 0;                          //Marcador auxiliar de tiempo.

// INTERRUPCIÓN
/*!
 * @brief Función que maneja por interrupción el botón de la tarjeta de desarrollo
 *        detecta el flanco de subida y el flanco de bajada.
 *
 * @param[uint16_t] GPIO_Pin  Número de pin del GPIO de interrupción .
 *
 * @return Función del tipo void.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	aux = HAL_GetTick() / portTICK_PERIOD_MS; //Guarda el tiempo en el que se llama al callback.
	if (eboard_switch()) {
		RisingUp_Time = aux;
		rising_flag = 0;
		FallingDown_Time = 0;
	} else if (!eboard_switch()) {
		FallingDown_Time = aux;
		rising_flag = 1;
	}
}
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
	BtnPressed_Time = 0;
	rising_flag = 0;
	vPrintString(messages[Btn_State]); //Envío de mensaje por UART del estado del botón
	if (Btn_State != BLOCKED)
		Btn_State = NONE;
	else
		Btn_State = UNBLOCKED;
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
	while (1) {

		/*
		 * La resta que determina el tiempo que llevó presionado el botón se realiza
		 * cuando se ha detectado un flanco ascendete del botón de usuario.
		 */
		if (rising_flag)
			BtnPressed_Time = FallingDown_Time - RisingUp_Time;

		/*
		 * Procesado del estado del botón de usuario
		 *
		 * SHORPRESSED: El botón fue presionado entre 100 y 2000 ms.
		 * LONGPRESSED: El botón fue presionado entre 2000 y 8000 ms.
		 * BLOCKED: El botón se mantuvo presionado más de 8000 ms.
		 * UNBLOCKED: El botón estuvo en estado BLOCKED y posteriormente se liberó.
		 * NONE: El botón no fue presionado.
		 */
		switch (Btn_State) {
		case SHORTPRESSED:
			resetear_parametros();
			break;
		case LONGPRESSED:
			resetear_parametros();
			break;
		case BLOCKED:
			if (rising_flag)
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
		/*
		 * Se encola la notificación del estado del botón
		 * objeto activo para ser leída por el objeto activo led.
		 */
		sd = xQueueSend(QueueBtnStatus, &Btn_State, portMAX_DELAY);
		//Revisar que el mensaje se halla encolado correctamente.
		assert(sd != 0);
	}
}

