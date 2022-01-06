/*
 * traffic_light_functions.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Rouen de la O
 */

#ifndef INC_TRAFFIC_LIGHT_FUNCTIONS_H_
#define INC_TRAFFIC_LIGHT_FUNCTIONS_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"

typedef enum TL_STATES { TL_SMStart, TL_off, TL_stop, TL_warn, TL_go } TL_STATE;

typedef struct TL_TaskDatas {
	unsigned int* enable; // enable or disable the Traffic Light FSM
	TL_STATE* TL_State;
	unsigned int* pedestrian;
} TL_TaskData;

typedef enum B_STATES { B_SMStart, B_off_pressed, B_on_pressed, B_off_released, B_on_released } B_STATE;

typedef struct B_TaskDatas {
	unsigned int* button_output;
	unsigned int* button_input;
	B_STATE* B_State;
} B_TaskData;

void trafficLight (TL_TaskData tl_taskData);

void button(B_TaskData b_task_data);

// function declaration for an FSM that transitions from illuminating a red LED
// PL2 to green LED PL4 back to red LED PL2. When a circle (button 1) is pressed, yellow
// a yellow circle is displayed before the red circle. In addition, there is
// another circle (button) 2 which functions as the enable-button to this FSM.
TL_TaskData initialize_TLstruct(TL_STATE* tl_state, unsigned int* givenEnabler, unsigned int* givenPedestrian);

B_TaskData initialize_Bstruct(unsigned int* output, unsigned int* input, B_STATE* B_State);

#endif /* INC_TRAFFIC_LIGHT_FUNCTIONS_H_ */

