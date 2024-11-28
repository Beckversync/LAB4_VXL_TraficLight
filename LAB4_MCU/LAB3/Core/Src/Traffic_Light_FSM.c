/*
 * Traffic_Light_FSM.c
 *
 *  Created on: Oct 29, 2024
 *      Author: Dell
 */

#include "Traffic_Light_FSM.h"

// Common function to control LED states
void setLEDState(GPIO_PinState red, GPIO_PinState amber, GPIO_PinState green, int index) {
    if (index == 0) { // Way 1
        HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin, red);
        HAL_GPIO_WritePin(GPIOA, AMBER_LED1_Pin, amber);
        HAL_GPIO_WritePin(GPIOA, GREEN_LED1_Pin, green);
    } else if (index == 1) { // Way 2
        HAL_GPIO_WritePin(GPIOA, RED_LED2_Pin, red);
        HAL_GPIO_WritePin(GPIOA, AMBER_LED2_Pin, amber);
        HAL_GPIO_WritePin(GPIOA, GREEN_LED2_Pin, green);
    }
}

// Tắt toàn bộ LED
void turnOffAllLED(void) {
    HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |
                             AMBER_LED1_Pin | AMBER_LED2_Pin |
                             GREEN_LED1_Pin | GREEN_LED2_Pin, GPIO_PIN_SET);
}

// Bật toàn bộ LED
void turnOnAllLED(void) {
    HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin |
                             AMBER_LED1_Pin | AMBER_LED2_Pin |
                             GREEN_LED1_Pin | GREEN_LED2_Pin, GPIO_PIN_RESET);
}

// Bật đèn RED LED for specified way
void turnOnRed(int index) {
    setLEDState(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, index);
}

// Bật đèn AMBER LED for specified way
void turnOnAmber(int index) {
    setLEDState(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, index);
}

// Bật đènGREEN LED for specified way
void turnOnGreen(int index) {
    setLEDState(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET, index);
}

// Nhấp nháy LED RED LEDs
void blinkyRed(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Nhấp nháy LED AMBER LEDs
void blinkyAmber(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, AMBER_LED1_Pin | AMBER_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Nhấp nháy LED GREEN LEDs
void blinkyGreen(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, GREEN_LED1_Pin | GREEN_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Tắt đèn giao thông của tất cả các hướng
void clearRoadLed(void) {
    turnOffAllLED();
}
