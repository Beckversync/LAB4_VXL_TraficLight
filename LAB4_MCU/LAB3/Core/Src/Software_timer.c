/*
 * Software_timer.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Dell
 */


#include "software_timer.h"



int timer_counter[NUM_TIMER] = {0};
int timer_flag[NUM_TIMER] = {0};
int timer_duration[NUM_TIMER] = {1000, 250, 0, 0};

void setTimer(int duration, int index){
	timer_counter[index] = duration / TIME_CYCLE;
	timer_flag[index] = 0;
}

void timerRun(){
	for (int i = 0; i < NUM_TIMER; i++){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
