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

// Turn off all LEDs
void turnOffAllLED(void) {
    HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin | AMBER_LED1_Pin |
                      AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin, GPIO_PIN_SET);
}

// Turn on all LEDs
void turnOnAllLED(void) {
    HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin | AMBER_LED1_Pin |
                      AMBER_LED2_Pin | GREEN_LED1_Pin | GREEN_LED2_Pin, GPIO_PIN_RESET);
}

// Turn on RED LED for specified way
void turnOnRed(int index) {
    setLEDState(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, index);
}

// Turn on AMBER LED for specified way
void turnOnAmber(int index) {
    setLEDState(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, index);
}

// Turn on GREEN LED for specified way
void turnOnGreen(int index) {
    setLEDState(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET, index);
}

// Blink RED LEDs
void blinkyRed(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, RED_LED1_Pin | RED_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Blink AMBER LEDs
void blinkyAmber(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, AMBER_LED1_Pin | AMBER_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Blink GREEN LEDs
void blinkyGreen(void) {
    if (timer_flag[1] == 1) {
        HAL_GPIO_TogglePin(GPIOA, GREEN_LED1_Pin | GREEN_LED2_Pin);
        setTimer(timer_duration[1], 1);
    }
}

// Clear all road LEDs
void clearRoadLed(void) {
    turnOffAllLED();
}
