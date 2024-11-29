/*
 * global.h
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "input_reading.h"
#include "Traffic_Light_FSM.h"
#include "System_FSM.h"
#include "scheduler.h"
#include "software_timer.h"
#include <stdio.h>

#define TIME_CYCLE	10
#define NUM_TIMER	4

//global init and off status
#define	INIT		10
#define OFF			0

//MODE OF SYSTEM
#define AUTO_MODE 	1
#define MANUAL_MODE 2
#define TUNING_MODE 3
#define ERROR_MODE	4
//STATE for AUTO / MANUAL SETTING
#define	RED_GREEN	1
#define	RED_AMBER	2
#define	GREEN_RED	3
#define	AMBER_RED	4

//STATE for TUNING SETTING
#define	RED_ADJ		1
#define AMBER_ADJ	2
#define GREEN_ADJ	3

extern int timeRed;
extern int timeAmber;
extern int timeGreen;


//String use for UART
extern char str[];

extern UART_HandleTypeDef huart2;


//Variable use for FSM
extern int autoStatus;
extern int manualStatus;
extern int tuningStatus;

// Variable use UART
extern uint8_t index_buffer;
#define MAX_BUFFER_SIZE 30
extern uint8_t buffer[MAX_BUFFER_SIZE];


#endif /* INC_GLOBAL_H_ */
