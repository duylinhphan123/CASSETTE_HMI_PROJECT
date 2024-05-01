#ifndef _EEPROM_PROCESS_H_
#define _EEPROM_PROCESS_H_
#include <Arduino.h>
void write_time_data_to_eeprom(byte* _hrs, byte* _min, byte* _sec, bool* _minus, int* _addr);
#endif