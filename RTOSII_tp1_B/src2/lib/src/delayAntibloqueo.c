/*
 * delayAntibloqueo.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Jesus
 */

#include "delayAntibloqueo.h"

static delay_t delay_1;
static tick_t duracion_1=20;


void delayInit( delay_t * delay, tick_t duration ){
	assert(delay!= NULL);
 delay->duration= duration;
 delay->running=false;
}

bool_t delayRead( delay_t * delay ){

	assert(delay!= NULL);
	if((delay->running)==false ){
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	if(delay->running){
		if((HAL_GetTick()-(delay->startTime))>=delay->duration){
			delay->running = false;
		}
	}
return delay->running;

}
void delayWrite( delay_t * delay, tick_t duration ){
	assert(delay!= NULL);
	delay->duration = duration;
}

void debounceFSM_init(debounceState_t * estado){
	delayInit(&delay_1,duracion_1);
	assert(estado!=NULL);
	*estado=BUTTON_UP;
}

void debounceFSM_update(debounceState_t * estado){
	assert(estado!=NULL);
		switch(*estado)
		{
		case BUTTON_UP:
			if(eboard_switch())
				*estado=BUTTON_FALLING;

			break;
		case BUTTON_FALLING:
			if(!(delayRead(&delay_1)))
			{
				if(eboard_switch())
				{
					*estado=BUTTON_DOWN;
					//buttonPressed();
				}
				else{
					*estado=BUTTON_UP;
				}
			}
			break;
		case BUTTON_DOWN:
			if(!(eboard_switch()))
						*estado=BUTTON_RAISING;
			break;
		case BUTTON_RAISING:
			if(!(delayRead(&delay_1)))
					{
						if(!(eboard_switch()))
						{
							*estado=BUTTON_UP;
							//buttonReleased();
						}
						else{
							*estado=BUTTON_DOWN;
						}
					}
			break;
		default:
			debounceFSM_init(estado);
			break;

		}
}

