#include "encoder_process.h"
#include "external_lib/Eeprom24Cxx.h"
static Eeprom24C eeprom(32, 0x57);
void write_time_data_to_eeprom(byte* _hrs, byte* _min, byte* _sec, bool* _minus, uint32_t* _addr)
{
  eeprom.write_1_byte(*_addr, *_hrs);
  eeprom.write_1_byte(*_addr + 1, *_min);
  eeprom.write_1_byte(*_addr + 2, *_sec);
  eeprom.write_1_byte(*_addr + 3, *_minus);
}