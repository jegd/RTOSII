/*
 * OA_SYS.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Jesus
 */

#ifndef APP_INC_OA_SYS_H_
#define APP_INC_OA_SYS_H_

#include "OA_BTN.h"
#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "eboard.h"
#include "supporting_Functions.h"
typedef enum {
	GREEN,
	RED
} color_led;

typedef enum{
	GREEN_ON,
	RED_ON,
	GREEN_OFF,
	RED_OFF,
	BOTH_ON,
	BOTH_OFF
} codigo_t;

typedef enum {
	OFF,
	ON
} estado_led;

void vTask_OA_SYS(void *pvParameters);

#endif /* APP_INC_OA_SYS_H_ */
