#ifndef ENCODER_H_
#define ENCODER_H_
#include <Arduino.h>
void simu_encoder_reset_circumlation(int32_t* _revolution,int32_t* _current_revolution);
void ENCODER_SIMULATION(int32_t* _revolution,int32_t* _current_revolution,int32_t* _current_angle);
bool encoder_dir(int32_t* _current_angle, int32_t* _last_angle, bool* _direction);
#endif
