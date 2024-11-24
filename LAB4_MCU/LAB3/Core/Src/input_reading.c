/*
 * button.c
 *
 *  Created on: Nov 1, 2023
 *      Author: DELL
 */
#include "input_reading.h"

struct keyget {
	int keyget1;
	int keyget2;
	int keyget3;
	int oldState;
	int shortPress;
	int longPress;
	int timePress;
};

struct keyget listButton[NUM_BUTTON] = {{RELEASE, RELEASE, RELEASE, RELEASE, 0, 0}};
GPIO_TypeDef * BUTTON_GPIO[NUM_BUTTON] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port};
uint16_t BUTTON_PIN[NUM_BUTTON] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin};

void getButtonValue(void) {
	for (int i = 0; i < NUM_BUTTON; i++){
		listButton[i].keyget1 = listButton[i].keyget2;
		listButton[i].keyget2 = listButton[i].keyget3;
		listButton[i].keyget3 = HAL_GPIO_ReadPin(BUTTON_GPIO[i], BUTTON_PIN[i]);
		if((listButton[i].keyget1 == listButton[i].keyget2) && (listButton[i].keyget2 == listButton[i].keyget3)){
			if (listButton[i].oldState != listButton[i].keyget3){
				listButton[i].oldState = listButton[i].keyget3;
				if (listButton[i].keyget3 == PRESSED){
					listButton[i].shortPress = 1;
					listButton[i].timePress = KEY_PRESS_TIME / TIME_CYCLE;
				}
				else if (listButton[i].keyget3 == RELEASE){
					// if new state != old state and button is released -> Short Press is complete
					 if(listButton[i].shortPress == 1) listButton[i].shortPress = 2;
				}
			}
			else if (listButton[i].keyget3 == PRESSED){
				listButton[i].timePress--;
				if (listButton[i].timePress == 0){
					listButton[i].longPress = 1;
					listButton[i].shortPress = 0; // When press time >= KEY_PRESS_TIME -> long press -> terminate short press
				}
			}
		}
	}
}



int isButtonShortPress(int index){
	if (listButton[index].shortPress == 2){
		listButton[index].shortPress = 0;
		return 1;
	}
	else return 0;
}

int isButtonLongPress(int index){
	if (listButton[index].longPress == 1){
		listButton[index].longPress = 0;
		return 1;
	}
	else return 0;
}
