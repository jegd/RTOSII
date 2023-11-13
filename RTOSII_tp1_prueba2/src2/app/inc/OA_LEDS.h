/*
 * OA_LEDS.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Compumax
 */

#ifndef APP_INC_OA_LEDS_H_
#define APP_INC_OA_LEDS_H_

#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "eboard.h"
#include "supporting_Functions.h"

#include "app.h"
#include "OA_BTN.h"

extern void vTask_OA_LEDS(void *pvParameters);

#endif /* APP_INC_OA_LEDS_H_ */
