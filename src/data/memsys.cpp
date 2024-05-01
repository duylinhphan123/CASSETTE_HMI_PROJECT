#include "data/memsys.h"
bool memsys::sw_stat()
{
return _SW_STAT;
}
bool memsys::stop_from_play()
{
    return _FLAG_STOP_FROM_PLAY;
}
bool memsys::play_from_stop()
{
    return _FLAG_PLAY_FROM_STOP;
}
