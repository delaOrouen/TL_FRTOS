/*

 * traffic_light_functions.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Rouen de la O
 */

#include "traffic_light_functions.h"


void trafficLight (TL_TaskData tl_taskData) {
   switch(*(tl_taskData.TL_State)) { // transitions
      case TL_SMStart:
    	  *(tl_taskData.TL_State) = TL_off;
         break;
      case TL_off:
         if (*(tl_taskData.enable)) {
        	 *(tl_taskData.TL_State) = TL_stop;
            break;
         }
         else {
        	 *(tl_taskData.TL_State) = TL_off;
            break;
         }
      case TL_stop:
         if (*(tl_taskData.enable)) {
        	 *(tl_taskData.TL_State) = TL_go;
            break;
         }
         else {
        	 *(tl_taskData.TL_State) = TL_off;
            break;
         }
      case TL_warn:
         if (!(*(tl_taskData.enable))) {
        	 *(tl_taskData.TL_State) = TL_off;
            break;
         }
         else {
        	 *(tl_taskData.TL_State) = TL_stop;
            break;
         }
      case TL_go:
         if (!(*(tl_taskData.enable))) {
        	 *(tl_taskData.TL_State) = TL_off;
            break;
         }
         else if (*(tl_taskData.pedestrian)) { // test if button PL1 was pressed
        	 *(tl_taskData.TL_State) = TL_warn;
            break;
         }
         else {
        	 *(tl_taskData.TL_State) = TL_stop;
            break;
         }
      default:
    	  *(tl_taskData.TL_State) = TL_SMStart;
         break;
   } // transitions

   switch(*(tl_taskData.TL_State)) { // state actions
      case TL_off:
    	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
    	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
         break;
      case TL_stop:
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
         break;
      case TL_warn:
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
         break;
      case TL_go:
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
         break;
      default:
         break;
   } // state actions
}



TL_TaskData initialize_TLstruct(TL_STATE* tl_state, unsigned int* givenEnabler, unsigned int* givenPedestrian) {
   TL_TaskData tl_taskData = {givenEnabler, tl_state, givenPedestrian};
	return tl_taskData;
}

// function declaration for an FSM that uses button presses to set and
// clear GPIO PL5
void button(B_TaskData b_task_data) {
   switch(*(b_task_data.B_State)) { // Transitions
      case B_SMStart: // Initial Transition
         *(b_task_data.B_State) = B_off_released;
         break;
      case B_off_released:
         if (*(b_task_data.button_input)) { // test if switch PL1 was pressed
            *(b_task_data.B_State) = B_on_pressed;
            break;
         }
         else {
        	 *(b_task_data.B_State) = B_off_released;
            break;
         }
      case B_on_pressed:
         if (!(*b_task_data.button_input)) { // test if switch PL1 was not pressed
            *(b_task_data.B_State) = B_on_released;
            break;
         }
         else {
            *(b_task_data.B_State) = B_on_pressed;
            break;
         }
      case B_on_released:
         if (*(b_task_data.button_input)){
            *(b_task_data.B_State) = B_off_pressed;
            break;
         }
         else {
        	*(b_task_data.B_State) = B_on_released;
            break;
         }
      case B_off_pressed:
         if (!(*b_task_data.button_input)) {
        	*(b_task_data.B_State) = B_off_released;
        	break;
         }
         else {
        	*(b_task_data.B_State) = B_off_pressed;
            break;
         }
      default:
    	 *(b_task_data.B_State) = B_SMStart;
         break;
   } // Transitions

      switch(*(b_task_data.B_State)) { // State actions
         case B_off_released:
            *(b_task_data.button_output) = 0;
            break;
         case B_on_pressed:
         	*(b_task_data.button_output) = 1;
            break;
         case B_on_released:
        	*(b_task_data.button_output) = 1;
            break;
         case B_off_pressed:
        	*(b_task_data.button_output) = 0;
            break;
         default:
            break;
      } // State actions
}

B_TaskData initialize_Bstruct(unsigned int* output, unsigned int* input, B_STATE* B_State) {
	B_TaskData b_taskdata = {output, input, B_State};
	return b_taskdata;
}
