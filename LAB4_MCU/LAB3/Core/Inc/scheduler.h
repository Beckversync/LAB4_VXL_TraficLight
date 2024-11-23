/*
 * scheduler.h
 *
 *  Created on: Nov 23, 2024
 *      Author: Dell
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"

#define SCH_MAX_TASK 10

typedef struct
{
	void (*pTask)();
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

void SCH_Init();
void SCH_Update();
uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period);	// 1 time unit = 1 microsecond
uint8_t SCH_Delete(uint32_t taskID);
void SCH_Dispatch_Tasks();
uint32_t get_time();

#endif /* INC_SCHEDULER_H_ */
