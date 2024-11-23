/*
 * System_FSM.c
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */


#include "System_FSM.h"

int default_redlight;
int default_yellowlight;
int default_greenlight;
void SystemFSM(){
	switch(status){
		case INIT:
			if(is_button_pressed(0)){
				button1_press = 1;
			}
			if(!is_button_pressed(0) && button1_press){
				status = MODE1_NORMAL;
				setTimer(100, 0);
				setTimer(100, 1);
				// set default status for traffic light fsm
				TL1 = RED;
				TL2 = GREEN;

				// set default value time for traffic light fsm
				default_redlight = redlight;
				default_yellowlight = yellowlight;
				default_greenlight = greenlight;

				Red1 = default_redlight;
				Green2 = default_greenlight;
				button1_press=0;
			}
			break;
		case MODE1_NORMAL:
			TrafficLightFSM1();
			TrafficLightFSM2();
			// press and release
			if(is_button_pressed(0)){
				button1_press = 1;
			}
			if(!is_button_pressed(0) && button1_press){
				status = MODE2_MANRED;
				setTimer(50, 3);
				button1_press = 0;
			}
			break;
		case MODE2_MANRED:
			// red led blinking 2HZ
			if(flag[3] == 1){
				setTimer(50, 3);
				HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
				HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
			}
			// 2 7SEG display value
			Updatebuffer(redlight, 1);
			// 2 7SEG display mode
			Updatebuffer(MODE2_MANRED, 2);
			// if button2 is pressed and released after that
			// increasing value by 1
			if(is_button_pressed(1)){
				button2_press = 1;
			}
			if(!is_button_pressed(1) && button2_press){
				redlight++;
				greenlight++;
				button2_press = 0;
			}
			// if button2 is pressed long 1s
			if(is_button_pressed_1s(1)){
				if(button2_first_press1s){
					setTimer(50, 4);
					button2_first_press1s = 0;
				}
				if(flag[4] == 1){
					setTimer(50, 4);
					redlight++;
					greenlight++;
				}
			}
			// if button3 is pressed, turn back to mode 1 normal
			if(is_button_pressed(2)){
				button3_press = 1;
			}
			if(!is_button_pressed(2) && button3_press){
				status = MODE1_NORMAL;
				// set timer for traffic light
				setTimer(100, 0);
				setTimer(100, 1);

				redlight = default_redlight;
				yellowlight = default_yellowlight;
				greenlight = default_greenlight;

				// turn off traffic light
				HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
				HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
				button3_press = 0;
			}
			// if button1 is pressed, go to next status
			if(is_button_pressed(0)){
				button1_press = 1;
			}
			if(!is_button_pressed(0) && button1_press){
				status = MODE3_MANYELLOW;
				// set timer for blinking led
				setTimer(50, 3);
				// turn off traffic light
				HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
				HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
				button1_press = 0;
			}
			break;
		case MODE3_MANYELLOW:
			// red led blinking 2HZ
			if(flag[3] == 1){
				setTimer(50, 3);
				HAL_GPIO_TogglePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin);
				HAL_GPIO_TogglePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin);
			}
			// 2 7SEG display value
			Updatebuffer(yellowlight, 1);
			// 2 7SEG display mode
			Updatebuffer(MODE3_MANYELLOW, 2);
			// if button2 is pressed and released after that
			// increasing value by 1
			if(is_button_pressed(1)){
				button2_press = 1;
			}
			if(!is_button_pressed(1) && button2_press){
				yellowlight++;
				greenlight++;
				button2_press = 0;
			}
			// if button2 is pressed long 1s
			if(is_button_pressed_1s(1)){
				if(button2_first_press1s){
					setTimer(50, 4);
					button2_first_press1s = 0;
				}
				if(flag[4] == 1){
					setTimer(50, 4);
					yellowlight++;
					greenlight++;
				}
			}
			// if button3 is pressed, turn back to mode 1 normal
			if(is_button_pressed(2)){
				button3_press = 1;
			}
			if(!is_button_pressed(2) && button3_press){
				status = MODE1_NORMAL;
				// set timer for traffic light
				setTimer(100, 0);
				setTimer(100, 1);

				redlight = default_redlight;
				yellowlight = default_yellowlight;
				greenlight = default_greenlight;

				// turn off traffic light
				HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
				HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
				button3_press = 0;
			}
			// if button1 is pressed, go to next status
			if(is_button_pressed(0)){
				button1_press = 1;
			}
			if(!is_button_pressed(0) && button1_press){
				status = MODE4_MANGREEN;
				// set timer for blinking led
				setTimer(50, 3);
				// turn off traffic light
				HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
				HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
				button1_press = 0;
			}
			break;
		case MODE4_MANGREEN:
			// red led blinking 2HZ
			if(flag[3] == 1){
				setTimer(50, 3);
				HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
				HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
			}
			// 2 7SEG display value
			Updatebuffer(greenlight, 1);
			// 2 7SEG display mode
			Updatebuffer(MODE4_MANGREEN, 2);
			// if button2 is pressed and released after that
			// increasing value by 1
			if(is_button_pressed(1)){
				button2_press = 1;
			}
			if(!is_button_pressed(1) && button2_press){
				greenlight++;
				redlight++;
				button2_press = 0;
			}
			// if button2 is pressed long 1s
			if(is_button_pressed_1s(1)){
				if(button2_first_press1s){
					setTimer(50, 4);
					button2_first_press1s = 0;
				}
				if(flag[4] == 1){
					setTimer(50, 4);
					greenlight++;
					redlight++;
				}
			}
			// if button3 is pressed, turn back to mode 1 normal
			if(is_button_pressed(2)){
				button3_press = 1;
			}
			if(!is_button_pressed(2) && button3_press){
				status = MODE1_NORMAL;
				// set timer for traffic light
				setTimer(100, 0);
				setTimer(100, 1);

				redlight = default_redlight;
				yellowlight = default_yellowlight;
				greenlight = default_greenlight;

				// turn off traffic light
				HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
				HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
				button3_press = 0;
			}
			// if button1 is pressed, go to next status
			if(is_button_pressed(0)){
				button1_press = 1;
			}
			if(!is_button_pressed(0) && button1_press){
				status = MODE1_NORMAL;
				// set timer for traffic light
				setTimer(100, 0);
				setTimer(100, 1);
				// turn off traffic light
				HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
				HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
				button1_press = 0;
			}
			break;
		default:
			break;
	}
}
