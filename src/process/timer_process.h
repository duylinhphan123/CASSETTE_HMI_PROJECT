#ifndef _TIMER_PROCESS_H_
#define _TIMER_PROCESS_H_
#include <Arduino.h>
void reset_timer_on_relay(byte _timer_number);
void timer_on_relay(byte _timer_number, uint32_t delay_time, bool _command);
#endif
