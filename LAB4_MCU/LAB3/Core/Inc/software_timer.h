/*
 * software_timer.h
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "global.h"

//Variables use for timer
extern int timer_flag[];
extern int timer_duration[];
void setTimer(int duration, int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
