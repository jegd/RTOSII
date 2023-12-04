/*
 *  OA_SYS.h
 *
 *  @Created on: Dic 03, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 */

#ifndef APP_INC_OA_SYS_H_
#define APP_INC_OA_SYS_H_

/****************************INCLUDES****************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "OA_BTN.h"
#include "main.h"
#include "cmsis_os.h"
#include "eboard.h"
#include "supporting_Functions.h"
/****************************DEFINES Y MACROS****************************/
typedef enum{
	GREEN_ON,
	RED_ON,
	GREEN_OFF,
	RED_OFF,
	BOTH_ON,
	BOTH_OFF
} codigo_t;
/****************************FUNCIONES****************************/
void vTask_OA_SYS(void *pvParameters);

#endif /* APP_INC_OA_SYS_H_ */
