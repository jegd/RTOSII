/*
 * OA_BTN.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Compumax
 */

#ifndef APP_INC_OA_BTN_H_
#define APP_INC_OA_BTN_H_

#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "eboard.h"
#include "supporting_Functions.h"

#define R 1 //Rising Edge
#define F 0 //Falling Edge

extern volatile uint32_t RisingUp_Time; //tick de tiempo en el que se produce el rising edge variable global pública y volátil (no optimizada)
extern volatile uint32_t FallingDown_Time; //tick de tiempo en el que se produce el falling edge variable global pública y volátil (no optimizada)
extern enum Btn_Status Btn_State;




extern QueueHandle_t QueueBtnStatus; //cola para enviar el estado del botón a los leds
extern BaseType_t sd;

enum Btn_Status {
	SHORTPRESSED, LONGPRESSED, BLOCKED, UNBLOCKED, NONE
};

extern void vTask_OA_BTN(void *pvParameters);

#endif /* APP_INC_OA_BTN_H_ */
