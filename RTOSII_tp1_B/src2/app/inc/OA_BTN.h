/*
 *  OA_BTN.h
 *
 *  @Created on: Dic 03, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 */

#ifndef APP_INC_OA_BTN_H_
#define APP_INC_OA_BTN_H_

/****************************INCLUDES****************************/
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "eboard.h"
#include "supporting_Functions.h"
#include "delayAntibloqueo.h"
/****************************VARIABLES****************************/
extern volatile uint32_t RisingUp_Time; //Tick de tiempo en el que se produce el rising edge variable global pública y volátil (no optimizada)
extern volatile uint32_t FallingDown_Time; //Tick de tiempo en el que se produce el falling edge variable global pública y volátil (no optimizada)
extern enum Btn_Status Btn_State; //Estado del botón de usuario
extern QueueHandle_t QueueBtnStatus; //Cola para enviar el estado del botón a los leds
extern BaseType_t sd; //Variable para verificar el correcto encolado de la notificación
//Enumeración con los estados del botón
enum Btn_Status {
	SHORTPRESSED, LONGPRESSED, BLOCKED, UNBLOCKED, NONE
};
/****************************FUNCIONES****************************/
/*!
 * @brief Tarea del Objeto activo botón.
 *
 * @param[void *] Puntero a parámetros.
 *
 * @return Función del tipo void.
 */
extern void vTask_OA_BTN(void *pvParameters);

#endif /* APP_INC_OA_BTN_H_ */
