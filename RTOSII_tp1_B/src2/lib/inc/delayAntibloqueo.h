/*
 * delayAntibloqueo.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Jesus
 */

#ifndef APP_INC_DELAYANTIBLOQUEO_H_
#define APP_INC_DELAYANTIBLOQUEO_H_

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "eboard.h"
#include "stm32f4xx_hal.h"
typedef bool bool_t;
typedef uint32_t tick_t;
//DELAY no bloqueante
typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;
//Maquina de estados de botón
typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING
} debounceState_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
void debounceFSM_init(debounceState_t * estado);		// debe cargar el estado inicial
void debounceFSM_update(debounceState_t * estado);	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED3

#endif /* APP_INC_DELAYANTIBLOQUEO_H_ */
