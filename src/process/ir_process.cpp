#include "process/ir_process.h"
extern bool data_IR_COMMAND_CODE;
extern char*PREVIOUS_CODE;
extern char*PLAY_CODE;
extern char*PAUSE_CODE;
extern char*STOP_CODE;
extern char*NEXT_CODE;
extern char*EJECT_CODE;
bool IR_COMMAND(uint16_t _COMMAND)
{ 
    if((data_IR_COMMAND_CODE == _COMMAND))
    {  
        return 1;
      }
      else
    {return 0;}
}
