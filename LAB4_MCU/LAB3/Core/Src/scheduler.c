/*
 * scheduler.c
 *
 *  Created on: Nov 01, 2024
 *      Author: Dell
 */
#include "scheduler.h"
#include <stdlib.h>

struct sTask{
	void (* pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	struct sTask *next;
};

struct container {
	struct sTask *tail;
	int numSlot;
	int emptySlot;
};

struct container* container;


struct sTask* Add_Node(struct sTask** curr, void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    struct sTask *temp = (struct sTask*)malloc(sizeof(struct sTask));
    temp -> pTask = pFunction;
    temp -> Delay = DELAY;
    temp -> Period = PERIOD;
    if (curr == NULL || *curr == NULL) {
        temp -> next = temp;
    }
    else {
        temp -> next = (*curr) -> next;
    }
    return temp;
}

void SCH_Init(void) {
    container = (struct container*)malloc(sizeof(struct container));
	container -> tail = NULL;
	container -> numSlot = 0;
	container -> emptySlot = 0;
}

void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	// container empty
	if (container -> tail == NULL) {
		container -> tail = Add_Node(NULL, pFunction, DELAY, PERIOD);
		(container -> numSlot)++;
	}
	else {
		struct sTask* temp = container -> tail;
		uint32_t sumDelay = 0;
		uint32_t newDelay = 0;
		// find first task with bigger delay
		for (int i = 0; i < container -> numSlot; i++) {
			sumDelay = sumDelay + temp -> next -> Delay;
			// add head or middle
			if (sumDelay > DELAY) {
                // delay of new task
				newDelay = DELAY - (sumDelay - temp -> next -> Delay);
				temp -> next -> Delay = sumDelay - DELAY;
				// create new node if there is no empty slot
				if (container -> emptySlot == 0) {
					temp -> next = Add_Node(&temp, pFunction, newDelay, PERIOD);
					(container -> numSlot)++;
                }
				// if is, move tail to after temp and use it
				else {
					container -> tail -> pTask = pFunction;
					container -> tail -> Delay = newDelay;
					container -> tail -> Period = PERIOD;
					struct sTask *newTail = temp -> next;
					while (newTail -> next != container -> tail) {
						newTail = newTail -> next;
					}
					if (temp == container -> tail) container -> tail = newTail;
					else {
						newTail -> next = container -> tail -> next;
						container -> tail -> next = temp -> next;
						temp -> next = container -> tail;
						container -> tail = newTail;
					}
                    (container -> emptySlot)--;
				}
                break;
			} else {
				// add tail
                if (temp -> next -> pTask == 0x0000) {
					temp -> next -> pTask = pFunction;
					temp -> next -> Delay = DELAY - sumDelay;
					temp -> next -> Period = PERIOD;
                    (container -> emptySlot)--;
					break;
				}
				else {
					if (temp -> next == container -> tail) {
						container -> tail -> next = Add_Node(&(container -> tail), pFunction, DELAY - sumDelay, PERIOD);
						container -> tail = container -> tail -> next;
						(container -> numSlot)++;
						break;
					}
				}

			}
			temp = temp -> next;
		}
	}

}

void SCH_Delete_Task(struct sTask** preDel) {
    struct sTask* del = (*preDel) -> next;
    if (del != container -> tail) del -> next -> Delay += del -> Delay;
	del -> pTask = 0x0000;
	del -> Delay = 0;
	del -> Period = 0;
	if (*preDel == container -> tail)
		container -> tail = container -> tail -> next;
	else {
		if (del -> next -> pTask != 0 && del != container -> tail) {
			(*preDel) -> next = del -> next;
			del -> next = container -> tail -> next;
			container -> tail -> next = del;
			container -> tail = del;
		}
	}
	(container -> emptySlot)++;
}


void SCH_Update(void) {
	if (container -> tail) {
		if (container -> tail -> next -> Delay > 0)
			(container -> tail -> next -> Delay)--;
	}
}


void SCH_Dispatch_Tasks(void) {
	while (container -> tail -> next -> Delay <= 0) {
		(*(container -> tail -> next -> pTask))();
		struct sTask temp = *(container -> tail -> next);
		SCH_Delete_Task(&(container -> tail));
		if (temp.Period != 0) {
			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
		}
	}
}
