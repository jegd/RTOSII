/*
 * OA_LEDS.h
 *
 *  @Created on: Dic 03, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 */

#ifndef APP_INC_OA_LEDS_H_
#define APP_INC_OA_LEDS_H_
/****************************INCLUDES****************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "cmsis_os.h"
#include "eboard.h"
#include "supporting_Functions.h"
#include "app.h"
#include "OA_BTN.h"
#include "OA_SYS.h"
/****************************FUNCIONES****************************/
void vTask_OA_LEDS(void *pvParameters);

#endif /* APP_INC_OA_LEDS_H_ */
