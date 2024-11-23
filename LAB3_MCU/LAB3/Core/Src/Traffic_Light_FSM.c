/*
 * Traffic_Light_FSM.c
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */

#include "Traffic_Light_FSM.h"

void TrafficLightFSM1(){
	switch(TL1){
		case RED:
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
			Updatebuffer(Red1, 1);

			if(flag[0] == 1){
				setTimer(100, 0);
				Red1--;
				if(Red1 < 0){
					TL1 = GREEN;
					Green1 = greenlight;
				}
			}
			break;
		case GREEN:
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, RESET);
			Updatebuffer(Green1, 1);

			if(flag[0] == 1){
				setTimer(100, 0);
				Green1--;
				if(Green1 < 0){
					TL1 = YELLOW;
					Yellow1 = yellowlight;
				}
			}
			break;
		case YELLOW:
			HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, RESET);
			HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
			Updatebuffer(Yellow1, 1);

			if(flag[0] == 1){
				setTimer(100, 0);
				Yellow1--;
				if(Yellow1 < 0){
					TL1 = RED;
					Red1 = redlight;
				}
			}
			break;
		default:
			break;
	}
}

void TrafficLightFSM2(){
	switch(TL2){
		case RED:
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
			Updatebuffer(Red2, 2);

			if(flag[1] == 1){
				setTimer(100, 1);
				Red2--;
				if(Red2 < 0){
					TL2 = GREEN;
					Green2 = greenlight;
				}
			}
			break;
		case GREEN:
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, RESET);
			Updatebuffer(Green2, 2);

			if(flag[1] == 1){
				setTimer(100, 1);
				Green2--;
				if(Green2 < 0){
					TL2 = YELLOW;
					Yellow2 = yellowlight;
				}
			}
			break;
		case YELLOW:
			HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, RESET);
			HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, SET);
			Updatebuffer(Yellow2, 2);

			if(flag[1] == 1){
				setTimer(100, 1);
				Yellow2--;
				if(Yellow2 < 0){
					TL2 = RED;
					Red2 = redlight;
				}
			}
			break;
		default:
			break;
	}
}
