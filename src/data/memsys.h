#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_
#include <stdint.h>
class memsys
{
private:
    /* data */
    bool _SW_STAT = 0;
    bool _FLAG_STOP_FROM_PLAY = 0;
    bool _FLAG_PLAY_FROM_STOP = 0;
    bool _FLAG_WAIT_TIMER_EN = 0;
    bool _FLAG_WAIT_TIMER_START = 0;
    bool _FLAG_WAIT_TIMER_RESET = 0;
    bool _FLAG_WAIT_TIMER_OUTPUT = 0;
    uint32_t _CURRENT_WAIT_TIMER = 0;
public:
    bool sw_stat();
    bool stop_from_play();
    bool play_from_stop();
    bool current_mode();
    bool timer_wait_out();
    void reset_wait_timer();
   
};



#endif // !_DATA_TRANSFER_H_