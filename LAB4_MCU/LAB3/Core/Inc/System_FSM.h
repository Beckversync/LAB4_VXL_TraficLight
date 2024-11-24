/*
 * System_FSM.h
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */

#ifndef INC_SYSTEM_FSM_H_
#define INC_SYSTEM_FSM_H_

#include "global.h"
#include <stdio.h>

void fsm_switch_mode(void);
void fsm_traffic(void);
void clock_counter_traffic_update(void);

#endif /* INC_SYSTEM_FSM_H_ */
