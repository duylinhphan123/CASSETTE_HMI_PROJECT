#include "encoder_process.h"
static bool data_MOTOR_STAT = 0;
bool _old_encoder_state = 0;
bool _encoder_state = 0;
uint32_t _encoder_time = 0;
int32_t _temp_angle = 0;
extern void (*uart)(String,int,int32_t);
void simu_encoder_reset_circumlation(int32_t* _revolution,int32_t* _current_revolution)
{
 *_revolution = 0;
 *_current_revolution = 0;
}

void ENCODER_SIMULATION(int32_t* _revolution,int32_t* _current_revolution,int32_t* _current_angle)
{
 if (_encoder_state!= 0)
  {
    if (millis() - _encoder_time > 22)
    {
      _encoder_time = millis();
      if (_encoder_state == 2)
      {
        *_current_angle += 91;
        _temp_angle += 91;
        if (_temp_angle > 360)
        {
          _temp_angle = _temp_angle - 360;
          *_revolution++;
          *_current_revolution = *_revolution;
        }
      }

      if (_encoder_state == 1)
      {
        *_current_angle -= 91;
        _temp_angle -= 91;
        if (_temp_angle < 0)
        {
          _temp_angle = 360 - _temp_angle;
          _revolution--;
          *_current_revolution = *_revolution;
        }
      }
    }
  }
  if (_encoder_state != _old_encoder_state)
  {
    _old_encoder_state = _encoder_state;
    data_MOTOR_STAT = _old_encoder_state;
    uart("MT", 1, _encoder_state);
  }
}

bool encoder_dir(int32_t* _current_angle, int32_t* _last_angle, bool* _direction)
{
  if (*_current_angle - *_last_angle > 0)
  {
    *_last_angle = *_current_angle;
    *_direction = 1;
  }
  else if (*_current_angle - *_last_angle < 0)
  {
    *_last_angle = *_current_angle;
    *_direction = 0;
  }
  return *_direction;
}


