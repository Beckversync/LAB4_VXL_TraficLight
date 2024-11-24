/*
 * System_FSM.c
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */


#include "System_FSM.h"

// Trạng thái chính
int trafficMode = INIT;
int autoStatus = INIT;
int manualStatus = OFF;
int tuningStatus = OFF;

// Bộ đếm thời gian cho từng hướng
int clock_counter_main = 0;
int clock_counter_side = 0;

// Thời gian mỗi đèn trong chế độ tự động
int timeRed = 5;
int timeAmber = 2;
int timeGreen = 3;


// ======================= CHẾ ĐỘ TỰ ĐỘNG =======================


void switchAutoState(int newState, int mainTime, int sideTime) {
    autoStatus = newState;
    clock_counter_main = mainTime;
    clock_counter_side = sideTime;
    clearRoadLed();
}

void fsm_traffic_auto_mode(void) {
    switch (autoStatus) {
        case OFF:
            break; // Không làm gì
        case INIT:
            switchAutoState(RED_GREEN, timeRed, timeGreen);
            break;
        case RED_GREEN:
            turnOnRed(0);
            turnOnGreen(1);
            if (clock_counter_side == 0)
                switchAutoState(RED_AMBER, clock_counter_main, timeAmber);
            break;
        case RED_AMBER:
            turnOnRed(0);
            turnOnAmber(1);
            if (clock_counter_side == 0)
                switchAutoState(GREEN_RED, timeGreen, timeRed);
            break;
        case GREEN_RED:
            turnOnGreen(0);
            turnOnRed(1);
            if (clock_counter_main == 0)
                switchAutoState(AMBER_RED, timeAmber, clock_counter_side);
            break;
        case AMBER_RED:
            turnOnAmber(0);
            turnOnRed(1);
            if (clock_counter_main == 0)
                switchAutoState(RED_GREEN, timeRed, timeGreen);
            break;
        default:
            break;
    }
}


// ======================= CHẾ ĐỘ TINH CHỈNH =======================
void logNewTime(){
	if (tuningStatus == RED_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER RED :%d#\r\n",timeRed),500);
	if (tuningStatus == AMBER_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER AMBER :%d#\r\n",timeAmber),500);
	if (tuningStatus == GREEN_ADJ) HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER GREEN :%d#\r\n",timeGreen),500);
}
int initialTimeRed = 5;
int initialTimeAmber = 2;
int initialTimeGreen = 3;
void fsm_traffic_tunning_mode(void){
	switch(tuningStatus){
	case OFF:
		// do nothing
	case INIT:
		tuningStatus = RED_ADJ;
		clearRoadLed();
		logNewTime();
		setTimer(timer_duration[1], 1);
		break;
	case RED_ADJ:
		blinkyRed();
		if (isButtonShortPress(2)){
            timeRed = (timeRed + 1) % 100;
            logNewTime();

		}
		else if (isButtonLongPress(2)){
            timeRed = (timeRed - 1 + 100) % 100;
            logNewTime();
		}
		else if (isButtonShortPress(1)){
			tuningStatus = GREEN_ADJ;
			clearRoadLed();
			logNewTime();
		}
        else if(isButtonShortPress(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();  // Tắt tất cả đèn
        }
		break;
	case GREEN_ADJ:
		blinkyGreen();
		if(isButtonShortPress(2)){
            timeGreen = (timeGreen + 1) % 100;
            logNewTime();;
		}
		else if(isButtonLongPress(2)){
            timeGreen = (timeGreen - 1 + 100) % 100;
            logNewTime();
		}
		else if(isButtonShortPress(1)){
			tuningStatus = AMBER_ADJ;
			clearRoadLed();
			logNewTime();
		}
        else if(isButtonShortPress(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();  // Tắt tất cả đèn
        }
		break;
	case AMBER_ADJ:
		blinkyAmber();
		if (isButtonShortPress(2)){
            timeAmber = (timeAmber + 1) % 100;
            logNewTime();
		}
		else if(isButtonLongPress(2)){
            timeAmber = (timeAmber - 1 + 100) % 100;
            logNewTime();
		}
		else if (isButtonShortPress(1)){
			tuningStatus = RED_ADJ;
			clearRoadLed();
			logNewTime();
		}
        else if(isButtonShortPress(0)){
            // Đặt lại tất cả các đèn về thời gian ban đầu khi ấn nút 1
            timeRed = initialTimeRed;
            timeAmber = initialTimeAmber;
            timeGreen = initialTimeGreen;
            logNewTime();  // Gửi thông tin thời gian mới
            tuningStatus = GREEN_ADJ;  // Giữ trạng thái GREEN_ADJ
            clearRoadLed();  // Tắt tất cả đèn
        }
		break;

	default:
		break;
	}
}
// ======================= CHUYỂN ĐỔI CHẾ ĐỘ =======================
void fsm_switch_mode(void){
	if (isButtonLongPress(0)){
		if (trafficMode != MANUAL_MODE) {
			trafficMode = MANUAL_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO MANUAL MODE#\r\n"),500);
			// TODO: prepare for manual mode
			manualStatus = INIT;
			autoStatus= OFF;
			tuningStatus = OFF;
		}
		else {
			trafficMode = INIT;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO AUTO MODE#\r\n"),500);

		}
	}
	else if (isButtonLongPress(1)){
		if (trafficMode != TUNING_MODE) {
			trafficMode = TUNING_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO TUNING MODE#\r\n"),500);
			// TODO: prepare for next mode
			tuningStatus = INIT;
			autoStatus = OFF;
			manualStatus = OFF;
		}
		else {
			trafficMode = INIT;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!SWITCH TO AUTO MODE#\r\n"),500);
		}
	}
}
// ======================= VÒNG LẶP CHÍNH =======================
void fsm_traffic(void){
	switch(trafficMode){
	case INIT:
		if (timeRed != (timeAmber + timeGreen)){
			trafficMode = ERROR_MODE;
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!TIMER ERROR#\r\n"),500);
			autoStatus = OFF;
			manualStatus = OFF;
			tuningStatus = OFF;
		}
		else {
			trafficMode = AUTO_MODE;
			autoStatus = INIT;
			manualStatus = OFF;
			tuningStatus = OFF;
			setTimer(timer_duration[0], 0);
		}
		turnOffAllLED();
		break;
	case AUTO_MODE:

		fsm_traffic_auto_mode();
		break;
	case TUNING_MODE:
		fsm_traffic_tunning_mode();
		break;
	default:
		break;
	}
}

void clock_counter_traffic_update(void){
	if((timer_flag[0] == 1) && (trafficMode == AUTO_MODE)){
		clock_counter_main--;
		clock_counter_side--;
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\n!7SEG WAY1:%d#\r\n",clock_counter_main),500);
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG WAY2:%d#\r\n",clock_counter_side),500);

		setTimer(timer_duration[0], 0);
	}
}
