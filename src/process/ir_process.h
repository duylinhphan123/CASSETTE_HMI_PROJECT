#ifndef IR_COMMANDS_H_
#define IR_COMMANDS_H_
#include <Arduino.h>

void IR_PROGRAM();
bool IR_COMMAND(uint16_t _COMMAND);
void handleOverflow();
void get_ir_data();
void IR_BEGIN();
#endif

