#include "process/timer_process.h"
extern bool* timer_start_flag;
extern bool* timer_flag;
extern bool* timer_counter;
void reset_timer_on_relay(byte _timer_number)
{
  timer_start_flag[_timer_number] = 0;
  timer_flag[_timer_number] = 0;
}
void timer_on_relay(byte _timer_number, uint32_t delay_time, bool _command)
{
  if (!timer_start_flag[_timer_number])
  {
    timer_counter[_timer_number] = millis();
    timer_start_flag[_timer_number] = 1;
  }
  if (timer_start_flag[_timer_number])
  {
    if (millis() - timer_counter[_timer_number] > delay_time)
    {
      timer_flag[_timer_number] = 1;
    }
    else
    {
      timer_flag[_timer_number] = 0;
    }
  }
}