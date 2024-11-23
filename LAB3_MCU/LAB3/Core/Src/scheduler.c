/*
 * scheduler.c
 *
 *  Created on: Nov 01, 2024
 *      Author: Dell
 */

#include "scheduler.h"

#define TIME_CYCLE 10	// 10 miliseconds

// Timestamps
uint32_t timestamps;

// array of tasks
sTask SCH_Tasks_G[SCH_MAX_TASK];
uint8_t visited[SCH_MAX_TASK] = {0};
uint32_t NumsOfTask;

// Initial the scheduler
void SCH_Init()
{
    for (int i = 0; i < SCH_MAX_TASK; i++)
    {
        visited[i] = 0;
    }
    NumsOfTask = 0;
    timestamps = 0;
}

// Increase 1 time unit
void SCH_Update()
{
    timestamps = timestamps + 1;
    if (visited[0] != 0)
    {
        SCH_Tasks_G[0].Delay = SCH_Tasks_G[0].Delay - 1 * TIME_CYCLE;
        if (SCH_Tasks_G[0].Delay == 0)
        {
            SCH_Tasks_G[0].RunMe = 1;
        }
    }
}

// Add new task into array of task
uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period)
{
    // Check array is full
    if (NumsOfTask == SCH_MAX_TASK)
        return 0;

    // Add new task
    uint8_t success = 0;
    uint32_t curTime = 0;
    uint32_t task;
    for (task = 0; task < NumsOfTask; task++)
    {
        if (curTime <= Delay)
        {
            curTime = curTime + SCH_Tasks_G[task].Delay;
        }

        if (curTime > Delay)
        {
            Delay = Delay - (curTime - SCH_Tasks_G[task].Delay);
            success = 1;
            break;
        }
    }
    if (!success)
    {
        Delay = Delay - curTime;
        success = 1;
    }

    // Shift right the task 1 unit
    sTask curTask = SCH_Tasks_G[task];
    curTask.Delay = curTask.Delay - Delay;
    for (uint32_t i = task; i < NumsOfTask; i++)
    {
        sTask tempTask = SCH_Tasks_G[i + 1];
        SCH_Tasks_G[i + 1] = curTask;
        SCH_Tasks_G[i + 1].TaskID = SCH_Tasks_G[i + 1].TaskID + 1; // update TaskID
        curTask = tempTask;
    }

    // Add new task with new Delay into the list
    SCH_Tasks_G[task].pTask = pFunction;
    SCH_Tasks_G[task].Delay = Delay;
    SCH_Tasks_G[task].Period = Period;
    SCH_Tasks_G[task].RunMe = 0;
    SCH_Tasks_G[task].TaskID = task;

    // Update status of the array of task
    NumsOfTask = NumsOfTask + 1;
    success = 1;
    visited[NumsOfTask - 1] = 1;

    return success;
}

// Delete task from array of task
uint8_t SCH_Delete(uint32_t TaskID)
{
    uint8_t success = 0;
    // Check TaskID is correct, array of task is empty
    if (TaskID >= NumsOfTask || NumsOfTask == 0)
        return 0;

    // Calculate Delay for all tasks after that and shift left them
    uint32_t Delay = SCH_Tasks_G[TaskID].Delay;
    for (uint32_t task = TaskID; task < NumsOfTask - 1; task++)
    {
        SCH_Tasks_G[task] = SCH_Tasks_G[task + 1];
        SCH_Tasks_G[task].TaskID = SCH_Tasks_G[task].TaskID - 1;
        SCH_Tasks_G[task].Delay = SCH_Tasks_G[task].Delay + Delay;
    }
    success = 1;
    NumsOfTask = NumsOfTask - 1;
    visited[NumsOfTask] = 0;

    return success;
}

// Run the task in the array of task
void SCH_Dispatch_Tasks()
{
	if (NumsOfTask == 0)
		return;
    while (SCH_Tasks_G[0].RunMe == 1 || SCH_Tasks_G[0].Delay == 0)
    {
        // Run the task
        (*SCH_Tasks_G[0].pTask)();
        sTask tempTask = SCH_Tasks_G[0];
        SCH_Delete(tempTask.TaskID);
        if (tempTask.Period != 0)
        {
            // Add this task into array again
            SCH_Add_Task(tempTask.pTask, tempTask.Period, tempTask.Period);
        }
    }
}

// Get timestamps
uint32_t get_time()
{
	return timestamps;
}


