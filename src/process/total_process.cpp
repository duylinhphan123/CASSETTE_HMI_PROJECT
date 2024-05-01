#include "process/total_process.h"
extern bool total_checked;
extern bool direction;
extern bool old_direction;
extern byte total_second;
extern byte total_minute;
extern byte total_hrs;
extern int32_t current_revolution;
extern int32_t last_revolution;
extern void (*sendtt)(byte*,byte*,byte*);
extern int TOTAL_ADDR;
extern void write_time_data_to_eeprom(byte* _hrs, byte* _min, byte* _sec, bool* _minus, int* _addr);
void total_program()
{
  if (total_checked)
  {
    if (current_revolution != last_revolution)
    {
      last_revolution = current_revolution;
      if (direction != old_direction)
      {
        old_direction = direction;
        total_second--;
      }
      total_second++;
      write_time_data_to_eeprom(&total_hrs, &total_minute, &total_second, 0, &TOTAL_ADDR);
      if (total_second > 99)
      {
        total_second = 0;
        total_minute++;
        if (total_minute > 99)
        {
          total_hrs++;
          total_minute = 0;
          if (total_hrs > 99)
          {
            total_hrs = 0;
          }
        }
      }
sendtt(&total_hrs,&total_minute,&total_second);
    }
  }
}