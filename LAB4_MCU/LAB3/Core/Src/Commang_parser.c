/*
 * Commang_parser.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Dell
 */

#define INIT_STATE  	0
#define RST 	1
#define OK 	2



#include<Command_parser.h>
#include <stdint.h>


uint8_t state_command_parser_fsm = INIT_STATE;
uint8_t check_command(const char* cmd, uint8_t len) {
    uint8_t index_buffer_tem = (index_buffer == 0) ? MAX_BUFFER_SIZE - 1 : index_buffer - 1;

    for (uint8_t i = len - 1; ; i--) {
        if (buffer[index_buffer_tem] != cmd[i]) {
            return 0;
        }
        index_buffer_tem = (index_buffer_tem == 0) ? MAX_BUFFER_SIZE - 1 : index_buffer_tem - 1;
        if (i == 0) break;
    }

    return 1;
}

void command_parser_fsm() {
    switch (state_command_parser_fsm) {
    case INIT:
        state_command_parser_fsm = RST;
        break;

    case RST:
        if (check_command("RST", 4)) { // Kiểm tra lệnh "!RST#"
            read_traffictime = 1; // Đặt cờ thời gian
            state_command_parser_fsm = OK;
        }
        break;

    case OK:
        if (check_command("OK", 3)) { // Kiểm tra lệnh "!OK#"
            ok_flag = 1; // Đặt cờ OK
            state_command_parser_fsm = RST;
        } else if (check_command("RST", 4)) { // Kiểm tra lệnh "!RST#"
            read_traffictime = 1; // Đặt cờ thời gian
        }
        break;

    default:
        break;
    }
}
